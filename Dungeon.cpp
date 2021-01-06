//
//  Dungeon.cpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/12/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#include "Dungeon.h"
#include "utilities.h"
#include "player.h"
#include "stairs.h"
#include "idol.h"
#include "Weapon.h"
#include "Scroll.h"
#include "gameObj.h"
#include "Goblin.h"
#include "Snake.h"
#include "Bogeymen.h"
#include "Dragon.h"
#include <climits>
#include <cstring>
#include <iostream>
using namespace std;


// Dungeon household functions ====================================================

Dungeon::Dungeon(int x, int y){
    
    // set the level of the dungeon and set the goblins smell distance
    level = x;
    gobsmell = y;
    
    // call the functions to create the random maze and the monsters
        
        dungeonstuff();
        makemonsters(level);
        
    //if its level 4 , create an idol and place in in the dungeon
        if (level ==4){
            m_idol = new idol();
                
                int rs;
                   int cs;
                   do
                   {
                       rs = randInt(1, 16);
                       cs = randInt(1, 68);
                   } while (this->getCellStatus(rs, cs) != ' ');
               
                m_idol->setpos(rs, cs);
        }

    }
    




Dungeon::~Dungeon(){
    
    // loop through the list of dungeon objects and destroy all of them
    for (list<gameObj*>::iterator p = dungObjs.begin();p != dungObjs.end(); ){
    
        delete (*p);
        p = dungObjs.erase(p);
    }
    
    // if an idol has been created, delete it
    if(level==4)
        delete m_idol;
    
    // if a stair has been created, delete it
    if(level!=4)
    delete m_stair;
    
    // loop through the list of monsters and delete them
   for (list<Actor*>::iterator m = monstlist.begin();m != monstlist.end(); ){
    
        delete (*m);
       m = monstlist.erase(m);
    }
    
    // loop through teh list of rooms created and delete them
    for (list<room*>::iterator p = dun.begin();p != dun.end(); ){
    
       delete (*p);
          p = dun.erase(p);
    }
    
}
 

//========================================================================================================

void Dungeon::display(player* pl){
    
    int r, c;
    
    
    // loop through the two dimensional array and replace everything except walls and stairs with an empty char
    for (r = 0; r < 18; r++)
     for (c = 0; c < 70; c++)
        if(displayGrid[r][c]!=' ' && displayGrid[r][c]!='#'&& displayGrid[r][c]!='>')
            displayGrid[r][c]=' ';
    
   // displaying the staircase if the staircase pointer is not null
        if (level!=4 && m_stair != nullptr)
            displayGrid[m_stair->row()][m_stair->col()] = '>';
   
   
    // displaying idol if the level is 4
    if(level ==4){
        if (m_idol != nullptr)
        displayGrid[m_idol->row()][m_idol->col()] = '&';
    }
    
    //displaying all the scrolls and weapons on the screen
    
    for (list<gameObj*>::iterator p = dungObjs.begin();p != dungObjs.end(); p++){
        
        if((*p)->getdmgamt()==0 &&(*p)->getdex()==0 && (*p)->getaction()=="none"){
            displayGrid[(*p)->getro()][(*p)->getcol()] = '?';
        }
        else{
            displayGrid[(*p)->getro()][(*p)->getcol()] = ')';
        }
        
        
    }
    
    //displaying all the monsters on the screen
    
    for (list<Actor*>::iterator p = monstlist.begin();p != monstlist.end(); p++){
        
        displayGrid[(*p)->r()][(*p)->c()] = (*p)->getchar();
    }
    
    
    
    // displaying the player if the player pointer is not null
    if (pl != nullptr)
    displayGrid[pl->r()][pl->c()] = '@';
    
    // Draw the grid
    clearScreen();
    for (r = 0; r <18; r++)
    {
        for (c = 0; c <70; c++)
            cout << displayGrid[r][c];
        cout << endl;
    }//display the player statistics each time after the maze is displayed
    cout<<"Dungeon Level: "<<level<<", Hit points: "<<pl->gethitp()<<", Armor: "<<pl->getar()<<", Strength: "<<pl->getstre()<<", Dexterity: "<<pl->getdex()<<endl;
    cout << endl;

    
}

// this function is used to return the character in a particluar cell
char Dungeon::getCellStatus(int r, int c) const
{
    
    return displayGrid[r][c];
}


