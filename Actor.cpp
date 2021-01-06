//
//  Actor.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/12/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "Actor.h"
#include "gameObj.h"


Actor::Actor(){
    
}

Actor::~Actor(){
    // deleting the weapon wielded by the actor
    delete weapon;

}

void Actor::setpos(int r, int c){
    m_row = r;
    m_col = c; 
}

void Actor::setname(string a){
    name = a; 
}

void Actor::hitp(int a){
    hitpoints = a;
}

void Actor::maxhitp(int a){
    maxhitpoints = a;
}

void Actor::weap(gameObj* a){
    weapon = a;
}
void Actor::ar(int a){
    arm = a;
}
void Actor::stre(int a){
    stren = a;
}
void Actor::dex(int a){
    dexter = a;
}
void Actor::slt(int a){
    sltime = a;
}
