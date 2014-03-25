CS161 - WINTER 2014
FINAL PROJECT SUBMISSION - README.TXT

C. VAUGHAN SCHMIDT

Submission: BattleShip Style game.

Included files should be:
BattleShip.cpp          the main game wrapper program
Game.cpp + Game.h       the files for the game class
BattleShip_README.txt   this file

Description
-----------

BattleShip.cpp is similar to the board game where 2 players place navy ship
playing pieces on a grid hidden from the opponent. In this program, the 
computer hides the ship, and player enters grid coordinates to 'attack'.
Results of game play are displayed on a grid.

Compiling
---------
On flip server, I compiled & ran with the following steps:

g++ BattleShip.cpp -c -o BattleShip.o
g++ Game.cpp -c -o Game.o
g++ -o battleshipgame Game.o BattleShip.o
./battleshipgame

(There is probably a simpler / better way, but this worked for me.)

Gameplay
--------
Invoke the game with command "./battleshipgame" once compiled per above.
** NOTE ** - might need a larger terminal window if you can't see the whole
game board.

Debug Option
------------
Invoke the game with command "./battleship debug" to turn on debug mode.

To-Do
-----
I am submitting a working version early with hope of having time to reduce 
this list of things I would *like* to complete, but I believe the current
submission is largely complete.  I am unsure of time available in the next
week due to work schedule, etc.
1. Better Scoring  ** Somewhat done 2014.03.11 **
2. Way to gracefully exit  ** somewhat done 2014.03.11 **
      Note: exiting could be much improved, but it works.
3. Pointer to a struct  ** DONE 2014.03.11 **
4. Pointer to a object  ** DONE 2014.03.11 **
5. Keep track of actual boats sunk and when game would be really over


Functional Requirements
-----------------------
In general, I have tried to provide clear comments as to exactly where 
functional requirements are met inside the source files.  However, some
of the requirements don't fit any specific line of code.  As such, here is
the requirements list and any ancillary comments I have explaining how they
are met.

1, 2 Binary Numbers + 2's Complement

    The player must answer challenge questions about binary and 2's
    complement to set the difficulty level.  I have made the questions
    purposefully easy (and in case of 2's complement, even supply the answer)
    because I did not want player to have to pull out pencil and paper to 
    solve.

3. Predefined Macro

    Used in BattleShipp.cpp, getIntInput()

4. Simple output

   Yep, did some of that.

6. Type Casting

    Used in Game.cpp, showGrid() function to display the columns as
    alpha chars.

7. Conditionals

    Pervasive use of conditionals, but especially in Game.cpp, 
    validatePos() function.

8. Bitwise Operator

    Used to add two ints (recursively, see #19 also) in BattleShip.cpp,
    function bitwiseRecursiveAdder()  Note: credit to website
    www.geeksforgeeks.org/add-two-numbers-without-using-arithmetic-operators/
    for this solution.

9. Loops

    Pervasive use of loops throughout, but especially in Game.cpp, 
    validatePos() to make sure a new boat placement will not hit an existing
    boat already on the playing grid.

11, 12 Error categories + Debugging

    Yes, I have experienced all possible error categories and then some when 
    writing this program.  The "debug" mode (invoked with command line
    arg.) in particular was added to help debug both logic and run time errors
    in the validatePos() function (and others).

14. Functional Decomposition

    see all the functions and also use of Game.cpp, Game.h to break out
    the game object.

15. Variable Scope

    It is not uncommon for the same variable name to be used between 
    both BattleShip.cpp and Game.cpp - but, the use of each variable is 
    appropriate to it's scope of resolution within the program.

16. Passing Mechanisms

    Pervasive use throughout.  See BattleShip.cpp, welcome() function
    for pass-by-reference.

17. Function Overloading

    See Game.cpp constructor.  There are 2 versions of the constructor
    such that game object can be initialized with default values or specific
    values.

18. String Variable

    String playerName used in BattleShip.cpp, welcome() function.
    Also, the struct Stats in BattleShipp.cpp makes use of the pName string.

19. Recursion

    See BattleShip.cpp, bitwiseRecursiveAdder() Function.  Used in 
    combo with #8 above.

20 + 21  Multi-Dimensional Array + Dynamic Array

    Game grid (playing board) is a 2-D Dynamically declared array.  See
    Game.cpp, makeGrid() function for implementation.

22. Command Line Arg

    debugging output is enabled with invoking the program as follows:
    "./BattleShip debug"

23. Struct

    BattleShip.cpp has struct GameStats

24. Defines and uses a class

    Games class is implements as myGame object in BattleShip.cpp

25. Pointer to an array

    (See 20 & 21) The game grid is implemented as a dynamically allocated
    2-D array.  In Game.cpp, function makeGrid() does this by creating
    a pointer 'theGrid' to a array of pointers, each element of this first
    array are my "rows".  Each row element is then technically a pointer
    to a 1-D array, which are my 'column' elements.

26. Pointer to struct

    In BattleShip.cpp - I have a pointer to Stats struct called tempStats.
    Kind of forced useage of pointer to a struct, but there to meet 
    functional requirements.

27. Pointer to an object

    In BattleShip.cpp - I use pointer myGame to a game object

28. Does something awesome

    Well, in my (biased) opinion, I'm really impressed with the whole
    program. it was much more work than originally expected.

29. Extra credit

    See #28.  In hindsight, this ended up much more intensive than I thought
    it would be.  Getting the logic for placing boats randomly seemed easy
    enough on paper - actual implementation took a lot of debugging.

    Also, the teletype text effect was pretty cool to get working, trying
    to make visually interesting output given the limitations of a terminal
    environment.