bool Dungeon::stairpos(int r, int c){
    
    // function checks if stairs exist at the location passed as the parameters
    if(level!=4){
    if(r == m_stair->row() && c == m_stair->col())
        return true;
    }
    return false;
    
}

bool Dungeon::idolpos(int r, int c){
    // function checks if the idol exists at the location passed as the parameters
    if(level==4){
        
    if(r == m_idol->row() && c == m_idol->col())
        return true;
    }
    return false;
    
}

//this function is used to check if a player has picked up an object and if so, remove the object from the dungeon and add it to the players inventory.

string Dungeon::pickobJ(player *pl){
    string a;
    // loop through the list of dungeon objects to check if the player is on an object
    for (list<gameObj*>::iterator p = dungObjs.begin();p != dungObjs.end(); p++){
        
        // if the player is on an object
        if(pl->prow()==(*p)->getro() &&pl->pcol()==(*p)->getcol()){
            // remove object from the dungeon list
            a = (*p)->getname();
            gameObj* x = (*p);
            p = dungObjs.erase(p);
            
            // add object to player's inventory using addtoinvent function
            if(!pl->addtoinvent(x)){
                dungObjs.push_back(x);
                return "space";
            }
            else{
               return a;
            }
        }
    
    }
    return "none";
}

// this is the constructor for the room struct
Dungeon::room::room(int rx, int finr, int cx, int finc){
    r = rx;
    c = cx;
    endr = finr;
    endc = finc;

    // set values to the centre coordinates of the room
    midr = (r + endr) /2;
    midc = (c+ endc)/2;
}


