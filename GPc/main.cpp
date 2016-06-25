#include <fstream>
#include <cstdlib>
#include "ndlexceptions.h"
#include "ndlstrutil.h"
#include "CMatrix.h"
#include "CKern.h"
#include "CGplvm.h"
#include "CClctrl.h"
#include "CClgplvm.h"
#include <limits>

int readSvmlDataFile(CMatrix& X, CMatrix& y, const string fileName);
int main(int argc, char* argv[]){
  cout<<"hello world"<<endl;

  string trainDataFileName="examples/new_pose.svml";
  /*
  string modelFileName="swagger_back_constrained.model";
  CGplvm* pmodel=readGplvmFromFile(modelFileName, 2);

  CMatrix Xext(pmodel->pX->getRows(), 3, 0.1);
  for(int i=0; i<pmodel->pX->getRows(); i++)
  {
  for(int j=0; j<2; j++)
  Xext.setVal(pmodel->pX->getVal(i, j), i, j);
}
*/
CMatrix Y;
CMatrix labs;
vector<int> labels;
readSvmlDataFile(Y, labs, trainDataFileName);

vector<int> labelledIndices;
for(int i=0; i<labs.getRows(); i++)
{
  double val = labs.getVal(i);
  int intVal = (int)val;

  labels.push_back(intVal);
}
int latentDim = 2;
int numData = Y.getRows();
CMatrix X(numData, latentDim);

CCmpndKern kern(X);

cout<<"set RBF kern"<<endl;
CKern* defaultKern = new CRbfKern(X);
kern.addKern(defaultKern);

kern.addKern(new CBiasKern(X));
kern.addKern(new CWhiteKern(X));

CMatrix ymean = meanCol(Y);
cout<<ymean<<endl;

//sup Ymean from Y
for(int i=0;i<Y.getRows();i++){
  Y.axpyRowRow(i,ymean,0,-1);
}

CMatrix K;

K.resize(numData,numData);

string modelFileName="new_pose.model";
CGplvm* pmodel=readGplvmFromFile(modelFileName, 2);
pmodel->pkern->display(cout);

CKern* pkern = pmodel->pkern;
pkern->display(cout);

//calculate K
double kVal=0.0;
for(int i=0; i<numData; i++)
{
  K.setVal(pkern->diagComputeElement(*pmodel->pX, i), i, i);
  for(int j=0; j<i; j++)
  {
    kVal=pkern->computeElement(*pmodel->pX, i, *pmodel->pX, j);
    K.setVal(kVal, i, j);
    K.setVal(kVal, j, i);
  }
}
K.setSymmetric(true);

//cout<<K<<endl;


CMatrix Ktemp;
Ktemp.resize(1,2);
cout<<pmodel->pX->getRows()<<endl;//27
cout<<pmodel->pX->getCols()<<endl;//2

//GET x
int frame_n = atoi(argv[1]);
int option = atoi(argv[2]);
double num_temp_0,num_temp_1;
if(option == 0){
 num_temp_0 =( pmodel->pX->getVal(frame_n-1,0)+pmodel->pX->getVal(frame_n+1,0) )/2.0;
 num_temp_1 =( pmodel->pX->getVal(frame_n-1,1)+pmodel->pX->getVal(frame_n+1,1) )/2.0 ;
}
else{
 num_temp_0 = pmodel->pX->getVal(frame_n,0);
 num_temp_1 = pmodel->pX->getVal(frame_n,1);
}

Ktemp.setVal(num_temp_0, 0, 0);
Ktemp.setVal(num_temp_1, 0, 1);

CMatrix Kx;
Kx.resize(1,numData);
for(int j=0; j<numData; j++)
{
  kVal=pkern->computeElement(Ktemp, 0, *pmodel->pX, j);
  Kx.setVal(kVal, 0, j);
}


//calculate invK
CMatrix invK;
invK.resize(numData,numData);
CMatrix LcholK;
LcholK.deepCopy(K);
LcholK.chol(); /// this will initially be upper triangular.
invK.setSymmetric(true);
invK.pdinv(LcholK);

Y.trans();
CMatrix tempproduct = multiply(Y,invK);
Kx.trans();
CMatrix vector = multiply(tempproduct, Kx);
vector.trans();
Y.trans();

CMatrix diffvector;
double absdiff = 0;
diffvector.resize(1,vector.getCols());
for(int j=0;j<vector.getCols();j++){
  //double val = (Y.getVal(frame_n, j)- vector.getVal(j))/(Y.getVal(frame_n, j) + numeric_limits<float>::min());
  //double val = abs(Y.getVal(frame_n, j)- vector.getVal(j));
  double val = abs((Y.getVal(frame_n, j)- vector.getVal(j))/(ymean.getVal(j) + 0.000000000000001));
  diffvector.setVal(val,j);
  absdiff += val;
}

cout<<diffvector<<endl;
cout<<"absdiff = "<<absdiff<<endl;

CMatrix rev;
rev.resize(1,vector.getCols());
for(int j=0;j<vector.getCols();j++){
  double val = vector.getVal(j) + ymean.getVal(j);
  rev.setVal(val,j);
}

cout<<rev<<endl;
cout<<rev.getCols()<<endl;
ofstream myfile;
myfile.open ("exampleoutput.txt");
myfile << rev;
myfile.close();
return 0;


return 0;

}

