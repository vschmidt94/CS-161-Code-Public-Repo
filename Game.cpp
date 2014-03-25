/* 
 * File:        Game.cpp
 * Author:      C. Vaughan Schmidt
 *
 * Created on March 6, 2014, 2:59 PM
 * 
 * For: CS161 - Winter 2014 - FINAL PROJECT SUBMISSION  
 * 
 * Game.cpp is encapsulation of Game object
 * 
 * Game object contains the core functionality of a BattleShip-style
 * game
 */

#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

Game::Game() {
    // Default constructor
    // Initializes basic variables, calls initGrid() to build
    // and initialize the playing grid, then calls placeBoats()
    // to place hidden boats on grid.
    
    difficulty = 1;
    debug = false;
    exitFlag = false;

    // boat sizes
    tenderSize = 2;
    destroyerSize = 3;
    cruiserSize = 4;
    battleshpSize = 5;
    carrierSize = 6;

    initGrid();
    placeBoats();
}

Game::Game(int diff, bool d) {
    // Overloaded constructor
    // **************************************************************
    // ** FUNCTIONAL REQUIREMENT 17 - FUNCTION OVERLOADING         **
    // **************************************************************
    
    // boat sizes
    tenderSize = 2;
    destroyerSize = 3;
    cruiserSize = 4;
    battleshpSize = 5;
    carrierSize = 6;
    
    debug = d;
    exitFlag = false;
    difficulty = diff;
    initGrid();
    placeBoats();
}

Game::~Game() {
    // Destructor
}

// Accessor Functions

int Game::getDifficulty() {
    // returns difficulty level
    return difficulty;
}

int Game::getRows() {
    // returns number of rows in use in current game
    return rows;
}

int Game::getCols() {
    // returns number of columns in use in current game
    return cols;
}

// Mutator Functions

void Game::setDifficulty(int diff) {
    // sets difficulty level of current game
    difficulty = diff;
    return;
}

void Game::setRows(int r) {
    // sets rows for current game
    rows = r;
    return;
}

void Game::setCols(int c) {
    // sets cols for current game
    cols = c;
    return;
}

// Utility Functions

void Game::initGrid() {
    // Function Game::initGrid()
    // sets basic game variables based on difficulty, then 
    // calls makeGrid to build and populate the grid
    if (difficulty == 1) {
        rows = 8;
        cols = 8;
        boats = 3;
    } else if (difficulty == 2) {
        rows = 10;
        cols = 10;
        boats = 4;
    } else {
        rows = 12;
        cols = 12;
        boats = 5;
    }
    grid = makeGrid(rows, cols);
    
    if(debug) {
        cout << RED << "DEBUG: in initGrid() :"
                << "\n Grid has been populated with water.\n"
                << "[ENTER] to view\n";
        pressEnter();
        showGrid();
        pressEnter();
    }
    return;
}

void Game::placeBoats() {
    // Computer opponent randomly places a selection of boats
    // on current playing grid.  Number of boats determined by 
    // difficulty level.  Calls placeBoat() to place each 
    // individual boat as needed.

    if (difficulty >= 3) {
        // Difficulty 3 adds a Carrier
        placeBoat(carrierSize); // place Carrier
    }
    
    if (difficulty >= 2) {
        // Difficulty 2 adds a Cruiser
        placeBoat(cruiserSize); // place Cruiser
    }

    if (difficulty >= 1) {
        // All difficulties get at least 3 boats
        placeBoat(battleshpSize); // place Battleship
        placeBoat(destroyerSize); // place Destroyer
        placeBoat(tenderSize); // place Tender
    }
}