void Dungeon::dungeonstuff(){
    {
    

        //==================================================================================
          // Fill displayGrid with '#'
        for (int r = 0; r < 18; r++)
            for (int c = 0; c < 70; c++)
                displayGrid[r][c] = '#';
        
        
        //creating random number of 4 to 6 rooms.
       int numrooms = randInt(4, 6);
    
        //loop while the size of the list with rooms has not reached the number of rooms required
        while(dun.size()<numrooms){
            

           // randomly chose the starting row and column
            int r_r = randInt(1, 13);
            int c_r =randInt(1, 63);
            
            
            
            // set length and breadth of the room to an invalid large size
            int len = 40;
            int bre = 40;
            
           // choose new values for breadth and lenght till they are not valid.
            while(r_r+bre-1>16||c_r+len-1>68){
                
                bre = randInt(4, 7);
                len = randInt(6,12);
            }
            
            
            // set the bool intersect to false
            bool intersect = false;
                
            // loop through the newly created dungeon dimensions. if any of those in the grid is an empty space, that implies that the new room intersects with an old one.
            for(int r = r_r; r<=r_r +bre; r++){
            for(int c = c_r; c<=c_r+len; c++){
                if(getCellStatus(r, c)==' '){
                    // if room intersects set intersect to true
                    intersect = true;
                    break;
                    break;
                }
                    
            }
            }
             
            // if the room does not intersect with any another, then add it to the list of rooms 'dun'.
        if(!intersect){
                
                room* h = new room(r_r,r_r +bre-1,c_r, c_r+ len-1);
                dun.push_back(h);
                
            // for the new room created, set all the coordinates in the grid to empty spaces i.e ' '.
                for(int r = (h)->r; r<(h)->endr+1; r++){
                for(int c = (h)->c; c<(h)->endc+1; c++){
                    setempty(r, c);
                }
                }
               
            }
            
        }
        
         
        // creating the corridors between the rooms
        //setting the iterator to the last room in the list
         list<room*>::iterator p = dun.end();
         p--;
          
        // making sure that there are more than one rooms in the list and if so, looping through the list to make corridors
        // which connect all the rooms
        if(dun.size()>1)
         while(p!=dun.begin()){
             //setting the starting r and c to the centre of the room
             int rb = (*p)->midr;
             int cb = (*p)->midc;
             
             
             //decrementing iterator to go to the next room
             p--;
             
             //setting the ending coordinates to the centre of the other room
             int re = (*p)->midr;
             int ce = (*p)->midc;
            
             
             // if starting column is less than ending column make an empty row from the starting column and row to the ending column
             
             if(cb<ce){
                 do{
                     cb++;
                     displayGrid[rb][cb]=' ';
                 }while(cb!=ce);
                 
                 // if the starting row is less than the ending row make an empty column from the starting row to the ending row
                 if(rb<re){
                     do{
                         rb++;
                         displayGrid[rb][ce]=' ';
                     }while(rb!=re);
                 }// if the ending row is less than the starting row, make an empty column from the ending row to the starting row
                 else if(rb>re){
                     do{
                         re++;
                         displayGrid[re][ce]=' ';
                     }while(rb!=re);
                 }
             }// if ending column is less than starting column make an empty row from the ending column and row to the starting column
             else if (cb>ce){
                 do{
                     ce++;
                     displayGrid[re][ce]=' ';
                 }while(cb!=ce);
                 
                 // if the starting row is less than the starting row make an empty column from the starting row to the ending row
                 if(rb<re){
                     do{
                         rb++;
                         displayGrid[rb][cb]=' ';
                     }while(rb!=re);
                 }// if the ending row is less than the starting row, make an empty column from the ending row to the starting row
                 else if(rb>re){
                     do{
                         re++;
                         displayGrid[re][cb]=' ';
                     }while(rb!=re);
                 }
             }//condition is called if starting and ending column are the same, thus only a vertical corridors between the rooms need to be created
             else {
                 // if the starting row is less than the starting row make an empty column from the starting row to the ending row
                 if(rb<re){
                     do{
                         rb++;
                         displayGrid[rb][cb]=' ';
                     }while(rb!=re);
                 }// if the ending row is less than the starting row, make an empty column from the ending row to the starting row
                 else if(rb>re){
                     do{
                         re++;
                         displayGrid[re][cb]=' ';;
                     }while(rb!=re);
                 
             }
             
             }
         
         }
        
         
        // if the level is not 4 , then create new stairs and add them to the game
        if(level!=4){
            m_stair = new stairs();
            
            int rs;
            int cs;
            do
            {
                rs = randInt(1, 16);
                cs = randInt(1, 68);
            } while (this->getCellStatus(rs, cs) != ' ');
            
            
            m_stair->setpos(rs, cs);
        }
        
        
        
        //==================================================================================
        
        //creating 2 or 3 game objects for each level
        int obnum = randInt(2, 3);
        
        for(int j = 0; j<obnum; j++){
        
            // get appropriate coordinates for the game object
            int rs;
            int cs;
            do
            {
                rs = randInt(1, 16);
                cs = randInt(1, 68);
            } while (this->getCellStatus(rs, cs) != ' ');
            
            int wtype = randInt(0, 6);
            
            // use randint to generate a random number
            // assign equal probability to all objects and create a new object depending on the random number produced.
            // push the new object to the list of dungeon objects
            if (wtype== 0){
                dungObjs.push_back(new Weapon("short sword",rs,cs));
                
            }
            else if(wtype==1){
                dungObjs.push_back(new Weapon("long sword",rs,cs));
            }
            else if(wtype==2){
                dungObjs.push_back(new Weapon("mace",rs,cs));
            }
            else if(wtype==3){
                dungObjs.push_back(new Scroll("scroll of improve armor",rs,cs));
            }
            else if(wtype==4){
                dungObjs.push_back(new Scroll("scroll of raise strength",rs,cs));
            }
            else if(wtype==5){
                dungObjs.push_back(new Scroll("scroll of enhance health",rs,cs));
            }
            else if(wtype ==6){
                dungObjs.push_back(new Scroll("scroll of enhance dexterity",rs,cs));
            }
            
            
        }
    
    }
}


// this sets the values of the parameters to a spot in the dungeon which is not occupied by an actor
void Dungeon::getspot(int &a, int &b){
    
    int r;
    int c;
    do
    {
        r = randInt(1, 16);
        c = randInt(1, 68);
    } while (getCellStatus(r, c) != ' ' && getCellStatus(r, c) != ')' && getCellStatus(r, c) != '&' && getCellStatus(r, c) != '>' && getCellStatus(r, c) != '?');
    
    a = r;
    b = c;
    
}

// this sets a spot in the grid to an empty character

void Dungeon::setempty(int a, int b){
    
    displayGrid[a][b] = ' ';
}

// this function takes in coordinates and a character, then sets the position in the grid to that character

void Dungeon::putchar(int a, int b, char x){
    
    displayGrid[a][b] = x;
}

