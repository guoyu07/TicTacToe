#include <iostream>

#include "controller/ttt_controller.h"

int main() {

    std::string name1, name2, symbol1, symbol2;
    std::cout << "Enter Player1 Name: "; std::cin >> name1;
    std::cout << "Enter Player1 Symbol: "; std::cin >> symbol1;
    std::cout << std::endl;

    std::cout << "Enter Player2 Name: "; std::cin >> name2;
    std::cout << "Enter Player2 Symbol: "; std::cin >> symbol2;
    std::cout << std::endl;

//    Board  board(Player(name1,symbol1),Player(name2,symbol2));
//    board.start();

    ttt_controller controller;
    controller.createPlayer(name1,symbol1,1);
    controller.createPlayer(name2,symbol2,2);

    controller.startGame();

}