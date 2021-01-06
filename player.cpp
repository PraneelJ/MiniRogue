//
//  player.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/12/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "player.h"
#include "utilities.h"
#include "Dungeon.h"
#include "gameObj.h"
#include "Scroll.h"
#include "Weapon.h"
#include <list>



// players housekeeping functions

player::player(int r, int c):Actor(){
    //player constructor calls methods derived from class actor to assign values to the player's attributes
    
    gameObj* p =new Weapon("short sword",0,0);
    ro = r;
    col = c;
    setpos(ro, col);
    hitp(20);
    weap(p);
    ar(2);
    stre(2);
    dex(2);
    slt(0);
    setname("Player");
    maxhitp(20);
    
// the player's weapon is pushed onto the player inventory list .
    pObjs.push_back(p);

}

player::~player(){
    
    // looping through the player's inventory list to delete all objects
    for (list<gameObj*>::iterator p = pObjs.begin();p != pObjs.end();){
       
        // not deleting the weapon that the player weilds as this will be destroyed when the base class (Actor) destructor is called.
        if((*p)==getweap()){
            p = pObjs.erase(p);
            continue;
            
        }
        
           delete (*p);
        p = pObjs.erase(p);
       }
  
    
}

bool player::playermove(char dir, Dungeon* m_dung){
    
    //checking if the player can move in that direction
    // if player can move, set the players current position in the grid to empty
    // change the player's position coordinates
    // set the new posiiton in the grid to '@'
    //return true if the player moved
    
    
    if(dir == ARROW_UP && (m_dung->getCellStatus(r()-1, c()) == ' '||m_dung->getCellStatus(r()-1, c()) == '>'|| m_dung->getCellStatus(r()-1, c()) == '&'||m_dung->getCellStatus(r()-1, c()) == '?'||m_dung->getCellStatus(r()-1, c()) == ')')){
        m_dung->setempty(ro, col);
        ro--;
        m_dung->putchar(ro, col, '@');
        setpos(ro, col);
        return true;
    }

    else if(dir == ARROW_DOWN && (m_dung->getCellStatus(r()+1, c()) == ' '||m_dung->getCellStatus(r()+1, c()) == '>'|| m_dung->getCellStatus(r()+1, c()) == '&'||m_dung->getCellStatus(r()+1, c()) == '?'||m_dung->getCellStatus(r()+1, c()) == ')')){
        m_dung->setempty(ro, col);
        ro++;
        m_dung->putchar(ro, col, '@');
        setpos(ro, col);
        return true;

    }
    
    else if(dir == ARROW_LEFT && (m_dung->getCellStatus(r(), c()-1) == ' '||m_dung->getCellStatus(r(), c()-1) == '>'|| m_dung->getCellStatus(r(), c()-1) == '&'||m_dung->getCellStatus(r(), c()-1) == '?'||m_dung->getCellStatus(r(), c()-1) == ')')){
        m_dung->setempty(ro, col);
        col--;
        m_dung->putchar(ro, col, '@');
        setpos(ro, col);
        return true;
    }
    
    else if(dir == ARROW_RIGHT && (m_dung->getCellStatus(r(), c()+1) == ' '||m_dung->getCellStatus(r(), c()+1) == '>'|| m_dung->getCellStatus(r(), c()+1) == '&'||m_dung->getCellStatus(r(), c()+1) == '?'||m_dung->getCellStatus(r(), c()+1) == ')')){
        m_dung->setempty(ro, col);
        col++;
        m_dung->putchar(ro, col, '@');
        setpos(ro, col);
        return true; 
    }
    //return false if the player did not move
    
    return false;
    
}

// method to change the players location
void player::psetpos(int r, int c){
    ro = r;
    col = c;
    setpos(ro, col);
}

void player::inventory(){
    
    // call clear screen and display the inventory onto the screen
    clearScreen();
      cout<<"Inventory:"<<endl;
      char i = 'a';
    // use a character 'i' and increment it to display the inventory sequencially
    for (list<gameObj*>::iterator p = pObjs.begin();p != pObjs.end(); p++){
         
        cout<< i<<". "<<(*p)->getname()<<endl;
        i++;
       }

    
}

bool player::addtoinvent(gameObj *r){
    
    //loop through teh inventory with an int counter to check teh number of items in teh inventory
    int x = 0;
    for (list<gameObj*>::iterator p = pObjs.begin();p != pObjs.end(); p++)
        x++;
    
    // if inventory has less tahn 26 items, add the item to the inventory list and return true
    // else return false
    if(x<26){
    pObjs.push_back(r);
        return true;
    }
    else{ return false; }
    
}