// this function takes the level of the dungeon as a parameter
void Dungeon::makemonsters(int a){

    // generate the random number of monsters to be created according to the level
    int num = randInt(2, 5*(a+1)+1);
    int r;
    int c;
    
    // depending on the level, generate equal probability for each monster to be created
   
    // puch the monster onto the
    if(a==0 || a==1){
        for(int i = 0 ; i < num; i++){
            getspot(r, c);
            int motype = randInt(1, 2);
            
            // make a new monster depending on the random number generated
            if(motype==1){
                // puch the monster onto the list of monsters
                monstlist.push_back(new Goblin(r,c));
                displayGrid[r][c] = 'G';
            }
            if(motype==2){
                monstlist.push_back(new Snake(r,c));
                displayGrid[r][c] = 'S';
            }
                
        }
        
    }
    else if (a==2){
        for(int i = 0 ; i < num; i++){
            getspot(r, c);
                int motype = randInt(1, 3);
                
                if(motype==1){
                    monstlist.push_back(new Goblin(r,c));
                    displayGrid[r][c] = 'G';
                }
                else if(motype==2){
                    monstlist.push_back(new Snake(r,c));
                    displayGrid[r][c] = 'S';
                }
                else if(motype ==3){
                    monstlist.push_back(new Bogeymen(r,c));
                    displayGrid[r][c] = 'B';
            }
        }
    }
    else if (a==3 ||a==4){
        
        for(int i = 0 ; i < num; i++){
            getspot(r, c);
            int motype = randInt(1, 4);
            
            if(motype==1){
                monstlist.push_back(new Goblin(r,c));
                displayGrid[r][c] = 'G';
            }
            else if(motype==2){
                monstlist.push_back(new Snake(r,c));
                displayGrid[r][c] = 'S';
            }
            else if(motype ==3){
                monstlist.push_back(new Bogeymen(r,c));
                displayGrid[r][c] = 'B';
            }
            else if(motype == 4){
                    monstlist.push_back(new Dragon(r,c));
                    displayGrid[r][c] = 'D';
                }
            
        }
        
    }
    
}

// this function first checks which monster is being attacked by the player.
// it then calls the attack function to make sure the attack is conducted
//then it pushes the appropriate message to the list of strings passed by reference.


