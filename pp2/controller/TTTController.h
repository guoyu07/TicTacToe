//
// Created by rchowda on 9/7/2016.
//

#ifndef TICTACTOE_TTT_CONTROLLER_H
#define TICTACTOE_TTT_CONTROLLER_H


#include <string>
#include "../model/Player.h"
#include "../model/Board.h"

class TTTController {

public:
    Player player1, player2;
    Board board;
    TTTController();
    ~TTTController();
    void createPlayer(std::string,std::string,int);         //required
    void createPlayer(std::string playerJsonObject);        //required
    std::string getPlayerName(int currentPlayer);
    std::string getAllSavedPlayers();                       //required
    void startNewGame();                                    //required
    bool setSelection(std::string gameJsonObject);          //required
    bool setSelection(int row, int col, int currentPlayer); //required
    bool setSelection(int pos, int currentPlayer);
    bool setSelection(const Player& player,int pos);
    int determineWinner();                                  //required
    std::string getGameDisplay(bool isJson);                //required
    std::string getGameDisplay();                           //required
    bool compare(const Player& , const Player&);
    void partParseJson(std::string& json, std::string& key);
    void partParseJson(std::string& json, int& key);
};


#endif //TICTACTOE_TTT_CONTROLLER_H
