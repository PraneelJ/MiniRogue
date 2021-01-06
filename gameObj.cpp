//
//  gameObj.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "gameObj.h"


gameObj::~gameObj(){
    
}

gameObj::gameObj(string nam, int r, int c){
    // constructor takes in the name of the object and its location on the grid
    
    // based on the objects name, it assigns its attributes 
    name = nam;
    
    ro = r;
    col = c;
    
    if(name == "short sword"){
        dexbonus = 0;
        dmgamt = 2;
        action = "slashes";
    }
    else if(name == "long sword"){
        dexbonus =2;
        dmgamt =4;
        action = "swings";
    }
    else if(name == "mace"){
        dexbonus =0;
        dmgamt =2;
        action = "swings";
    }
    else if(name == "magic fangs of sleep"){
        dexbonus =3;
        dmgamt =2;
        action ="strikes";
    }
    else if(name == "magic axe"){
        dexbonus =5;
        dmgamt =5;
        action = "chops";
    }
    else{
        dexbonus = 0;
        dmgamt = 0 ;
        action = "none";
    }
    
    
    
    
    
}
