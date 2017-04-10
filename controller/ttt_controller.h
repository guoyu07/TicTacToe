//
// Created by rchowda on 9/7/2016.
//

#ifndef TICTACTOE_TTT_CONTROLLER_H
#define TICTACTOE_TTT_CONTROLLER_H


#include <string>
#include "../model/Player.h"
#include "../model/Board.h"

class ttt_controller {
    Player player1, player2;
    Board board;
public:
    ttt_controller();
    ~ttt_controller();
    void createPlayer(std::string&,std::string&,int);
    void startGame();
    bool setSelection(int, int, int);
    int determineWinner();
    std::string getGameDisplay();
};


#endif //TICTACTOE_TTT_CONTROLLER_H
