//
// Created by rchowda on 10/28/2016.
//

#include <iostream>
#include "BigBoard.h"

BigBoard::BigBoard() : player1(Player("dummy",'d')), player2(Player("dummy",'d'))  {
    for(int i=0; i<9; i++){
        lBoard[i] = Board(player1,player2,i);
    }
}

BigBoard::BigBoard(const Player &player1, const Player &player2) : player1(player1), player2(player2) {
    for(int i=0; i<9; i++){
        lBoard[i] = Board(player1,player2,i);
    }
//    std::cout << lBoard.back().getId() <<","<< lBoard.size() << std::endl;
}

const std::array<Board, 9> &BigBoard::getLBoard() const {
    return lBoard;
}

void BigBoard::setLBoard(const std::array<Board, 9> &lBoard) {
    BigBoard::lBoard = lBoard;
}


//int main(){
//    Player p1 = Player("RV",'x');
//    Player p2 = Player("SW",'y');
//
//    BigBoard bb = BigBoard(p1,p2);
//}