int readSvmlDataFile(CMatrix& X, CMatrix& y, const string fileName)
{
  ifstream in(fileName.c_str());
  if(!in.is_open()) throw ndlexceptions::FileReadError(fileName);

  string line;
  string token;
  bool featureRead=false;
  int numData=0;
  int maxFeat=0;
  while(getline(in, line))
  {
    featureRead=false;

    if(line[line.size()-1]=='\r')
    line.erase(line.size()-1);
    if(line[0]=='#')
    continue;
    numData++;
    int pos=0;
    while(pos<line.size())
    {
      token.erase();
      while(pos<line.size() && line[pos]!=' ')
      {
        token+=line[pos];
        pos++;
      }
      pos++;
      if(token.size()>0)
      {
        // deal with token.
        if(featureRead)
        {
          int ind = token.find(':');
          if(ind==std::string::npos || ind < 0)
          {
            ndlexceptions::StreamFormatError err("");
            throw ndlexceptions::FileFormatError(fileName, err);
          }
          string featStr=token.substr(0, ind);
          int featNum = atoi(featStr.c_str());
          if(featNum>maxFeat)
          maxFeat=featNum;
        }
        else
        {
          featureRead=true;
        }
      }
    }

  }

  cout << "Data number of features: " << maxFeat << endl;
  cout << "Number of data: " << numData << endl;

  X.resize(numData, maxFeat);
  X.zeros();
  y.resize(numData, 1);
  y.zeros();
  in.close();
  ifstream inToo(fileName.c_str());
  int pointNo=0;
  while(getline(inToo, line))
  {
    if(line[line.size()-1]=='\r')
    line.erase(line.size()-1);
    featureRead=false;
    if(line[0]=='#')
    continue;
    else
    {
      int pos=0;
      while(pos<line.size())
      {
        token.erase();
        while(pos<line.size() && line[pos]!=' ')
        {
          token+=line[pos];
          pos++;
        }
        pos++;
        if(token.size()>0)
        {
          // deal with token.
          if(featureRead)
          {
            int ind = token.find(':');
            // TODO Check that : is in the string.
            string featStr=token.substr(0, ind);
            string featValStr=token.substr(ind+1, token.size()-ind);
            int featNum = atoi(featStr.c_str());
            if(featNum<1 || featNum>maxFeat || pointNo<0 || pointNo>=numData)
            {
              ndlexceptions::StreamFormatError err("");
              throw ndlexceptions::FileFormatError(fileName, err);
            }

            double featVal = atof(featValStr.c_str());
            X.setVal(featVal, pointNo, featNum-1);
          }
          else
          {
            y.setVal(atof(token.c_str()), pointNo);
            featureRead=true;
          }
        }
      }

    }
    pointNo++;
  }
  // WVB ADDED
  return -1;
}
