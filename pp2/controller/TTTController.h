//
// Created by rchowda on 9/7/2016.
//

#ifndef TICTACTOE_TTT_CONTROLLER_H
#define TICTACTOE_TTT_CONTROLLER_H


#include <string>
#include "../model/Player.h"
#include "../model/Board.h"
#include "../model/BigBoard.h"

class TTTController {
    bool isGameRegular;

public:
    Player player1, player2;
    Board board;
    BigBoard bigBoard;
    TTTController();
    ~TTTController();
    void createPlayer(std::string,std::string,int);         //required
    void createPlayer(std::string playerJsonObject);        //required
    void createPlayer_old(std::string playerJsonObject);


    std::string getPlayerName(int currentPlayer);
    std::string getAllSavedPlayers();                       //required
    void startNewGame();                                    //required


    bool setSelection(std::string gameJsonObject);          //required
    bool setSelection(int row, int col, int currentPlayer); //required
    bool setSelection(int pos, int currentPlayer);
    bool setSelection(const Player& player,int pos);
    bool setSelection(const Player &player, int pos, Board& board);
    bool setSelection(int row, int col, int outerRow, int outerCol, int currentPlayer);


    int determineWinner();                                  //required
    int determineWinner(Board& board);
    int determineWinner(BigBoard& bigBoard);

    std::string getGameDisplay(bool isJson);                //required
    std::string getGameDisplay();                           //required
    std::string getGameCursor();


    bool comparePlayers(const Player &, const Player &);
    bool compareBoards(const Board& b1, const Board& b2);
    void partParseJson(std::string& json, std::string& key);
    void partParseJson(std::string& json, int& key);
};


#endif //TICTACTOE_TTT_CONTROLLER_H
