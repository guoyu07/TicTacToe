//
// Created by rchowda on 10/28/2016.
//

#ifndef PP2_BIGBOARD_H
#define PP2_BIGBOARD_H


#include <array>
#include "Board.h"

class BigBoard {
    Player player1, player2;
public:
    std::array<Board,9> lBoard;
    BigBoard();

    BigBoard(const Player &player1, const Player &player2);

    std::array<Board, 9> &getLBoard();

    void setLBoard(const std::array<Board, 9> &lBoard);

    Player getPlayer (int number);
};


#endif //PP2_BIGBOARD_H
