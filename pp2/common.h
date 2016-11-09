#include <iostream>
#include <stdio.h>
#include <cstring>
#include "controller/TTTController.h"

#define SET_PLAYER_DEF_PARA

using namespace std;

/*--- Checks if (cond) is true (=> success)) else fail executes (fail) ---------------*/
#define makeAssert(cond, msg, fail)                     \
    if(!(cond)) {                                       \
        cout << msg << endl;                            \
        fail;                                           \
    }else {                                             \
    }                                                   \

void setPlayer(TTTController& controller);
void setPlayerDefaultPara(TTTController& controller);
void showGameDisplay(TTTController& controller);


/* There will be total 7 test cases
1. Player 2 win
2. Tie
*/
void testCase1(TTTController& controller);  
void testCase2(TTTController& controller); 
    
