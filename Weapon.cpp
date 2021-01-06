//
//  Weapon.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "Weapon.h"

//constructor calls the gameObj constructor and passes it the weapon's name and location
Weapon::Weapon(string a, int r,int c): gameObj(a, r, c){
    
    name = a;
    
    
}
