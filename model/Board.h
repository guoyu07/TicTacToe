//
// Created by rchowda on 9/6/16.
//

#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H


#include <string>
#include "Player.h"

class Board {
    std::string cursor;
    Player player1;
    Player player2;
public:
    Board();
    Board(const Player&, const Player&);
    void setPlayer(std::string&, std::string&, int);
    int markSymbol(const Player&, int);
    std::string printBoard();
    char whoWon();
    void start();
    void reset();
};


#endif //TICTACTOE_BOARD_H