string player::wieldweapon(){
    //input a character from the user
    char d = getCharacter();
    //check if the character is valid
    if(!(d>='a'&& d<='z'))
        return "none";
    // loop through the list to check what is the last alphabet used to show an object
    char x = 'a';
    for (list<gameObj*>::iterator p = pObjs.begin();p != pObjs.end(); p++)
    x++;
    
    // check if the character inputted by the user is valid by comparing it to the last alphabet used by the inventory
    if(d>=x)
        return "none";
    
    gameObj* targ = nullptr;
    
    char checker = 'a';
    bool exists = false;
    // loop through the list to check which object the player has selected
    
    for (list<gameObj*>::iterator p = pObjs.begin();p != pObjs.end(); p++){
        
         if(d == checker){
                   exists = true;
                   targ = (*p);
               }
        
        checker++;
    }
    
    
    if(exists){
        
        if(targ!=nullptr){
            // check if the object is a scroll. ie. check the action of the object, all scrolls have action "none"
            // if object is a scroll, return the name of the scroll
        if(targ->getaction()=="none")
        return targ->getname();
            
            string n = targ->getname();
            
            //if the target is a weapon, call the weap() function to wield the weapon selected by the user and return its name
            
            if(n== "short sword"){
                weap(targ);
                return n;
            }
            else if( n == "long sword")
            {
              weap(targ);
                return n;
            }
            else if(n=="mace"){
             weap(targ);
                return n;
            }
            else if(n=="magic axe"){
                weap(targ);
               return n;
            }
        
            else if(n=="magic fangs of sleep"){
               weap(targ);
                return n;
            }
            
            
        }
    }
        // return "none" if character inputted by used is not valid
    return "none";
    
}

string player::readscroll(){
    //input a character from the user
    char d = getCharacter();
    //check if the character is valid
    if(!(d>='a'&& d<='z'))
        return "none";
    // loop through the list to check what is the last alphabet used to show an object
    char x = 'a';
    for (list<gameObj*>::iterator p = pObjs.begin();p != pObjs.end(); p++)
    x++;
    // check if the character inputted by the user is valid by comparing it to the last alphabet used by the inventory
    if(d>=x)
    return "none";
    
    gameObj* targ = nullptr;
    
    char checker = 'a';
    bool exists = false;
    
    string n;
    // loop through the list to check which object the player has selected
    for (list<gameObj*>::iterator p = pObjs.begin();p != pObjs.end(); p++){
        
        if(d == checker){
            exists = true;
            targ = (*p);
            //if the target selected by the user is a weapon , return its name
            if(targ->getaction()!="none"){
                return targ->getname();
            }
            //if the object selected by the user is a scroll , store its name in a variable, delete the scroll and erase its pointer from the list
            else{
                n = targ->getname();
                delete targ;
                p = pObjs.erase(p);
                
            }
        }
            
        
        checker++;
    }
    
    // if the user has selected a scroll, use the scroll's name to use its powers
    if(exists){
        if(targ!=nullptr){
            // if scroll is of teleportation, just return its name and appropriate message
                if(n== "scroll of teleportation"){
                
                    n = "scroll of teleportation. You feel your body wrenched in space and time.";
                    return n;
                }// if it is any other scroll, perform the task required and return the name of the scroll along with the message
                else if( n == "scroll of improve armor")
                {  // increasing the players armor
                    ar(getar()+randInt(1, 3));
                    
                    // if armor is above 99, set it to 99
                    if(getar()>99)
                        ar(99);
                    
                    n = "scroll of improve armor. Your armor glows blue.";
                                return n;
                }
                else if(n=="scroll of raise strength"){
                 // increasing the player's strength
                    stre(getstre()+randInt(1, 3));
                    
                    // if strength is above 99 , set it to 99
                    if(getstre()>99)
                        stre(99);
                               
                    n = "scroll of raise strength. Your muscles bulge.";
                                return n;
                }
                else if(n=="scroll of enhance health"){
                    // increase the player's max hitpoints
                    maxhitp(getmaxhitp()+randInt(3, 8));
                
                    // if maxhealth is above 99, set it to 99
                    if(getmaxhitp()>99)
                        maxhitp(99);
                
                    
                    
                    n = "scroll of enhance health. You feel your heart beating stronger.";
                                return n;
                }
                else if(n=="scroll of enhance dexterity"){
                    //increasing the player's dexterity
                    dex(getdex()+1);
                    
                    //if dexterity is above 99, set it to 99 
                    if(getdex()>99)
                        dex(99);
                    
                    n = "scroll of enhance dexterity. You feel like less of a klutz.";
                                return n;
                }
        
            
            
        }
        
    }
    return "none";
}