void Game::placeBoat(int size) {
    // Function Game::placeBoat()
    // randomly places a boats of length size on the grid
    // boat position is generated as random grid loc row, col for the bow
    // of the boat and a random direction (1, 2, 3, 4).
    // direction is which way the boat is oriented on grid: example:
    // direction 1 = boat facing "North" (towards top of grid)
    // Selected position is then checked for conflicts:
    // a) boat's position(s) must not overflow array bounds
    // b) boat must not share a location with a previously located boat
    
    int boatRow, boatCol, boatDir;
    bool validPos = false;
    
    do {
    boatRow = (rand() % rows) + 1;
    boatCol = (rand() % cols) + 1;
    boatDir = (rand() % 4) + 1;
    
    if(debug) {
        cout << RED << "DEBUG : in placeBoat() do..loop \n";
        cout << "boatRow = " << boatRow << endl;
        cout << "boatCol = " << boatCol << endl;
        cout << "boatDir = " << boatDir << endl;
        cout << "size = " << size << endl;
        cout << "[ENTER]\n" << RESET;
        pressEnter();
    }
    
    validPos = validatePos(boatRow, boatCol, size, boatDir);
    } while (!validPos);
    
    // Boat's location has been validated, place boat on grid
    if(debug) {
        cout << RED << "DEBUG : in placeBoat() : VALIDATED \n" 
                << "Boat's location has been validated, now placing on grid.\n";
        cout << "boatRow = " << boatRow << endl;
        cout << "boatCol = " << boatCol << endl;
        cout << "boatDir = " << boatDir << endl;
        cout << "[ENTER]\n" << RESET;
        pressEnter();
    }
    
    if(boatDir == 1) {
        for(int i = 0; i < size; ++i) {
            grid[boatRow + i - 1][boatCol - 1] = 'B';
            if(debug) {
                showGrid();
                pressEnter();
            }
        }
    }
    if(boatDir == 2) {
        for(int i = 0; i < size; ++i) {
            grid[boatRow - 1][boatCol - i - 1] = 'B';
            if(debug) {
                showGrid();
                pressEnter();
            }
        }
    }
    if(boatDir == 3) {
        for(int i = 0; i < size; ++i) {
            grid[boatRow - i - 1][boatCol - 1] = 'B';
            if(debug) {
                showGrid();
                pressEnter();
            }
        }
    }
    if(boatDir == 4) {
        for(int i = 0; i < size; ++i) {
            grid[boatRow - 1][boatCol + i - 1] = 'B';
            if(debug) {
                showGrid();
                pressEnter();
            }
        }
    }
}

bool Game::validatePos(int row, int col, int size, int dir) {
    // *******************************************************
    // ** FUNCTIONAL REQUIREMENT 7 - CONDITIONALS           **
    // ** Conditionals used pervasively in this function    **
    // ** FUNCTIONAL REQUIREMENT 9 - LOOPS                  **
    // ** Loops used to check that new boat will not hit    **
    // ** an existing boat on the grid                      **
    // *******************************************************
    if(debug) {
        cout << RED << "DEBUG: Entering validatePos() : \n"
             << "row = " << row << " / rows = " << rows << endl
             << "col = " << col << " / cols = " << cols << endl
             << "size = " << size << endl
             << "dir = " << dir << endl
             << "[ENTER]\n" << RESET;
        pressEnter();
    }
    
    // if boat direction 1 (north), can't be near last rows
    if(dir == 1 && row > (rows - size)) {
        // if boat direction 1 (north), can't be near last rows
        return false;
    }
    
    if(dir == 2 && col < size) {
        // if boat direction 2 (east), can't be near first col
        return false;
    }
    
    if(dir == 3 && row < size) {
        // if boat direction 3 (south), can't be near first row
        return false;
    }
    
    if((dir == 4) && (col > (cols - size))) {
        // if boat direction 4 (west), can't be near last col
        return false;
    }
    
    if(debug) {
        cout << RED << "DEBUG: in validatePos(): position will "
                << "not overflow array, now checking for \n"
                << "conflict with other boats...\n"
                << "[ENTER]\n" << RESET;
        pressEnter();
    }
    
    // if this point reached, boat will fit on grid at random location
    // without overflowing the array.  Now check that there is not
    // already another boat in the same coordinates
    if(dir == 1) {
        for(int i = 0; i < size; ++i) {
            if(grid[row + i - 1][col - 1] == 'B') {
                return false;   // already a boat on this coordinate, invalid
            }
        } 
    }
    if(dir == 2) {
        for(int i = 0; i < size; ++i) {
            if(grid[row - 1][col - i - 1] == 'B') {
                return false;   // already a boat on this coordinate, invalid
            }
        } 
    }
    if(dir == 3) {
        for(int i = 0; i < size; ++i) {
            if(grid[row - i - 1][col - 1] == 'B') {
                return false;   // already a boat on this coordinate, invalid
            }
        } 
    }
    if(dir == 4) {
        for(int i = 0; i < size; ++i) {
            if(grid[row - 1][col + i - 1] == 'B') {
                return false;   // already a boat on this coordinate, invalid
            }
        } 
    }
    
    if(debug) {
        cout << RED << "DEBUG : returning TRUE from validatePos() \n" 
             << "row = " << row << " / rows = " << rows << endl
             << "col = " << col << " / cols = " << cols << endl
             << "size = " << size << endl
             << "dir = " << dir << endl
             << "[ENTER]\n" << RESET;
        pressEnter();
    }
    
    return true;
}

