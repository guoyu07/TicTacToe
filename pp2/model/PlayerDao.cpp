//
// Created by rchowda on 10/8/2016.
//

#include <fstream>
#include <iostream>
#include "PlayerDao.h"
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/writer.h"
#include "../lib/rapidjson/stringbuffer.h"

bool PlayerDao::createNewPlayer(Player &player) {
    if(isPresent(player.getName())) return false;
    if(!outFile.is_open()){outFile.open(fileName,std::ios_base::app);}
    outFile << player.getName() << std::endl;
    outFile << player.getSymbol() << std::endl;
    outFile.close();
    return true;
}

Player PlayerDao::getPlayer(std::string name) {
    if(!inFile.is_open()){inFile.open(fileName);}
    std::string tmp_str;
    if(!inFile.eof()) std::getline(inFile,tmp_str);
    while(!inFile.eof()) {
        if (tmp_str == name) {
            std::getline(inFile,tmp_str);
            return Player(name, tmp_str);
        }
        std::getline(inFile,tmp_str);
        std::getline(inFile,tmp_str);
    }
    inFile.close();
    return Player();
}

std::list<Player> PlayerDao::getAllPlayers() {
    std::list<Player> playersList;
    if(!inFile.is_open()){inFile.open(fileName);}
    std::string tmp_name_str, tmp_sym_str;
    if(!inFile.eof()) {
        std::getline(inFile,tmp_name_str);
        std::getline(inFile,tmp_sym_str);
    }
    while(!inFile.eof()){
        if(tmp_name_str == "" || tmp_sym_str == "") {}
            else playersList.push_back(Player(tmp_name_str,tmp_sym_str));
        std::getline(inFile,tmp_name_str);
        std::getline(inFile,tmp_sym_str);
    }
    inFile.close();
    return playersList;
}

bool PlayerDao::isPresent(const std::string& name) {
    std::ofstream file;
    file.open("log.txt",std::ios_base::app);
    file << "case:" << name;
    if(!inFile.is_open()) {inFile.open(fileName); file << "File Opened\n";}
    if(inFile.good())
    {   file << "It is good\n";
        std::string tmp_str;
        if(!inFile.eof()) {std::getline(inFile,tmp_str); file << "First Check has: " << tmp_str << "\n";}
        while(!inFile.eof()){
            if(tmp_str == name){
                inFile.close();
                file << "match"; file.close();
                return true;
            }
            std::getline(inFile,tmp_str);std::getline(inFile,tmp_str);    //To skip symbol
        }
        file << "not match"; file.close();
        return false;

    }
    else{//TODO remove this line before submission
        file << "not good"; file.close();
       // std::cout << "Unable to find" + fileName + "\n";
        return false;
    }
}

//int main(){
//    PlayerDao playerDao;
//    Player one("Raghuvaran",'R');
//
//    std::cout << playerDao.getPlayer("Raghuvaran").getSymbol();;
//}
