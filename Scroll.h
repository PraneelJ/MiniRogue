//
//  Scroll.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef Scroll_hpp
#define Scroll_hpp
#include "gameObj.h"

#include <string>

using namespace std;

class Scroll : public gameObj{
    
public:
    
    Scroll(string a, int r, int c);
    
private:
    string name;
  
    
    
};

#endif /* Scroll_hpp */
