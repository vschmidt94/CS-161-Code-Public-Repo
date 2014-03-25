/* 
 * File:        BattleShip.cpp
 * Author:      C. Vaughan Schmidt
 *
 * Created on March 6, 2014, 2:59 PM
 * 
 * For: CS161 - Winter 2014 - FINAL PROJECT SUBMISSION  
 * 
 */

#include <cstdlib>
#include <limits.h>
#include <iostream>
#include <bitset>
#include <cstring>
#include <string>
#include <locale>
#include <unistd.h>             // for usleep function
#include "Game.h"

// definitions
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

// Structure to keep track of game statistics

struct Stats {
    string pName;
    int hits;
    int misses;
};

// Function Prototypes

void welcome(int &, string &, bool);
// Displays the welcome message

void teletype(string);
// Outputs string to terminal with teletype-like effect

void teletype(string, int);
// Overload version of teletype - Optional in parameter can be used to
// adjust speed for effect.

string stringToUpper(string);
// returns an uppercase version of the string

int challenge(bool);
// Use questions about binary and 2's complement to set difficulty level

int bitwiseRecursiveAdder(int, int);
// adds two ints using bitwise recursion

int getIntInput(int, int, bool);
// gets an integer input between min and max values

void pressEnter();
// Looks for enter key to be pressed to continue

void endGame(Stats *, Game *);
// shuts down game

int main(int argc, char** argv) {

    // Declare and initialize variables
    bool debug = false;
    bool gameOn = true;
    int seed = 0;

    // Declare game stats structure and initialize members
    Stats gameStats;
    gameStats.pName = " ";
    gameStats.hits = 0;
    gameStats.misses = 0;
    
    // Make a pointer to gameStats struct
    // ********************************************************
    // ** FUNCTIONAL REQUIREMENT 26 - POINTER TO STRUCT      **
    // ** Note: Only reason for doing this is meeting        **
    // ** requirements.  Does not add a lot to the game      **
    // ********************************************************
    Stats * tempStats = new Stats(); 

    if (argc > 1 && strcmp(argv[1], "debug") == 0) {
        // **********************************************************
        // ** FUNCTIONAL REQUIREMENT 12 - DEBUGGING                **
        // ** FUNCTIONAL REQUIREMENT 22 - COMMAND LINE ARGS        **
        // **********************************************************
        debug = true;
        cout << RED << "Debug mode ON [ENTER] \n" << RESET;
        pressEnter();
    }

    welcome(seed, gameStats.pName, debug);
    
    if(debug) {
        cout << RED << "DEBUG: Random seed = " << seed << endl
                << "[ENTER]" << endl << RESET;
        pressEnter();
    }
    
    srand(seed); // sets the random seed to mission #
    // Note: using player input for seed is helpful for debug
    // as same 'random' ship layout can be generated if needed

    // Use binary & 2's complement questions as a challenge question to set the 
    // difficulty level.
    int diff = challenge(debug);

    // *************************************************************
    // ** FUNCTIONAL REQUIREMENT 27 - POINTER TO OBJECT           **
    // *************************************************************   
    Game * myGame = new Game(diff, debug); // Use a pointer to address game object
    
    // Play the game
    while(gameOn) {
        myGame->showGrid();
        //gameOn = myGame.nextMove();
        int moveResults = myGame->nextMove();
        
        if(moveResults == 1) {
            // move did not hit a boat
            // *****************************************************
            // ** FUNCTIONAL REQUIREMENT 26 - POINTER TO A STRUCT **
            // *****************************************************
            tempStats->misses++;
        } else if(moveResults == 2) {
            // move resulted in a hit
            tempStats->hits++;
        } else if (moveResults == 99) {
            // the exit code
            endGame(tempStats, myGame);
        }
        
        cout << "YOUR GAMEPLAY, COMMANDER " << gameStats.pName << ":\n";
        cout << "HITS: \t\t" << tempStats->hits << endl;
        cout << "MISSES: \t" << tempStats->misses << endl;
        cout << "RATIO: \t\t"; 
        cout << (tempStats->hits * 100.0) /(tempStats->hits + tempStats->misses); 
        cout << "%" << endl;
        cout << "[ENTER]";
        pressEnter();
    }
    
    // Delete the pointer to struct
    delete tempStats;
    // Delete the pointer to game object
    delete myGame;

    return 0;
}

