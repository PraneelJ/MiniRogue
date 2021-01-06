// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "player.h"
#include "Dungeon.h"
#include <iostream>
using namespace std;
#include "stairs.h"

// Game household functions

Game::Game(int goblinSmellDistance)
{
    // start the game with level 0, set the goblin smell distance and create a new dungeon
    level = 0;
    gobsmell = goblinSmellDistance;
    m_dung = new Dungeon(level, gobsmell);
    
    
    // create the player object and give it valid coordinates in the dungeon
    
    int r;
    int c;
    do
    {
        r = randInt(1, 16);
        c = randInt(1, 68);
    } while (m_dung->getCellStatus(r, c) != ' ' && m_dung->getCellStatus(r, c) != ')' && m_dung->getCellStatus(r, c) != '&' && m_dung->getCellStatus(r, c) != '>' && m_dung->getCellStatus(r, c) != '?');
    
  m_player = new player( r, c);
    m_dung->putchar(r, c, '@');
      
    
    
    
}

Game::~Game(){
    // delete the dungeon and the player after the game is over
    
    delete m_dung;
    delete m_player;
}
 

//====================================================================================
void Game::play()
{ // display the dungeon
    m_dung->display(m_player);
    // input a character from the user
    char dir =getCharacter();
    
    // loop while the user does not enter a 'q'
    while (dir != 'q'){
        
        // increase the players health
        int hi = randInt(1, 10);
        // checking if the 1 in 10 chances is met and if the player's health is less than its initial max health.
        // if conditions are met , increase the players health by 1
        if(hi == 5 && ((m_player)->gethitp())<((m_player)->getmaxhitp())){
            int hel =(m_player)->gethitp();
            (m_player)->hitp(hel+1);
        }
        
        
       //check if the player's sleep time is 0 , if so allow the player to make a move
      if(m_player->getslt()==0){
        // increasing hitpoints and strength as the player has cheated.
        if(dir=='c'){
            m_player->stre(9);
            m_player->hitp(50);
        }
        //================================================================================
        
          bool move = false;
        // checking if dir is moving the player. and if it is moving the player, then bool move is set to true;
        if (dir == ARROW_UP || dir == ARROW_DOWN || dir == ARROW_LEFT || dir == ARROW_RIGHT){
            
            move = m_player->playermove(dir, m_dung);
            
        }
        //================================================================================================
        
        
        // checking if the player has moved already, if not then 
        // checking if the player's move is attacking a monster ==========================================
        
        // checking if the cell in direction the player wants to move in contains a monster
        // if it does, calling the player attack function in the dungeon class.
          if(!move){
              
        if (dir == ARROW_UP || dir == ARROW_DOWN || dir == ARROW_LEFT || dir == ARROW_RIGHT){
            
            if(dir == ARROW_UP && (m_dung->getCellStatus(m_player->r()-1, m_player->c()) == 'G'||m_dung->getCellStatus(m_player->r()-1, m_player->c()) == 'S'|| m_dung->getCellStatus(m_player->r()-1, m_player->c()) == 'D'||m_dung->getCellStatus(m_player->r()-1, m_player->c()) == 'B')){
                m_dung->playeraction('u', m_player, messages);
            }
                
                
            if(dir == ARROW_DOWN && (m_dung->getCellStatus(m_player->r()+1, m_player->c()) == 'G'||m_dung->getCellStatus(m_player->r()+1, m_player->c()) == 'S'|| m_dung->getCellStatus(m_player->r()+1, m_player->c()) == 'D'||m_dung->getCellStatus(m_player->r()+1, m_player->c()) == 'B')){
            m_dung->playeraction('d', m_player, messages);

            }
            
                
            if(dir == ARROW_LEFT && (m_dung->getCellStatus(m_player->r(), m_player->c()-1) == 'G'||m_dung->getCellStatus(m_player->r(), m_player->c()-1) == 'S'|| m_dung->getCellStatus(m_player->r(), m_player->c()-1) == 'D'||m_dung->getCellStatus(m_player->r(), m_player->c()-1) == 'B')){
                m_dung->playeraction('l', m_player, messages);
            }
            
            if(dir == ARROW_RIGHT && (m_dung->getCellStatus(m_player->r(), m_player->c()+1) == 'G'||m_dung->getCellStatus(m_player->r(), m_player->c()+1) == 'S'|| m_dung->getCellStatus(m_player->r(), m_player->c()+1) == 'D'||m_dung->getCellStatus(m_player->r(), m_player->c()+1) == 'B')){
                m_dung->playeraction('r', m_player, messages);
                
            }
            
        }
        
          }
        //================================================================================================
        
        
        
        
        // checking if the player has typed > and can descend into a deeper level
        // call the stairpos function to check if the player is on the stairs, if so desced to new level
      if (dir== '>')
          if(m_dung->stairpos(m_player->prow(), m_player->pcol())){
              // increase the level, delete the old dungeon and create a new dungeon with a higher level
              level++;
              delete m_dung;
              m_dung = new Dungeon(level,gobsmell);
              
              // assign new position coordinates to the player
              int r;
              int c;
              do
              {
                  r = randInt(1, 16);
                  c = randInt(1, 68);
              } while (m_dung->getCellStatus(r, c) != ' ' && m_dung->getCellStatus(r, c) != ')' && m_dung->getCellStatus(r, c) != '&' && m_dung->getCellStatus(r, c) != '>' && m_dung->getCellStatus(r, c) != '?');
              
              m_player->psetpos(r, c);
              m_dung->putchar(r, c, '@');
              
              // display the new dungeon, get a character from the user and continue
              m_dung->display(m_player);
              dir = getCharacter();
              continue;
          }
        
        //================================================================================================
        
        //check if a player has picked up an object from the dungeon
        if (dir== 'g'){
            string n = m_dung->pickobJ(m_player);
            // use the pickobJ function to determine whether the player has picked up an object from the dungeon
            //depending on the string returned by the function, add a message to the message list.
            if(n!="none"&&n!="space"){
                messages.push_back("you pick up a "+n);

            }
            else if(n=="space"){
                messages.push_back("Your knapsack is full; you can't pick that up.");
            }
        }
        
        //==============================================================================================================
        
        
        // checking if the player wants to display the inventory
        
            string message;
             
             // now checking if player is weilding a weapon
                         if(dir== 'w'){
                             m_player->inventory(); //display the inventory
                         string x = m_player->wieldweapon();
                             // depending on the string returned by function weild weapon, create an appropriate message
                             int dec = 0;
                             if(x=="none"){
                                 dec = 1;
                             }
                             else if(x== "short sword"){
                               message = "You are wielding " + x;
                             }
                             else if( x == "long sword")
                             {
                                message = "You are wielding " + x;
                             }
                             else if(x=="mace"){
                              message = "You are wielding " + x;
                             }
                             else if(x=="magic axe"){
                                 
                                message = "You are wielding " + x;
                             }
                         
                             else if(x=="magic fangs of sleep"){
                                 message = "You are wielding " + x;
                             }
                             else{
                                 message = "You can’t wield "+ x;
                             }
                             
                             
                    // push a message onto the list only if player uses an object or attempts to use a wrong object
                          if(dec ==0){
                              messages.push_back(message);
                             
                             }
                         }
             
                         // now checking if the player will read a scroll
                         if(dir== 'r'){
                             m_player->inventory();//display the inventory
                         string x = m_player->readscroll();
                             // depending on the string returned by function read scroll, create an appropriate message
                             int dec = 0;
                             
                             if(x=="none"){
                                 dec = 1;
                             } // if the scroll is of teleportation, give the player a new valid position on the grid
                             else if(x== "scroll of teleportation. You feel your body wrenched in space and time."){
                                 int ro;
                                 int co;
                                 m_dung->getspot(ro, co);
                                 m_dung->setempty(m_player->prow(), m_player->pcol());
                                 m_player->psetpos(ro, co);
                                 m_dung->putchar(ro, co, '@');
                                 
                                   message = "You read a scroll called "+ x;
                                 }
                                 else if( x == "scroll of improve armor. Your armor glows blue.")
                                 {
                                    message = "You read a scroll called "+ x;
                                 }
                                 else if(x=="scroll of raise strength. Your muscles bulge."){
                                  message = "You read a scroll called "+ x;
                                 }
                                 else if(x=="scroll of enhance health. You feel your heart beating stronger."){
                                     
                                    message = "You read a scroll called "+ x;
                                 }
                             
                                 else if(x=="scroll of enhance dexterity. You feel like less of a klutz."){
                                     message = "You read a scroll called "+ x;
                                 }
                                 else{
                                     message = "You can’t read a " + x;
                                 }
             
                         // now add a message to the list only if player uses an object or attempts to use a wrong object
                          if(dec ==0){
                              messages.push_back(message);
            
                             }
                         }
                         // display the players inventory and input any character
                         if(dir=='i'){
                             m_player->inventory();
                             getCharacter();
                             
                         }
        
         //==============================================================================================================
        
    
        // checking if the player has typed g and has picked up a golden idol
        if (dir== 'g')
        if(m_dung->idolpos(m_player->prow(), m_player->pcol())){
            //if the player picked the idol, display the appropriate message and call the end() function
            cout<< "Congratulations! You have won the game by picking up the idol"<<endl;
            end();
            break;
        }
      }
      else{ // if the player was asleep, then reduce the player's sleep time
          m_player->slt(m_player->getslt()-1);
      }
    
        
        //Monsters move now ================================
         // call function to let monsters take their move
        m_dung->monstersmove(m_player, messages);
        
        //========================================================
        // display the dungeon and then display all the messages by calling the displaymessages function
        m_dung->display(m_player);
        displaymessages();
        // if player's hitpoints are negative, i.e. the player is dead, call the end() function
        if(m_player->gethitp()<1){
            end();
            break;
        }
        // input a new character
        dir = getCharacter();
        // if the player is asleep and the user types in a 'q', the game should not quit thus, change the value of 'dir' to avoid this
        if(dir=='q'&&m_player->getslt()>0)
            dir = 'y';
    }
   
        
}
// this function output all the messages that need to be displayed.
void Game::displaymessages(){
    // loop through the message list and erase each message after outputting
     for (list<string>::iterator p = messages.begin();p != messages.end(); ){
         cout<<(*p)<<endl;
         p = messages.erase(p);
     }
}
    
// this function is called whenever the player dies or when the player picks up the idol and wins
// it takes in characters till the user types in a 'q' after which the game is terminated
void Game::end(){
    cout << "Press q to exit game." << endl;
    char dirf =getCharacter();
    
    while (dirf != 'q'){
        dirf = getCharacter();
    
    }

}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
