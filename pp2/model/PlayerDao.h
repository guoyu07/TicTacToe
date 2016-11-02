//
// Created by rchowda on 10/8/2016.
//

#ifndef PP2_PLAYERDAO_H
#define PP2_PLAYERDAO_H


#include <list>
#include <fstream>
#include "Player.h"
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/writer.h"
#include "../lib/rapidjson/stringbuffer.h"

class PlayerDao {
    std::string fileName = "filePlayers.txt", temp_fileName = "filePlayers_temp.txt";
    std::ofstream outFile;
    std::ifstream inFile;
    bool isJsonGood(rapidjson::Document& json);
    Player createPlayerInstance(rapidjson::Document& json);
public:
    bool createNewPlayer(Player &player);    //Create
    bool createNewPlayer_old(Player &player);    //Obsolete
    Player getPlayer(std::string name); //Read
    Player getPlayer_old(std::string name); //Obsolete
    std::list<Player> getAllPlayers();
    std::list<Player> getAllPlayers_old();  //Obsolete
    bool updatePlayerScore(Player& player, char game, int result); //Update
    //Delete
    bool isPresent_old(const std::string &name);
    bool isPresent(const std::string &name);
};


#endif //PP2_PLAYERDAO_H
