//
//  Goblin.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "Goblin.h"
#include "utilities.h"
#include "Weapon.h"

//constructor used to call derived functions from the base class Actor, to assign values to the monster's attributes
Goblin::Goblin(int r, int c):Actor(){
    
    
    ro = r;
    col = c;
    setpos(ro, col);
    hitp(randInt(15,20));
    weap(new Weapon("short sword",0,0));
    ar(1);
    stre(3);
    dex(1);
    slt(0);
    setname("Goblin");
    
    
}




