//
//  Weapon.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef Weapon_hpp
#define Weapon_hpp
#include "gameObj.h"
#include <string>

using namespace std;

class Weapon: public gameObj{
    
public:
    
    Weapon(string a, int r, int c);

    
private:
    string name;
   
    
    
};

#endif /* Weapon_hpp */
