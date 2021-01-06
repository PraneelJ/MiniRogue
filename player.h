//
//  player.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/12/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef player_hpp
#define player_hpp
#include "Actor.h"
#include <list>

class Actor;
class gameObj;

class Dungeon;

using namespace std;
class player : public Actor
{
public:
    
    player(int r, int c);
    virtual ~player();
    // getter and setter methods to
    int prow() const {return ro;}
    int pcol() const {return col;}
    void psetpos(int r, int c);
    virtual char getchar() const {return '@';}
    
    //methods to make the player move, access the players inventory and use objects from the inventory. 
   bool playermove(char dir, Dungeon* x);
    void inventory();
    bool addtoinvent(gameObj* p);
    string wieldweapon();
    string readscroll();
    

    
private:
    // variables to store the players position
    int ro;
    int col;
    // list used to store the items in the player's inventory 
    list<gameObj*> pObjs;
};




#endif
