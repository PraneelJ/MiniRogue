//
//  Scroll.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "Scroll.h"

//constructor calls the gameObj constructor and passes it the scroll's name and location
Scroll::Scroll(string a, int r, int c): gameObj(a, r, c) {
    
    name = a; 
}
