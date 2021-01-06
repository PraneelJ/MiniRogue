//
//  gameObj.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef gameObj_hpp
#define gameObj_hpp
#include <string>

using namespace std;

class gameObj{
public:
    
    virtual ~gameObj();
    gameObj(string name, int r, int c);
    int getro() const {return ro;}
    int getcol() const {return col;}
    string getaction() const {return action;}
    string getname() const {return name;}
    int getdex() const{return dexbonus;}
    int getdmgamt() const {return dmgamt;}
    
private:
    string name;
    string action;
    int dexbonus;
    int dmgamt;
    int ro;
    int col;
    
    
    
};

#endif /* gameObj_hpp */
