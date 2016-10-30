//
// Created by rchowda on 10/8/2016.
//

#include <fstream>
#include <iostream>
#include "PlayerDao.h"
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/writer.h"
#include "../lib/rapidjson/stringbuffer.h"

bool PlayerDao::createNewPlayer_old(Player &player) {
    if(isPresent(player.getName())) return false;
    if(!outFile.is_open()){outFile.open(fileName,std::ios_base::app);}
    outFile << player.getName() << std::endl;
    outFile << player.getSymbol() << std::endl;
    outFile.close();
    return true;
}

bool PlayerDao::createNewPlayer(Player &player) {
    if(isPresent(player.getName())) return false;
    if(!outFile.is_open()){outFile.open(fileName,std::ios_base::app);}

    rapidjson::Document json;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
    json.SetObject();
    rapidjson::Value tmp_val;
    tmp_val.SetString(player.getNameChar(),player.getName().length(),allocator);
    json.AddMember("name", tmp_val,allocator);  //It's okay to have red line
    tmp_val.SetString(player.getSymbolChar(), 1, allocator);
    json.AddMember("symbol", tmp_val, allocator);  //It's okay to have red line
    json.AddMember("win",0, allocator);json.AddMember("loss",0,allocator);json.AddMember("tie",0,allocator);
    json.AddMember("uwin",0, allocator);json.AddMember("uloss",0,allocator);json.AddMember("utie",0,allocator);
    json.Accept(writer);
    outFile << buffer.GetString() << std::endl;
    outFile.close();
    return true;
}

Player PlayerDao::getPlayer_old(std::string name) {
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
//include player stats
Player PlayerDao::getPlayer(std::string name) {
    if(!inFile.is_open()){inFile.open(fileName);}
    std::string tmp_str;
    char* tmp_char;
    rapidjson::Document json;
    if(!inFile.eof()) {std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);}
    while(!inFile.eof()) {
        if (json.HasMember("name") && json["name"].GetString() == name && json.HasMember("symbol")){
            return Player(json["name"].GetString(), json["symbol"].GetString());
        }
        std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);  //Fetch next
    }
    inFile.close();
    return Player();
}

std::list<Player> PlayerDao::getAllPlayers_old() {
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
//include player stats
std::list<Player> PlayerDao::getAllPlayers() {
    std::list<Player> playersList;
    if(!inFile.is_open()){inFile.open(fileName);}
    std::string tmp_str, tmp_name_str, tmp_sym_str;
    char* tmp_char;
    rapidjson::Document json;
    if(!inFile.eof()) {
        std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);
    }
    while(!inFile.eof()){
        if(json.HasMember("name") && json.HasMember("symbol")) {
            playersList.push_back(Player(json["name"].GetString(), json["symbol"].GetString()));
        }
        std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);  //Fetch next line
    }
    inFile.close();
    return playersList;
}

bool PlayerDao::isPresent_old(const std::string &name) {
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

bool PlayerDao::isPresent(const std::string &name) {
    std::ofstream file;
    file.open("log.txt",std::ios_base::app);
    file << "case:" << name;
    if(!inFile.is_open()) {inFile.open(fileName); file << "File Opened\n";}
    if(inFile.good())
    {   file << "It is good\n";
        std::string tmp_str;
        char* tmp_char;
        rapidjson::Document json;
        if(!inFile.eof()) {std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char); file << "First Check has: " << tmp_str << "\n";}
        while(!inFile.eof()){
            if(json.HasMember("name") && json["name"].GetString() == name){
                inFile.close();
                file << "match"; file.close();
                return true;
            }
            std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);
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

int main(){
    PlayerDao playerDao;
    Player one("Raghuvaran",'R');

    std::cout << playerDao.createNewPlayer(one);
}
