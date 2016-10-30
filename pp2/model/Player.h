//
// Created by rchowda on 9/6/16.
//

#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H


#include <string>

class Player {

    std::string name;
    char symbol;
    int id;
    int reg[3], ult[3];

public:
    int getId() const;

    void setId(int id);

    std::string getName() const;

    const char* getNameChar() const;

    void setName(std::string name);

    const char getSymbol() const;

    const char* getSymbolChar() const;

    void setSymbol(char symbol);

    const int* getRegStats() const;

    const int* getUltStats() const;

    Player();

    Player(char symbol);

    Player(const std::string &name, char symbol);

    Player(const std::string &name, const std::string symbol);

    Player(const std::string &name, char symbol, int win, int loss, int tie, int uwin, int uloss, int utie);

};


#endif //TICTACTOE_PLAYER_H
