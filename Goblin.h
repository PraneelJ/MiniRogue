//
//  Goblin.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef Goblin_hpp
#define Goblin_hpp
#include "Actor.h"

using namespace std;

class Dungeon;


class Goblin : public Actor
{
public:
    
  
    Goblin(int r, int c);
    int prow() const {return ro;}
    int pcol() const {return col;}
    virtual char getchar() const {return 'G';}
   
    
private:
    int ro;
    int col;
    
};




#endif /* Goblin_hpp */