void Dungeon::playeraction(char d, player *pl, list<string> &a){
    
    // set r and c to the coordinates where the monster is located
    int r=0;
    int c=0;
    
    if(d=='u'){
        r = pl->r()-1;
        c= pl->c();
    }
    else if (d=='d'){
        r = pl->r()+1;
        c= pl->c();
    }
    else if (d=='l'){
        r = pl->r();
        c= pl->c()-1;
    }
    else if(d=='r'){
        r = pl->r();
        c= pl->c()+1;
    }
    
    // point x to the monster being attacked by the player.
    Actor* x = nullptr;
    
    for (list<Actor*>::iterator p = monstlist.begin();p != monstlist.end(); p++){
          
        if((*p)->r()==r && (*p)->c()==c)
            x= (*p);
    }
    
    bool sl = false;
    bool hits = false;
    

    attack(pl, x,sl,hits);
    
    string message;
    
    
    //If the monster is dead set the appropriate message, delete the monster from the maze and create a new item in that spot if needed
    // if the monster is not hit, or if the monster is hit, but not dead, set the appropriate message
    if(x->gethitp()<1){
        
        message = "The player "+ (pl->getweap())->getaction()+" the "+(pl->getweap())->getname()+ " at the "+x->getname()+" dealing a final blow.";
        
        for (list<Actor*>::iterator p = monstlist.begin();p != monstlist.end(); p++){
            if((*p)==x){
                p = monstlist.erase(p);
            }
        }
        
        //set the position in the grid where the monster died to empty
        //displayGrid[r][c] = ' ';
        
        //check if the position where the player died already had a gridcharacter
        
        bool had = true;
        //looping through the dungeon objects to check if any of them existed on that position
        for (list<gameObj*>::iterator k = dungObjs.begin();k != dungObjs.end(); k++){
            if((*k)->getro()==r&&(*k)->getcol()==c)
                had = false;
        }
        
        // checking if a stair or idol is present at the location
        if(level ==4){
            if(m_idol->row()==r&&m_idol->col()==c)
                had = false;
        }
        
        if(level<4){
            if(m_stair->row()==r&&m_stair->col()==c)
                had = false;
        }
        
        
        
        
        // if there was no objecton the location the monster died on , then
        // place a new object on the position depending on what player has died
        if(had){
            // if a dragon has died, create a new scroll and push it onto the dungeon object list
            if(x->getname()=="Dragon"){
                
                displayGrid[r][c] = '?';
                
                int chance = randInt(1, 5);
                
                if(chance ==1){
                    dungObjs.push_back(new Scroll("scroll of teleportation",r,c));
                    
                }
                else if (chance==2){
                    dungObjs.push_back(new Scroll("scroll of improve armor",r,c));
                }
                else if (chance==3){
                    dungObjs.push_back(new Scroll("scroll of raise strength",r,c));
                }
                else if (chance==4){
                    dungObjs.push_back(new Scroll("scroll of enhance health",r,c));
                }
                else if (chance==5){
                    dungObjs.push_back(new Scroll("scroll of enhance dexterity",r,c));
                }
                
            }
            // for other monsters generate a probability for which object can be dropped,
            // accordingly create a new object and push it onto the dungeon object list
            else if (x->getname()=="Goblin"){
                
                int chance = randInt(1, 3);
                if(chance ==2){
                    int chance2 =randInt(1, 2);
                    
                    if(chance2 ==1){
                        dungObjs.push_back(new Weapon("magic axe",r,c));
                        displayGrid[r][c] = ')';
                    }
                    else if (chance2==2){
                        dungObjs.push_back(new Weapon("magic fangs of sleep",r,c));
                        displayGrid[r][c] = ')';
                    }
                    
                }
                else{
                    displayGrid[r][c] = ' ';
                }
                
            }
            else if (x->getname()=="Snakewoman"){
                
                int chance = randInt(1, 3);
                
                if(chance ==2){
                    dungObjs.push_back(new Weapon("magic fangs of sleep",r,c));
                    displayGrid[r][c] = ')';
                }
                else{
                    displayGrid[r][c] = ' ';
                }
                
                
            }
            else if (x->getname()=="Bogeyman"){
                int chance = randInt(1, 10);
                
                if(chance ==2){
                    dungObjs.push_back(new Weapon("magic axe",r,c));
                    displayGrid[r][c] = ')';
                }
                else{
                    displayGrid[r][c] = ' ';
                }
                
            }
        }
        
        // delete the monster from the game
        delete x;
        
    }// if monster has been put to sleep, generate the appropriate message
    else if(sl){
                message = "The player "+ (pl->getweap())->getaction()+" the "+(pl->getweap())->getname()+ " at the "+x->getname()+" and hits."+ " Putting the "+x->getname()+" to sleep.";
    }//if monster has been hit, generate the appropriate message
    else if(hits)
    {
        message = "The player "+ (pl->getweap())->getaction()+" the "+(pl->getweap())->getname()+ " at the "+x->getname()+" and hits.";
    } // set appropriate message if the player missed the monster
    else{
        
        message = "The player "+ (pl->getweap())->getaction()+" the "+(pl->getweap())->getname()+ " at the "+x->getname()+" and misses.";
    }
    // push the messsage onto the list of messages
    a.push_back(message);
}

