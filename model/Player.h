//
// Created by rchowda on 9/6/16.
//

#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H


#include <string>

class Player {

    std::string name;
    char symbol;
public:
    const std::string &getName() const;

    void setName(std::string &name);

    const char getSymbol() const;

    void setSymbol(char symbol);

    Player();

    Player(const std::string &name, char symbol);

    Player(const std::string &name, const std::string symbol);
};


#endif //TICTACTOE_PLAYER_H