char** Game::makeGrid(int rows, int cols) {
    // Function Game::makeGrid()
    // Builds a dynamic 2-D Array of size rows x cols
    // populates the array with water chars '+'
    // ***********************************************************
    // ** FUNCTIONAL REQUIREMENT #20 - MULTI-DIM ARRAY +        **
    // ** FUNCTIONAL REQUIREMENT #21 - DYNAMICALLY DECL ARRAY   **
    // ** FUNCTIONAL REQUIREMENT #25 - POINTER TO ARRAY         **
    // ** (Actually a pointer to a array of pointers to do a    **
    // **  2-D Dynamic Array                                    **
    // ** So dawg, I heard you liked dynamic arrays and         **
    // ** multi-dimensional arrays, so I got you a              **
    // ** a dynamically-allocated multi-dimensional array.      **
    // ** So, yeah...  it's all here.                           **
    // *********************************************************** 
    char** theGrid = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        theGrid[i] = new char[cols];
    }

    // Fill all grid elements with water ('+' char)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            theGrid[i][j] = '+';
        }
    }
    
    if(debug) {
        cout << RED << "DEBUG: in makeGrid() :"
                << "\nGrid has been populated. \n"
                << "[ENTER] \n" << RESET;
        
        pressEnter();
        
    }

    return theGrid;
}

void Game::showGrid() {
    // Outputs the playing grid to the console.
    
    cout << CLEAR;

    if (debug) {
        cout << RED << "DEBUG: Entering showGrid() function.\n"
                << "int rows = " << rows << endl
                << "int cols = " << cols << endl
                << "int difficulty = " << difficulty << endl
                << "[ENTER]" << RESET;
        pressEnter();
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // *******************************************************
            // ** FUNCTIONAL REQUIREMENT 7, 9 - CONDITIONALS, LOOPS ** 
            // *******************************************************
            // print the header row if needed
            if (row == 0 && col == 0) {
                cout << "\t";
                for (int h = 0; h < cols; h++) {
                    // ************************************************
                    // ** FUNCTIONAL REQUIREMENT 6 - TYPE CASTING    **
                    // ************************************************
                    cout << "| " << static_cast<char> (h + 65) << " ";
                }
                cout << "| \n";
                cout << "--------";
                for (int h = 0; h < cols; h++) {
                    cout << "|---";
                }
                cout << "| \n";
            }

            // print a normal row
            if (col == 0) {
                cout << "    " << (row + 1) << "\t|";
            }
            cout << " ";
            // *******************************************************
            // ** FUNCTIONAL REQUIREMENT 20 - 2D ARRAY              **
            // *******************************************************
            if (grid[row][col] == '+') {
                // cell is water or unhit boat
                cout << BG_BLUE << CYAN << grid[row][col] << RESET;
            } else if (grid[row][col] == 'B' && debug) {
                // debug = show boats and cell is boat
                cout << WHITE << grid[row][col] << RESET;
            } else if (grid[row][col] == 'B' && !debug) {
                // cell is a boat, but !debug
                cout << BG_BLUE << CYAN << '+' << RESET;
            } else if (grid[row][col] == 'O') {
                // cell has recorded a miss
                cout << BG_WHITE << CYAN << grid[row][col] << RESET;
            } else {
                // cell must be a hit boat
                cout << BG_RED << WHITE << "*" << RESET;
            }
            cout << " |";
        }

        // print the separator row
        cout << "\n--------";
        for (int h = 0; h < cols; h++) {
            cout << "|---";
        }
        cout << "| \n";
    }
}