void welcome(int &seed, string &name, bool debug = false) {
    // function welcome() :
    // displays the welcome screen
    // ********************************************************
    // ** FUNCTIONAL REQUIRMENT 16 - PASSING MECHANISMS      **
    // ** seed parameter is pass-by-ref                      **
    // ********************************************************
    string playerName;

    cout << CLEAR;
    cout.flush();
    string text = "C++ BATTLESHIP\n\nMISSION: SINK THE ENEMY FLEET.\n";
    text += "ENTER YOUR LAST NAME: ";

    teletype(text);

    // ************************************************************
    // ** FUNCTIONAL REQUIREMENT 5.1 - USE GETLINE FOR INPUT     **
    // ************************************************************
    getline(cin, name);
    name = stringToUpper(name);
    // ************************************************************
    // ** FUNCTIONAL REQUIREMENT 18 - STRING VARIABLE            **
    // ************************************************************

    text = "COMMANDER " + name + ":\nPLEASE SELECT YOUR MISSION ";
    text += "(0-1000): ";

    teletype(text);

    seed = getIntInput(0, 1000, debug);
}

void teletype(string theText) {
    // function teletype(string) 
    // outputs string in slow-motion, teletype fashion
    for (int i = 0; i < theText.length(); i++) {
        cout << CLEAR;
        cout.flush();
        cout << "\n";
        for (int j = 0; j <= i; j++) {
            cout << theText.at(j);
            cout.flush();
        }
        usleep(55000);
    }
}

void teletype(string theText, int speed) {
    // function teletype(string) 
    // outputs string in slow-motion, teletype fashion
    // optional parameter speed can be sent to control the effect speed
    // ******************************************************************
    // ** FUNCTIONAL REQUIREMENT # ?? - FUNCTION OVERLOADING           **
    // ** This version of teletype accepts different parameters than   **
    // ** version above.                                               **
    // ******************************************************************
    for (int i = 0; i < theText.length(); i++) {
        cout << CLEAR;
        cout.flush();
        cout << "\n";
        for (int j = 0; j <= i; j++) {
            cout << theText.at(j);
            cout.flush();
        }
        usleep(speed);
    }
}

string stringToUpper(string inString) {
    // function stringToUpper(string) 
    // returns a uppercase version of string.
    for (string::iterator p = inString.begin(); inString.end() != p; ++p) {
        *p = toupper(*p);
    }
    return inString;
}

int getIntInput(int min = INT_MIN, int max = INT_MAX, bool debug = false) {
    // function getIntInput() :
    // validates user input as integer and returns value
    // optional parameters are inclusive min and max range
    // **********************************************************
    // ** FUNCTIONAL REQUIREMENT 3 - PREDIFINED MACRO          **
    // ** I am using INT_MIN and INT_MAX as default parameters **
    // ** this function.                                       **
    // **********************************************************
    int intInput;
    bool validated = false;

    // debugging output
    if (debug) {
        cout << RED << "\nDEBUG: In function getIntInput() : min=";
        cout << min;
        cout << ", max=" << max << endl << RESET;
    }

    do {
        if (!(cin >> intInput)) {
            // ************************************************************
            // ** FUNCTIONAL REQUIREMENT 5.2 - USING CIN FOR INPUT       **
            // ************************************************************
            cout << "\nINVALID ENTRY. TRY AGAIN: ";
        } else {
            validated = true;
        }

        if (intInput > max || intInput < min) {
            cout << "\nYOUR INPUT DOES NOT MEET CRITERIA.\n";
            cout << "TRY AGAIN: ";
            validated = false;
        }

        cin.clear();
        cin.ignore(100000, '\n');
    } while (!validated);

    return intInput;
}