void Dungeon::monstersmove(player *pl, list<string> &a){
    int r = pl->prow();
    int c = pl->pcol();
    
    // looping through the list of monsters to take a turn for every monster.
    
    for (list<Actor*>::iterator p = monstlist.begin();p != monstlist.end(); p++){
        
        //check if the monster is a dragon, if so increase hitpoints is possible
        if((*p)->getname()=="Dragon"){
            int h = randInt(1, 10);
            // checking if the 1 in 10 chances is met and if the dragons health is less than its initial max health.
            if(h == 5 && ((*p)->gethitp())<((*p)->getmaxhitp())){
                int hel =(*p)->gethitp();
                (*p)->hitp(hel+1);
            }
            
        }
        
        // check if the monsters sleeptime is 0 , only then take a turn for the monster
        if((*p)->getslt()==0){
            int r_m = (*p)->r();
            int c_m = ((*p)->c());
            
            //checking if the monster has a player next to it. if so call the attack function to make sure the monster attacks the player
            if((r_m-1==r && c_m==c)||(r_m+1==r && c_m==c)||(r_m==r && c_m-1==c)||(r_m==r && c_m+1==c)){
                
                string message;
                bool sl = false;
                bool hits = false;
                
                
                attack((*p), pl, sl,hits);
                
                
                // if the player is dead after the attack, set the appropriate message
                if(pl->gethitp()<1){
                       
                       message = "The "+((*p)->getname())+" "+((*p)->getweap())->getaction()+" the "+((*p)->getweap())->getname()+ " at the Player"+" dealing a final blow. The player is dead.";
                }
                // if the player has been put to sleep , i.e if bool sl is true, display the appropriate message
                else if(sl){
                             message = "The "+((*p)->getname())+" "+((*p)->getweap())->getaction()+" the "+((*p)->getweap())->getname()+ " at the Player"+" and hits."+ " Putting the Player to sleep.";
                }// if the monster hits the player, set the appropriate message
                
                else if(hits){
                    
                    message = message = "The "+((*p)->getname())+" "+((*p)->getweap())->getaction()+" the "+((*p)->getweap())->getname()+ " at the Player"+" and hits.";
                }// if none of the above, this means that the monster missed the player.
                else{
                    
                    message = "The "+((*p)->getname())+" "+((*p)->getweap())->getaction()+" the "+((*p)->getweap())->getname()+ " at the Player"+" and misses.";
                }
                
                a.push_back(message);
            }
            // if the monster are not attacking the player, this means that the monster will either move, or not move.
            else{
                

                
                if((*p)->getname()=="Goblin"){
                    
                   // if the monster is a Goblin , call the goblinmove function
                    gobmove((*p), pl);
                    
                    
                } // if the monster is a snakewoman or bogeyman, call the appropriate move functions
                else if ((*p)->getname()=="Snakewoman"){
                    SnBmove((*p), pl);
                }
                else if ((*p)->getname()=="Bogeyman"){
                    SnBmove((*p), pl);
                }
                
            }
            
        }
        else{ // decrease the monster's sleeptime by one 
            (*p)->slt((*p)->getslt()-1);
        }
        
        
    
        
    }

    
}


// function called to move the snakewoman and Bogeyman

