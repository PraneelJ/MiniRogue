//
//  Snake.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "Snake.h"
#include "utilities.h"
#include "Weapon.h"



//constructor used to call derived functions from the base class Actor, to assign values to the monster's attributes 
Snake::Snake(int r, int c):Actor(){
    
    
    ro = r;
    col = c;
    setpos(ro, col);
    hitp(randInt(3,6));
   weap(new Weapon("magic fangs of sleep",0,0));
    ar(3);
    stre(2);
    dex(2);
    slt(0);
    setname("Snakewoman");
    
    
}


