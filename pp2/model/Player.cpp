//
// Created by rchowda on 9/6/16.
//

#include "Player.h"

Player::Player(): name("No name"), symbol('*'), id(-1), reg{0,0,0}, ult{0,0,0}{}

Player::Player(char symbol): name("null"), symbol(symbol), id(-rand()%10000), reg{0,0,0}, ult{0,0,0}{}

Player::Player(const std::string &name, char symbol) : name(name), symbol(symbol), id(rand()%10000), reg{0,0,0}, ult{0,0,0}{}

Player::Player(const std::string &name, const std::string symbol) : name(name), symbol(symbol[0]), id(rand()%10000), reg{0,0,0}, ult{0,0,0}{}

Player::Player(const std::string &name, char symbol, int win, int loss, int tie, int uwin, int uloss, int utie) : name(name), symbol(symbol), id(rand()%10000) {
    reg[0] = win; reg[1] = loss; reg[2] = tie;
    ult[0] = uwin; ult[1] = uloss; ult[2] = utie;
}

std::string Player::getName() const {
    return name;
}

const char *Player::getNameChar() const {
    return &name[0];
}

void Player::setName(std::string name) {
    Player::name = name;
}

const char Player::getSymbol() const {
    return symbol;
}

const char *Player::getSymbolChar() const {
    return &symbol;
}

void Player::setSymbol(char symbol) {
    Player::symbol = symbol;
}

int Player::getId() const {
    return id;
}

void Player::setId(int id) {
    Player::id = id;
}

const int *Player::getRegStats() const{
    return reg;
}

const int *Player::getUltStats() const {
    return ult;
}