void Game::pressEnter() {
    // Utility function to look for ENTER key being pressed
    string temp;
    getline(cin, temp);
}

void Game::deleteDynArray() {
    // Deletes the 2-D Dynamic Array from heap memory
    // TODO
}

int Game::nextMove() {
    // Function nextMove():
    // gets the player's next move and validates the move

    bool validMove = false;

    
    do {
        cout << "ENTER TARGET COORDINATES AS ROW,COL OR 'EXIT' TO QUIT \n";
        cout << "(Example: 7,A) => ";
        validMove = getTarget();
    } while (!validMove);
    
    if(exitFlag) {
        return 99;  // 99 is the code to exit the game
    }
    
    int attackResult = markGrid();
    if(attackResult == 1) {
        cout << WHITE << "MISS\n" << RESET;
    }
    if(attackResult == 2) {
        cout << RED << "HIT!\n" << RESET;
    }
    
    cout << "[ENTER]";
    pressEnter();
    
    return attackResult;
}

bool Game::getTarget() {
    // Function getTarget():
    // gets user input as cin in the form of row,col

    string target;
    getline(cin, target);
    
    // exit if needed 
    if(target == "EXIT" || target == "exit") {
        exitFlag = true;
        return true;
    }
    
    // input must have comma
    int found = target.find(',');
    if(found == string::npos) {
        // no comma
        return false;
    }
    
    // validate entry as a valid target on grid.
    istringstream ss(target);
    string rowStr;
    string colStr;
    
    getline(ss, rowStr, ',');
    getline(ss, colStr);
    
    if(colStr.length() > 1) {
        // the column string should always be a single alpha char
        return false; 
    }
    
    
    colStr = stringToUpper(colStr); // make sure column is uppercase
    
    moveRow = atoi(rowStr.c_str());  // converts rowStr to int value
    moveCol = int(colStr.at(0)) - 64;           // converts col
    
    if(moveRow < 1 || moveRow > rows || moveCol < 1 || moveCol > cols) {
        return false;
    }
    
    if(debug) {
        cout << RED << "DEBUG: in getTarget():\n"
                << "string target = " << target << endl
                << "rowStr = " << rowStr << " / moveRow = " << moveRow << endl
                << "colStr = " << colStr << " / moveCol = " << moveCol << endl
                << "[ENTER]\n" << RESET;
        pressEnter();
    }
    
    return true;
}


int Game::markGrid() {
    // Function markGrid():
    // Marks the user's move on the grid / records hits and stats
    if(grid[moveRow - 1][moveCol - 1] == '+') {
        // record a miss
        grid[moveRow - 1][moveCol - 1] = 'O';
        return 1;
    }
    
    if(grid[moveRow - 1][moveCol - 1] == 'B') {
        // record a hit boat
        grid[moveRow - 1][moveCol - 1] = 'X';
        return 2;
    }
    
    // only other option would be to hit an already marked spot
    return 1;
}

string Game::stringToUpper(string inString) {
    // function stringToUpper(string) 
    // returns a uppercase version of string.
    for (string::iterator p = inString.begin(); inString.end() != p; ++p) {
        *p = toupper(*p);
    }
    return inString;
}
