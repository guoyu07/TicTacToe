//
// Created by rchowda on 9/6/16.
//

#include "Player.h"

Player::Player(){
    name = "No Name";
    symbol = '*';
}

Player::Player(const std::string &name, char symbol) {
    Player::name = name;
    Player::symbol = symbol;
}

Player::Player(const std::string &name, const std::string symbol) {
    Player::name = name;
    Player::symbol = symbol[0];
}

const std::string &Player::getName() const {
    return name;
}

void Player::setName(std::string &name) {
    Player::name = name;
}

const char Player::getSymbol() const {
    return symbol;
}

void Player::setSymbol(char symbol) {
    Player::symbol = symbol;
}
