//
//  Dragon.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef Dragon_hpp
#define Dragon_hpp
#include "Actor.h"
using namespace std;

class Dungeon;


class Dragon : public Actor
{
public:
    

    Dragon(int r, int c);
    int prow() const {return ro;}
    int pcol() const {return col;}
    
    virtual char getchar() const {return 'D';}
   
    
private:
    int ro;
    int col;
    
};


#endif /* Dragon_hpp */