int challenge(bool debug) {
    // Function challenge():
    // Ask challenge questions about binary numbers and 2's complement to 
    // set game difficulty.
    // ***************************************************************
    // ** FUNCTIONAL REQUIREMENT 1 - BINARY NUMBERS                 **
    // ** FUNCTIONAL REQUIREMENT 2 - 2's COMPLEMENT                 **
    // ***************************************************************

    if (debug) {
        cout << RED << "DEBUG: In challenge() : " << endl
                << "[ENTER]" << endl << RESET;
        pressEnter();
    }

    int diff = 1; // result of the difficulty calculation
    int input = 0; // user input for questions
    int num = rand() % 17;
    int num2 = rand() % 5 * (-1);
    // Note: I've made these numbers *very* small on purpose so you
    // don't have to break out pen and paper to solve. Simply to demonstrate
    // understanding.

    string enter;

    string challenge1 = "COMMANDER, MUST SOLVE 3 CHALLENGE PROBLEMS TO GAIN\n";
    challenge1 += "ACCESS TO THE HEAVY ARTILLERY: \n";
    challenge1 += "Q1: WHAT IS THE INT VALUE OF THIS BINARY NUMBER:\n";

    string challenge2 = "Q2: WHAT IS THE INT VALUE OF THIS 2'S COMPLEMENT:\n";

    string challenge3 = "Q3: HOW FAST DOES AN UNLADEN SWALLOW FLY?";

    teletype(challenge1, 20000); // speeds up teletype outpu
    cout << (bitset<8>)num;
    cout << "\n > ";
    input = getIntInput();
    if (input == num) {
        diff = bitwiseRecursiveAdder(diff, 1);
        cout << "\nCORRECT! DIFFICULTY LEVEL SET TO: " << diff;
    } else {
        cout << "\nINCORRECT! DIFFICULTY LEVEL REMAINS: " << diff;
    }
    cout << RESET << "\n[ENTER] FOR NEXT QUESTION.";
    getline(cin, enter);

    teletype(challenge2, 20000);
    cout << (bitset<8>)num2 << " (" << num2 << ")";
    cout << "\n > ";
    input = getIntInput();
    if (input == num2) {
        diff = bitwiseRecursiveAdder(diff, 1);
        cout << "\nCORRECT! DIFFICULTY LEVEL SET TO: " << diff;
    } else {
        cout << RED << "\nINCORRECT! DIFFICULTY LEVEL REMAINS: " << diff;
    }
    cout << RESET << "\n[ENTER] FOR NEXT QUESTION.";
    getline(cin, enter);

    teletype(challenge3, 20000);
    cout << "\n (km/h) > ";
    input = getIntInput();
    cout << "\nJUST KIDDING... I WAS THOUGHT I WAS A PYTHON PROGRAM.\n";
    cout << "[ENTER] to continue.";
    pressEnter();

    return diff;
}

int bitwiseRecursiveAdder(int num1, int num2) {
    // Function bitwiseRecursiveAdder() :
    // Adds two ints using bitwise operations recursively.
    // credit for solution to: www.geeksforgeeks.org/add-two-numbers-without-
    //                                using-arithmetic-operators/
    // *******************************************************************
    // **  FUNCTIONAL REQUIREMENT  8 - BITWISE OPERATIONS               **
    // **  FUNCTIONAL REQUIREMENT 19 - RECURSION                        **
    // *******************************************************************
    if (num2 == 0) {
        return num1;
    } else {
        return bitwiseRecursiveAdder(num1 ^ num2, (num1 & num2) << 1);
    }
}

void pressEnter() {
    string temp;
    getline(cin, temp);
}

void endGame(Stats * tempStats, Game * myGame) {
    delete tempStats;
    delete myGame;
    exit(0);
}