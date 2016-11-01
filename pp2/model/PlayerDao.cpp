//
// Created by rchowda on 10/8/2016.
//

#include <fstream>
#include <iostream>
#include <cstdio>
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
//done
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
    rapidjson::Value regular(rapidjson::kObjectType);
    regular.AddMember("win",0, allocator);regular.AddMember("loss",0,allocator);regular.AddMember("tie",0,allocator);
    rapidjson::Value ultimate(rapidjson::kObjectType);
    ultimate.AddMember("win",0, allocator);ultimate.AddMember("loss",0,allocator);ultimate.AddMember("tie",0,allocator);
    rapidjson::Value stats(rapidjson::kObjectType);
    stats.AddMember("regular",regular,allocator);
    stats.AddMember("ultimate",ultimate,allocator);
    json.AddMember("stats",stats,allocator);
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
//done
Player PlayerDao::getPlayer(std::string name) {
    if(!inFile.is_open()){inFile.open(fileName);}
    if(!inFile.good()) return Player();
    std::string tmp_str;
    char* tmp_char;
    rapidjson::Document json;
    if(!inFile.eof()) {std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);}
    while(!inFile.eof()) {
        if (isJsonGood(json) && json["name"].GetString() == name){

            return createPlayerInstance(json);
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
//done
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
        if(isJsonGood(json)) {
            playersList.push_back(createPlayerInstance(json));
        }
        std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);  //Fetch next line
    }
    inFile.close();
    return playersList;
}
//done
bool PlayerDao::updatePlayerScore(Player &player, char game, int result) {
    //game: R - Regular, U - Ultimate
    //result: 1 - win , 2 - loss, 3 - tie
    if(!inFile.is_open()){inFile.open(fileName);}
    if(!inFile.good()) return false;
    if(!outFile.is_open()){outFile.open(temp_fileName,std::ios_base::out);}
    std::string tmp_str;
    char* tmp_char;
    rapidjson::Document json;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
    if(!inFile.eof()) {std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);}
    while(!inFile.eof()) {
        if (isJsonGood(json) && json["name"].GetString() == player.getName()){

            if(game == 'R') {

                switch (result){
                    case 1: {rapidjson::Value& value = json["stats"]["regular"]["win"];  value.SetInt(value.GetInt()+1); break;}
                    case 2: {rapidjson::Value& value = json["stats"]["regular"]["loss"]; value.SetInt(value.GetInt()+1); break;}
                    case 3: {rapidjson::Value& value = json["stats"]["regular"]["tie"];  value.SetInt(value.GetInt()+1); break;}
                    default: return false;
                }
            }else if(game == 'U') {
                switch (result){
                    case 1: {rapidjson::Value& value = json["stats"]["ultimate"]["win"];  value.SetInt(value.GetInt()+1); break;}
                    case 2: {rapidjson::Value& value = json["stats"]["ultimate"]["loss"]; value.SetInt(value.GetInt()+1); break;}
                    case 3: {rapidjson::Value& value = json["stats"]["ultimate"]["tie"];  value.SetInt(value.GetInt()+1); break;}
                    default: return false;
                }
            }

            json.Accept(writer);
            outFile << buffer.GetString() << std::endl;
            while(std::getline(inFile,tmp_str)) outFile << tmp_str << std::endl;

            inFile.close();
            outFile.close();
            auto success = std::rename(temp_fileName.c_str(),fileName.c_str());
            assert(success);
            return true;

        }
        outFile << tmp_str << std::endl;
        std::getline(inFile,tmp_str); tmp_char = &tmp_str[0]; json.Parse(tmp_char);  //Fetch next
    }

    inFile.close();
    outFile.close();
    std::remove(temp_fileName.c_str());
    return false;
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
//done
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
            if(isJsonGood(json) && json["name"].GetString() == name){
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

bool PlayerDao::isJsonGood(rapidjson::Document& json){
    if(json.HasMember("name") &&
       json.HasMember("symbol")&&
       json.HasMember("stats")
            ){
        const rapidjson::Value& stats = json["stats"];
        if( stats.HasMember("regular") &&
            stats.HasMember("ultimate") ){

            const rapidjson::Value& regular = (stats["regular"]);
            const rapidjson::Value& ultimate  = (stats["ultimate"]);

            return (regular.HasMember("win") &&
                    regular.HasMember("loss") &&
                    regular.HasMember("tie") &&
                    ultimate.HasMember("win") &&
                    ultimate.HasMember("loss") &&
                    ultimate.HasMember("tie"));

        }
    }
    return false;
}

Player PlayerDao::createPlayerInstance(rapidjson::Document& json){
    return Player(json["name"].GetString(), json["symbol"].GetString()[0], json["stats"]["regular"]["win"].GetInt(), json["stats"]["regular"]["loss"].GetInt(), json["stats"]["regular"]["tie"].GetInt(), json["stats"]["ultimate"]["win"].GetInt(), json["stats"]["ultimate"]["loss"].GetInt(), json["stats"]["ultimate"]["tie"].GetInt());
}

//int main(){
//    PlayerDao playerDao;
//    Player one("Raghuvaran6",'R');
//
//    std::cout << "Present: " << (playerDao.updatePlayerScore(one,'U',2)) << std::endl;
//}
