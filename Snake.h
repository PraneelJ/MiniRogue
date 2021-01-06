//
//  Snake.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp
#include "Actor.h"
using namespace std;

class Dungeon;


class Snake : public Actor
{
public:
   
    Snake(int r, int c);
    int prow() const {return ro;}
    int pcol() const {return col;}
    
    virtual char getchar() const {return 'S';}
  
    
private:
    int ro;
    int col;
    
};




#endif
