//
//  Arbre.h
//  InverseKinematics
//
//  Created by Etcheverry Mayalen on 03/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Arbre_h
#define Arbre_h


#include "Vec3.h"
#include "Matrix.h"
#include <QList>
#include <stdio.h>
#include <QFile>



/// A simple Noeud class storing position father and child
class Noeud {
public:
    inline Noeud () {}
    inline Noeud (const int &father, const int &nbMoves) :  father(father),nbMoves(nbMoves){
        p.resize(nbMoves);
        rotation.resize(nbMoves);
        M.resize(nbMoves);
        for (int j=0; j<nbMoves; j++) {
            p[j]=Vec3f(0.0,0.0,0.0);
            rotation[j]=Vec3f(0.0,0.0,0.0);
            M[j]=Matrix<float>(4,4);
        }
        offset =Vec3f(0.0,0.0,0.0);
        
        
        
    }
    inline virtual ~Noeud () {}
    int father;
    int nbMoves;
    std::vector<Vec3f> p;
    Vec3f offset;
    std::vector<Vec3f> rotation;
    std::vector< Matrix <float> > M;
    
    
};


/// A Arbre class, storing a list of noeuds
class Arbre {
public:
    std::vector<Noeud*> N;
    std::vector<Vec3f> Origine;
    
    /// Loads the arbre from a <file>.bvh
    void loadBVH (const std::string & filename);
    
    
    /// scale to the unit cube and center at original
    void centerAndScaleToUnit ();
    
};

#endif /* Arbre_h */
