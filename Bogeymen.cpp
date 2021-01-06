//
//  Bogeymen.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "Bogeymen.h"
#include "utilities.h"
#include "Weapon.h"


//constructor used to call derived functions from the base class Actor, to assign values to the monster's attributes 
Bogeymen::Bogeymen(int r, int c): Actor(){
    
    
    ro = r;
    col = c;
    setpos(ro, col);
    hitp(randInt(5,10));
    weap(new Weapon("short sword",0,0));
    ar(2);
    stre(randInt(2, 3));
    dex(randInt(2, 3));
    slt(0);
    setname("Bogeyman");
    
    
}


