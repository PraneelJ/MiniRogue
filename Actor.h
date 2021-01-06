//
//  Actor.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/12/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp
#include <iostream>
#include <string>
using namespace std;

class gameObj;

class Actor{

public:
    
    Actor();
    virtual ~Actor();
    
    //getter and setter methods for all the Actor attributes
    int r() const {return m_row;}
    int c() const {return m_col;}
    void setname(string a);
    string getname() const {return name;}
    void setpos(int r, int c);
    void hitp(int a);
    int gethitp() const {return hitpoints;}
    void maxhitp(int a); 
    int getmaxhitp() const { return maxhitpoints; }
    void weap(gameObj* a);
    gameObj* getweap() const{return weapon;}
    void ar(int a);
    int getar() const {return arm;}
    void stre(int a);
    int getstre() const {return stren;}
    void dex(int a);
    int getdex() const {return dexter;}
    void slt(int a);
    int getslt() const {return sltime;}
    virtual char getchar() const = 0; 
    
private :
    // private variables to store all the actor's attributes
    // i.e. the name, location, hitpoints and maxhitpoints, weapon, armor, strenght, dexterity and sleep time. 
    string name;
    int m_row;
    int m_col;
    int hitpoints;
    int maxhitpoints;
    gameObj* weapon;
    int arm;
    int stren;
    int dexter;
    int sltime; 
    
    
};

#endif /* Actor_hpp */