void Dungeon::SnBmove(Actor* monst, Actor* pl){
    
    //get the player coordinates
    int p_r = pl->r();
    int p_c = pl->c();
    
    // get the monsters coordinates
    int m_r = monst->r();
    int m_c = monst->c();
    
    // set range according to whether the monster is a snakewoman or bogeyman
    int range = 0;
    
    if(monst->getname() == "Bogeyman"){
        range = 5;
    }
    else if(monst->getname() == "Snakewoman"){
        range = 3;
    }
    
    bool present = false;
    
    // check in all the locations within range if the player is present, if so set present to true
    for(int c = m_c-range; c<m_c+range+1; c++){
        
        if(range==5){
            if(m_c-c==5||c-m_c==5){
                
                if(c<69 && c>0)
                    
                    if(displayGrid[m_r][c]=='@')
                        present= true;

            }
            if(m_c-c==4||c-m_c==4){
                
                for(int r = m_r-1; r<m_r+2; r++){
                    if(c<69 && c>0 && r<17 && r>0){
                        if(displayGrid[r][c]=='@')
                            present= true;
                    }
                }
            }
            
            if(m_c-c==3||c-m_c==3){
                
                for(int r = m_r-2; r<m_r+3; r++){
                    if(c<69 && c>0 && r<17 && r>0){
                        if(displayGrid[r][c]=='@')
                            present= true;
                    }
                }
            }
            if(m_c-c==2||c-m_c==2){
                
                for(int r = m_r-3; r<m_r+4; r++){
                    if(c<69 && c>0 && r<17 && r>0){
                        if(displayGrid[r][c]=='@')
                            present= true;
                    }
                }
            }
            if(m_c-c==1||c-m_c==1){
                
                for(int r = m_r-4; r<m_r+5; r++){
                    if(c<69 && c>0 && r<17 && r>0){
                        if(displayGrid[r][c]=='@')
                            present= true;
                    }
                }
            }
            if(m_c == c){
                for(int r = m_r-5; r<m_r+6; r++){
                    if(c<69 && c>0 && r<17 && r>0){
                        if(displayGrid[r][c]=='@')
                            present= true;
                    }
                }
            }
        }
        if(range ==3){
            if(m_c-c==3||c-m_c==3){
                
                if(c<69 && c>0){
                        if(displayGrid[m_r][c]=='@')
                            present= true;
        
                }
            }
            if(m_c-c==2||c-m_c==2){
                
                for(int r = m_r-1; r<m_r+2; r++){
                    if(c<69 && c>0 && r<17 && r>0){
                        if(displayGrid[r][c]=='@')
                            present= true;
                    }
                }
            }
            if(m_c-c==1||c-m_c==1){
                
                for(int r = m_r-2; r<m_r+3; r++){
                    if(c<69 && c>0 && r<17 && r>0){
                        if(displayGrid[r][c]=='@')
                            present= true;
                    }
                }
            }
            if(m_c == c){
                for(int r = m_r-3; r<m_r+4; r++){
                    if(c<69 && c>0 && r<17 && r>0){
                        if(displayGrid[r][c]=='@')
                            present= true;
                    }
                }
            }
        }
        
    }
    
    
    // if the player is in range , move the monster closer to the player
    if(present){
    
        // if the player is below the monster and the monster can move one row down do so
        if((m_r<p_r)&&(displayGrid[m_r+1][m_c]==' ' || displayGrid[m_r+1][m_c]== '>' || displayGrid[m_r+1][m_c]=='?' || displayGrid[m_r+1][m_c]=='&' || displayGrid[m_r+1][m_c]==')')){
            
            setempty(m_r,m_c);
            monst->setpos(m_r+1, m_c);
            putchar(m_r+1, m_c, monst->getchar());
            
        }  // if the player is above the monster and the monster can move one row up do so
        else if (((m_r>p_r)&&(displayGrid[m_r-1][m_c]==' ' || displayGrid[m_r-1][m_c]== '>' || displayGrid[m_r-1][m_c]=='?' || displayGrid[m_r-1][m_c]=='&' || displayGrid[m_r-1][m_c]==')'))){
            
            setempty(m_r,m_c);
            monst->setpos(m_r-1, m_c);
            putchar(m_r-1, m_c, monst->getchar());
            
        }// if the player is to the right of the monster and the monster can move right do so
        else if(((m_c<p_c)&&(displayGrid[m_r][m_c+1]==' ' || displayGrid[m_r][m_c+1]== '>' || displayGrid[m_r][m_c+1]=='?' || displayGrid[m_r][m_c+1]=='&' || displayGrid[m_r][m_c+1]==')'))){
            
            setempty(m_r,m_c);
            monst->setpos(m_r, m_c+1);
            putchar(m_r, m_c+1, monst->getchar());
            
        }// if the player is to the left of the monster and the monster can move left do so
        else if(((m_c>p_c)&&(displayGrid[m_r][m_c-1]==' ' || displayGrid[m_r][m_c-1]== '>' || displayGrid[m_r][m_c-1]=='?' || displayGrid[m_r][m_c-1]=='&' || displayGrid[m_r][m_c-1]==')'))){
            
            setempty(m_r,m_c);
            monst->setpos(m_r, m_c-1);
            putchar(m_r, m_c-1, monst->getchar());
            
        }
        
    }

    
    
}

