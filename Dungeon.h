//
//  Dungeon.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/12/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef Dungeon_hpp
#define Dungeon_hpp

#include <list>
#include <string>
using namespace std;
class gameObj;

class player;
class stairs;
class idol;
class Actor; 

class Dungeon{
public:
    // constructor that takes in the level of the dungeon
    Dungeon(int x, int y);
    ~Dungeon();
    char getCellStatus(int r, int c) const;
    void display(player* pl);
    void putchar(int a, int b, char x);
    bool stairpos(int r, int c);
    bool idolpos(int r, int c);
    void dungeonstuff();
    string pickobJ(player* pl);
    void getspot(int& a, int& b);
    void setempty(int a, int b);
    void makemonsters(int a);
    stairs* getstair() const{return m_stair;}
    void playeraction(char d, player* pl, list<string>& a);
    void attack(Actor* attacker, Actor* defender,bool& sl,bool& hits);
    void monstersmove(player* pl,list<string>& a );
    void SnBmove(Actor* monst, Actor* player);
    void gobmove(Actor* monst, Actor* player);
    

private:
    // array used to store the values of and display the grid
    char displayGrid[18][70];
    int level;
    int gobsmell;
    // pointers to the stairs and the idol
    stairs* m_stair;
    idol* m_idol;
    
    // lists used to store the objects in the dungeon and the monsters in the dungeon
    list<gameObj*>dungObjs;
    list<Actor*>monstlist;
    
   
    
    // The room struct used to create the rooms of the dungeon
    struct room {
        room(int rx, int finr, int cx, int finc);
        int r;
        int c;
        
        int endr;
        int endc;
        
        int midr;
        int midc;
        
        
    };
    // the list used to store rooms.
    list<room*> dun;
};

#endif /* Dungeon_hpp */
