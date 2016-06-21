//
//  Arbre.cpp
//  InverseKinematics
//
//  Created by Etcheverry Mayalen on 03/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#include "Arbre.h"

using namespace std;

void Arbre::loadBVH (const std::string & filename) {
    FILE * file = fopen(filename.c_str (), "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
    }
    
    
    unsigned int noeudCourant = -1;
    unsigned int i = -1; //nbr de noeuds
    
    QList<int> endSite;
    endSite <<7<<14<<49<<44<<39<<34<<29<<60<<65<<70<<75<<80<<83;
    
    
    
    N.resize(84);
    Origine.resize(119);
    
    
    while( 1 ){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        
        if (strcmp( lineHeader, "MOTION" ) == 0){
            break; // EOF = End Of File. Quit the loop.
        }
        // else : parse lineHeader
        
        if (strcmp( lineHeader, "{" ) == 0){
            i++;
            N[i]=new Noeud(noeudCourant,119);
            noeudCourant=i;
        }
        
        if (strcmp( lineHeader, "}" ) == 0 ){
            
            noeudCourant=N[noeudCourant]->father;
        }
        
        if (strcmp( lineHeader, "OFFSET" ) == 0 ){
            
            fscanf(file, "%f %f %f\n", &N[i]->offset[0],&N[i]->offset[1],&N[i]->offset[2]);
                    }
        
        
            
            else {printf("File can't be read by our simple parser :  Try exporting with other options\n");}
        
    }
    
   for (int j=0; j<119; j++) {
        for (int i=0; i<255; i++) {
            if (i<3) {
                fscanf(file, "%f", &Origine[j][i]);
            }
            else if (std::find(endSite.begin(), endSite.end(), (i-3)/3) != endSite.end()) {
                N[(i-3)/3]->rotation[j] = Vec3f(0.0,0.0,0.0);
                }
            else {   if ((i-3)%3==0) {
                    fscanf(file, "%f", &N[(i-3)/3]->rotation[j][0]);
                }
                
                if ((i-3)%3==1) {
                    fscanf(file, "%f", &N[(i-3)/3]->rotation[j][1]);
                }
                
                if ((i-3)%3==2) {
                    fscanf(file, "%f", &N[(i-3)/3]->rotation[j][2]);
                }}
            }
        }
    
    
    
    /*for (int i=0; i<meshes.size();i++) {
     meshes[i].recomputeNormals();
     }*/

    cout<<N[0]->father<<endl;
    cout<<N[2]->father<<endl;
    cout<<N[8]->father<<endl;
    cout<<N[50]->father<<endl;
    
    cout<<"noeud 0"<<endl;
    cout<<N[0]->p[0]<<endl;
    cout<<N[0]->p[1]<<endl;
    
    cout<<"rotation NO"<<endl;
    cout<<N[0]->rotation[0]<<endl;
    cout<<N[0]->rotation[1]<<endl;
    cout<<N[0]->rotation[2]<<endl;
    
    cout<<"rotation N1"<<endl;
    cout<<N[1]->rotation[0]<<endl;
    
    cout<<"rotation N2"<<endl;
    cout<<N[2]->rotation[0]<<endl;
    
    cout<<"rotation N3"<<endl;
    cout<<N[3]->rotation[0]<<endl;
    
    cout<<"rotation N82"<<endl;
    cout<<N[82]->rotation[0]<<endl;
    
    cout<<cos(M_PI)<<endl;
    
    
    Matrix<float> Rx= Matrix<float>(3,3);
    Matrix<float> Ry= Matrix<float>(3,3);
    Matrix<float> Rz= Matrix<float>(3,3);
    
    Matrix<float> R=Matrix<float>(3,3);
    Matrix<float> T=Matrix<float>(3,1);
    
    Matrix<float> M=Matrix<float>(4,4);
    
    float Ox;
    float Oy;
    float Oz;
    
    
    for (int i=0; i<119;i++){
        for(int j =0; j<84 ;j++){
            
            Ox=N[j]->rotation[i][1];
            Oz=N[j]->rotation[i][0];
            Oy=N[j]->rotation[i][2];
        
            Rx.put(0,0,1);
            Rx.put(0,1,0);
            Rx.put(0,2,0);
            Rx.put(1,0,0);
            Rx.put(2,0,0);
        
            Rx.put(1,1,cos(Ox*M_PI/180));
            Rx.put(1,2,-sin(Ox*M_PI/180));
            Rx.put(2,1,sin(Ox*M_PI/180));
            Rx.put(2,2,cos(Ox*M_PI/180));
            
            Ry.put(0,1,0);
            Ry.put(1,0,0);
            Ry.put(1,2,0);
            Ry.put(2,1,0);
            Ry.put(1,1,1);
            
            Ry.put(0,0,cos(Oy*M_PI/180));
            Ry.put(2,0,-sin(Oy*M_PI/180));
            Ry.put(0,2,sin(Oy*M_PI/180));
            Ry.put(2,2,cos(Oy*M_PI/180));
            
            Rz.put(0,2,0);
            Rz.put(1,2,0);
            Rz.put(2,0,0);
            Rz.put(2,1,0);
            Rz.put(2,2,1);
            
            Rz.put(0,0,cos(Oz*M_PI/180));
            Rz.put(0,1,-sin(Oz*M_PI/180));
            Rz.put(1,0,sin(Oz*M_PI/180));
            Rz.put(1,1,cos(Oz*M_PI/180));
            
            R=Rz*Rx*Ry;
            
            T.put(0, 0, N[j]->offset[0]);
            T.put(1, 0, N[j]->offset[1]);
            T.put(2, 0, N[j]->offset[2]);
            
            for ( int k = 0;k<3;k++){
                for ( int l = 0;l<3;l++){
                    M.put(k,l,R.get(k,l));
                }}
            for ( int k = 0;k<3;k++){
                        M.put(k,3,T.get(k,0));
                    }
            for ( int l = 0;l<3;l++){
                M.put(3,l,0);
            }
            M.put(3,3,1);
            
            N[j]->M[i]=M;
            
    }
    
}
    int father;
        Matrix<float> T2=Matrix<float>(4,1);
    T2.put(3,0,1);
    
    
    for ( int m=0; m <119;m++){
    for (int i =0; i<84;i++){
        
        father=i;
        for(int k=0;k<4;k++){
            for(int l=0;l<4;l++){
                M.put(k,l,0);
            }
        }
        for(int k=0;k<4;k++){
            M.put(k,k,1);
        }
        
            
        while (father!=0) {
            father = N[father]->father;
            M = (N[father]->M[m])*M;
        }
        
        for(int k=0;k<3;k++){
            T2.put(k,0,N[i]->offset[k]);
        }
        
        for(int k=0;k<3;k++){
            N[i]->p[m][k]=(M*T2).get(k,0) + Origine[m][k];
            
            
        }}
       
       
        
        
    }
        centerAndScaleToUnit();
    
}

void Arbre::centerAndScaleToUnit () {
    Vec3f c;
    int l = 84*119;
    for( int g=0; g<119;g++) {
        for  (unsigned int i = 0; i < 84; i++){
            c += N[i]->p[g];
        }}
    c/=l;
    
    float maxD = dist (N[0]->p[0], c);
    for( int g=0; g<119;g++) {
        for (unsigned int i = 0; i < 84; i++){
            float m = dist (N[i]->p[g], c);
            if (m > maxD)
                maxD = m;
        } }
    
    for( int g=0; g<119;g++){
        for  (unsigned int i = 0; i < 84; i++)
            N[i]->p[g] = (N[i]->p[g] - c) / maxD;
    }}