void Dungeon::gobmove(Actor *monst, Actor *pl){
    {
        
        //get the player coordinates
        int p_r = pl->r();
        int p_c = pl->c();
        
        // get the monsters coordinates
        int m_r = monst->r();
        int m_c = monst->c();
        
        
        int range = 0;
        
        if(monst->getname() == "Goblin"){
            range = 5;
        }
        
        bool present = false;
        
        // check in all the locations within range if the player is present, if so set present to true
        for(int c = m_c-range; c<m_c+range+1; c++){
            
            if(range==5){
                if(m_c-c==5||c-m_c==5){
                    
                    if(c<69 && c>0)
                        
                        if(displayGrid[m_r][c]=='@')
                            present= true;

                }
                if(m_c-c==4||c-m_c==4){
                    
                    for(int r = m_r-1; r<m_r+2; r++){
                        if(c<69 && c>0 && r<17 && r>0){
                            if(displayGrid[r][c]=='@')
                                present= true;
                        }
                    }
                }
                
                if(m_c-c==3||c-m_c==3){
                    
                    for(int r = m_r-2; r<m_r+3; r++){
                        if(c<69 && c>0 && r<17 && r>0){
                            if(displayGrid[r][c]=='@')
                                present= true;
                        }
                    }
                }
                if(m_c-c==2||c-m_c==2){
                    
                    for(int r = m_r-3; r<m_r+4; r++){
                        if(c<69 && c>0 && r<17 && r>0){
                            if(displayGrid[r][c]=='@')
                                present= true;
                        }
                    }
                }
                if(m_c-c==1||c-m_c==1){
                    
                    for(int r = m_r-4; r<m_r+5; r++){
                        if(c<69 && c>0 && r<17 && r>0){
                            if(displayGrid[r][c]=='@')
                                present= true;
                        }
                    }
                }
                if(m_c == c){
                    for(int r = m_r-5; r<m_r+6; r++){
                        if(c<69 && c>0 && r<17 && r>0){
                            if(displayGrid[r][c]=='@')
                                present= true;
                        }
                    }
                }
            }
            
            
        }
        
        
        // if the player is in range , move the monster closer to the player
        if(present){
        
            // if the player is below the monster and the monster can move one row down do so
            if((m_r<p_r)&&(displayGrid[m_r+1][m_c]==' ' || displayGrid[m_r+1][m_c]== '>' || displayGrid[m_r+1][m_c]=='?' || displayGrid[m_r+1][m_c]=='&' || displayGrid[m_r+1][m_c]==')')){
                
                setempty(m_r,m_c);
                monst->setpos(m_r+1, m_c);
                putchar(m_r+1, m_c, monst->getchar());
                
            }  // if the player is above the monster and the monster can move one row up do so
            else if (((m_r>p_r)&&(displayGrid[m_r-1][m_c]==' ' || displayGrid[m_r-1][m_c]== '>' || displayGrid[m_r-1][m_c]=='?' || displayGrid[m_r-1][m_c]=='&' || displayGrid[m_r-1][m_c]==')'))){
                
                setempty(m_r,m_c);
                monst->setpos(m_r-1, m_c);
                putchar(m_r-1, m_c, monst->getchar());
                
            }// if the player is to the right of the monster and the monster can move right do so
            else if(((m_c<p_c)&&(displayGrid[m_r][m_c+1]==' ' || displayGrid[m_r][m_c+1]== '>' || displayGrid[m_r][m_c+1]=='?' || displayGrid[m_r][m_c+1]=='&' || displayGrid[m_r][m_c+1]==')'))){
                
                setempty(m_r,m_c);
                monst->setpos(m_r, m_c+1);
                putchar(m_r, m_c+1, monst->getchar());
                
            }// if the player is to the left of the monster and the monster can move left do so
            else if(((m_c>p_c)&&(displayGrid[m_r][m_c-1]==' ' || displayGrid[m_r][m_c-1]== '>' || displayGrid[m_r][m_c-1]=='?' || displayGrid[m_r][m_c-1]=='&' || displayGrid[m_r][m_c-1]==')'))){
                
                setempty(m_r,m_c);
                monst->setpos(m_r, m_c-1);
                putchar(m_r, m_c-1, monst->getchar());
                
            }
            
        }

        
        
    }
}


void Dungeon::attack(Actor* attacker, Actor* defender,bool& sl, bool& hits){
    
    //calculate attacker points and defender points to check if the attacker hits the defender
     int attackerPoints = attacker->getdex()+ (attacker->getweap())->getdex();
     int defenderPoints = defender->getdex() + defender->getar();
    
    // calculate damage points
    int damagePoints = randInt(0, attacker->getstre() + (attacker->getweap())->getdmgamt() - 1);
    
    //check if the attacker hits the defender
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)){
        hits = true;
        // calculate damage points and reduce the defenders hitpoints accordingly
        int hel =(defender->gethitp())-damagePoints;
        defender->hitp(hel);
        
        // check if the weapon of the attacker is magic fangs of sleep, if check if the defender has been put to sleep
        
        if((attacker->getweap())->getname()=="magic fangs of sleep"){
            int s = randInt(1, 5);
            
            if(s==3){
                
              int sleept = randInt(2, 6);
                
                // if defender's sleep time should been increased ,increase it and set bool sl to true
                if(defender->getslt()<sleept){
                    
                    defender->slt(sleept);
                    sl = true;
                }
                    
            }
            
        }
        
    }
    
    
    
}


