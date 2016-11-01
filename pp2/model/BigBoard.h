//
// Created by rchowda on 10/28/2016.
//

#ifndef PP2_BIGBOARD_H
#define PP2_BIGBOARD_H


#include <array>
#include "Board.h"

class BigBoard {
    Player player1, player2;
    std::array<Board,9> lBoard;
public:
    BigBoard();

    BigBoard(const Player &player1, const Player &player2);

    const std::array<Board, 9> &getLBoard() const;

    void setLBoard(const std::array<Board, 9> &lBoard);

    const Player& getPlayer (int number) const;
};


#endif //PP2_BIGBOARD_H
