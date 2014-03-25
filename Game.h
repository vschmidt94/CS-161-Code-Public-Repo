/* 
 * File:        Game.h
 * Author:      C. Vaughan Schmidt
 *
 * Created on March 6, 2014, 3:01 PM
 *
 * For: CS161 - Winter 2014 - FINAL PROJECT
 * 
 * Description: Game is the main game object for Final Project Battleship
 *              type game.
 */

// Includes
#include <iostream>
#include <string>

// Definitions
#define CLEAR   "\033[2J"       /* Screen Clear Code */
#define RESET   "\033[0m"       /* Resets ASCII codes */
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */ 
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BG_RED  "\033[41m"      /* Backgroud Red    */
#define BG_BLUE "\033[44m"      /* Background Blue  */
#define BG_WHITE "\033[47m"     /* Background White */

using namespace std;


#ifndef GAME_H
#define	GAME_H

class Game{
public:
    // Constructor
    Game();
    
    // Constructor - Overload
    Game(int, bool);
    
    // Destructor
    ~Game();
    
    // Accessors
    int getDifficulty();
    int getRows();
    int getCols();
    
    // Mutators
    void setDifficulty(int);
    void setRows(int);
    void setCols(int);
    void setDebug(bool);
    
    // Output
    void showGrid();
    void pressEnter();
    
    // Misc
    void deleteDynArray();
    int nextMove();
    bool exitFlag;
    
private:
    bool debug;
    int difficulty;
    int rows;
    int cols;
    int boats;
    string target;
    int moveRow;
    int moveCol;
    bool hit;
    bool validMove;
    
    // boat sizes
    int tenderSize;
    int destroyerSize;
    int cruiserSize;
    int battleshpSize;
    int carrierSize;
    
    char** grid;  // 2-D Dynamically allocated grid
    
    void initGrid();   // Initializes the game grid based on difficulty
    
    char** makeGrid(int, int); // returns 2-D playing grid of size rows x cols
    
    int bitwiseRecursiveAdder(int, int); // Adds two ints
    
    void placeBoats(); // places boats on the grid based on difficulty
    void placeBoat(int);  // places a single boat
    bool validatePos(int, int, int, int); // validates a boat's grid placement
    bool getTarget();  // gets user input for next move
    int markGrid(); // records the player's move on the grid
    string stringToUpper(string);
                          
 
};

#endif	/* GAME_H */

