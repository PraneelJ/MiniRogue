//
//  Dragon.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "Dragon.h"
#include "Weapon.h"

#include "utilities.h"


//constructor used to call derived functions from the base class Actor, to assign values to the monster's attributes
Dragon::Dragon(int r, int c):Actor(){
    
    
    ro = r;
    col = c;
    setpos(ro, col);
    int x =randInt(20,25);
    hitp(x);
    maxhitp(x);
    weap(new Weapon("long sword",0,0));
    ar(4);
    stre(4);
    dex(4);
    slt(0);
    setname("Dragon");
    
    
}


