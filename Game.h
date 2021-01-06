// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <list>
#include <string>
using namespace std; 
//#include "Dungeon.h"

// You may add data members and other member functions to this class.
class Dungeon;
class player; 
class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
    void end();
    void inventory();
    void displaymessages(); 
    
private:
    // private variables to store the level and goblin smell distance

    int level ; 
    int gobsmell ;
    
    // pointers to the dungeon and player object
    Dungeon* m_dung;
    player* m_player;
    
    // list of strings used to store the messages
    list<string> messages;
    
};

#endif // GAME_INCLUDED
