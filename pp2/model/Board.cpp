//
// Created by rchowda on 9/6/16.
//

#include <iostream>
#include "Board.h"

Board::Board():id(-1) {
    cursor = {Player('1'),Player('2'),Player('3'),Player('4'),Player('5'),Player('6'),Player('7'),Player('8'),Player('9')};
    player1 = Player("dummy",'d');
    player2 = Player("dummy",'d');
}

Board::Board(const Player &p1, const Player &p2):id(-1) {
    cursor = {Player('1'),Player('2'),Player('3'),Player('4'),Player('5'),Player('6'),Player('7'),Player('8'),Player('9')};
    player1 = p1;
    player2 = p2;
}

Board::Board(const Player &p1, const Player &p2, int id): id(id) {
    cursor = {Player('1'),Player('2'),Player('3'),Player('4'),Player('5'),Player('6'),Player('7'),Player('8'),Player('9')};
    player1 = p1;
    player2 = p2;
}

const std::array<Player, 9> Board::getCursor() const{
    return cursor;
}

void Board::setCursor(const std::array<Player, 9> &cursor) {
    Board::cursor = cursor;
}

int Board::getId() const {
    return id;
}

void Board::setId(int id) {
    Board::id = id;
}

//int main(){
//    Board b = Board(Player("Raghu",'x'),Player("Sathy",'o'));
//    if(b.compare(b.player1,b.player1))    std::cout << b.player1.getId() << " | " << b.player2.getId() << std::endl;
//    std::cout << b.cursor[3].getSymbol() << std::endl;
//}