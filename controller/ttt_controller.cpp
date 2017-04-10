//
// Created by rchowda on 9/7/2016.
//

#include <iostream>
#include <cstring>
#include <limits>
#include "ttt_controller.h"
#include "../model/Player.h"

ttt_controller::ttt_controller() {}
ttt_controller::~ttt_controller() {}

void ttt_controller::createPlayer(std::string& name, std::string& marker, int playerNum=1)  {
            switch (playerNum){
                case 1: player1 = Player(name, marker); break;
                case 2: player2 = Player(name, marker); break;

            }
          // board.setPlayer(name, marker,playerNum);
}

void ttt_controller::startGame(){
    board = Board(player1,player2);
    std::cout << board.printBoard() << std::endl;
    int turn = 1;
    int pos = -1;

    while (board.whoWon() == 'R'){

        if(turn % 2){
            std::cout << player1.getName() << "'s turn:";
            std::cin >> pos;
	    std::cout << std::endl;
            if(!board.markSymbol(player1,pos)){
                turn++;
            }
        }else{
            std::cout << player2.getName() << "'s turn:";
            std::cin >> pos;
	    std::cout << std::endl;
            if(!board.markSymbol(player2,pos)){
                turn++;
            }
        }
	if (std::cin.eof()==1) {
		std::cin.clear();
		//std::cin.ignore();
		continue;
	}
	if(pos==0){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
	for(int m = 0; m <2; m++){std::cout << "                                                " << std::endl;}
        std::cout << "\033[12A";
	for(int m = 0; m <10; m++){std::cout << "                                                " << std::endl;}
        std::cout << "\033[10A";
        std::cout << board.printBoard() << std::endl;
    }


    if(board.whoWon() == 'D') {
        std::cout << "The game is draw!" << std::endl;
    }else{
        if(player1.getSymbol() == board.whoWon()){
            std::cout << player1.getName() << " has won the game!" << std::endl;
        } else{
            std::cout << player2.getName() << " has won the game!" << std::endl;
        }
    }
}

bool ttt_controller::setSelection(int row, int col, int currentPlayer) {
    switch (currentPlayer){
        case 1: board.markSymbol(player1,(3*row+col+1));
            return true;
        case 2: board.markSymbol(player2,(3*row+col+1));
            return true;
        default: std::cout << "Invalid Player number" << std::endl;return false;
    }
}

int ttt_controller::determineWinner() {
    char win = board.whoWon();

    if(win == player1.getSymbol()){
        return 1;
    }else if(win == player2.getSymbol()){
        return 2;
    }else if(win == 'D'){
        return 0;
    }else{
        return -1;
    }


}


std::string ttt_controller::getGameDisplay() {
    return board.printBoard();
}
