//
//  Bogeymen.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef Bogeymen_hpp
#define Bogeymen_hpp
#include "Actor.h"

class Dungeon;

using namespace std;

class Bogeymen : public Actor
{
public:
    
    Bogeymen(int r, int c);
    int prow() const {return ro;}
    int pcol() const {return col;}
    virtual char getchar() const {return 'B';}
   
    
private:
    int ro;
    int col;
    
};


#endif 
