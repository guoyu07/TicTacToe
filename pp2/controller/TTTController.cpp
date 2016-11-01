//
// Created by rchowda on 9/7/2016.
//

#include <iostream>
#include <cstring>
#include <limits>
#include "TTTController.h"
#include "../model/Player.h"
#include "../model/PlayerDao.h"
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/stringbuffer.h"
#include "../lib/rapidjson/writer.h"

TTTController::TTTController() {}
TTTController::~TTTController() {}

//done
void TTTController::createPlayer(std::string name, std::string marker, int playerNum=1)  {
    PlayerDao playerDao;

    switch (playerNum){
        case 1:
            if(playerDao.isPresent(name)){              //Does player_num exist?
                player1 = playerDao.getPlayer(name);    //True; retrieve
            }else{
                player1 = Player(name, marker);         //False; Create and save
                playerDao.createNewPlayer(player1);
            }break;
        case 2:
            if(playerDao.isPresent(name)){
                player2 = playerDao.getPlayer(name);
            }else{
                player2 = Player(name, marker);
                playerDao.createNewPlayer(player2);
            }break;

    }
    // board.setPlayer(name, marker,playerNum);
}

//done
void TTTController::createPlayer(std::string playerJsonObject) {

    rapidjson::Document json;
    json.Parse(&playerJsonObject[0]);

    if(json.HasMember("name") &&
            json.HasMember("marker") &&
            json.HasMember("playerNum") &&
            json["name"].IsString() &&
            json["marker"].IsString() &&
            json["playerNum"].IsInt())
    createPlayer(json["name"].GetString(),json["marker"].GetString(),json["playerNum"].GetInt());
    else
        std::cout << "Invalid JSON!" << "@TTTController::createPlayer" << std::endl;

}

//obsolete
void TTTController::createPlayer_old(std::string playerJsonObject) {
    std::string name, marker;
    int playerNum =1;

    partParseJson(playerJsonObject,name);
    partParseJson(playerJsonObject,marker);
    partParseJson(playerJsonObject,playerNum);

    createPlayer(name,marker,playerNum);

}

//done
std::string TTTController::getPlayerName(int currentPlayer) {
    switch(currentPlayer){
        case 1: return player1.getName();
        case 2: return player2.getName();
        default: return "No Player exists";
    }
}

//TODO expected to be changed
std::string TTTController::getAllSavedPlayers() {
    PlayerDao playerDao;
    std::list<Player> playerList = playerDao.getAllPlayers();
    std::string playerStr;
    playerStr += "{\"players\":[";
    for(Player i: playerList){
        playerStr += "{\"name\":\"" + i.getName() + "\",\"marker\":\"" + i.getSymbol() + "\"},";
    }
    playerStr.pop_back();
    playerStr += "]}";

    return playerStr;
}

//done - maybe later tweak
void TTTController::startNewGame() {
    board = Board(player1,player2);
    bigBoard = BigBoard(player1,player2);
}

//TODO expected to be changed
bool TTTController::setSelection(std::string gameJsonObject) {

    rapidjson::Document json;
    json.Parse(gameJsonObject.c_str());
    if(json.HasMember("row") &&
            json.HasMember("col") &&
            json.HasMember("currentPlayer") &&
            json["row"].IsInt() &&
            json["col"].IsInt() &&
            json["currentPlayer"].IsInt())
        if(json.HasMember("outerRow") &&
                json.HasMember("outerCol") &&
                json["outerRow"].IsInt() &&
                json["outerCol"].IsInt())
            return setSelection(json["row"].GetInt(), json["col"].GetInt(),json["outerRow"].GetInt(),json["outerCol"].GetInt(),json["currentPlayer"].GetInt());
        else
            return setSelection(json["row"].GetInt(), json["col"].GetInt(),json["currentPlayer"].GetInt());
    else
        return false;
}

//done
bool TTTController::setSelection(int row, int col, int currentPlayer) {
    if(!(row>=0 && row <=2 && col >=0 && col <= 2)) return false;
    switch (currentPlayer){
        case 1: return setSelection(player1,(3*row+col));
        case 2: return setSelection(player2,(3*row+col));
        default:
            //std::cout << "Invalid Player number" << std::endl;
            return false;
    }
}

//done
bool TTTController::setSelection(int pos, int currentPlayer) {
    switch(currentPlayer){
        case 1: return setSelection(player1,pos);
        case 2: return setSelection(player2,pos);
        default: return false;
    }
}

//done
bool TTTController::setSelection(const Player &player, int pos) {

    std::array<Player,9> cursor;
    cursor = board.getCursor();
    if(pos >= 0 && pos <= 8){


        if(comparePlayers(cursor[pos], player1)|| comparePlayers(cursor[pos], player2)){

            //std::cout << "\033[1;31mCaution:\033[0;m Invalid position! Please try again";// << std::endl;
            return false;
        }

        cursor[pos] = player;
        board.setCursor(cursor);
        return true;

    }else{
        //std::cout << "\033[1;31mCaution:\033[0;m Position not in range";// << std::endl;
        return false;
    }

}

//yet to be tested
bool TTTController::setSelection(const Player &player, int pos, Board& board) {

    std::array<Player,9> cursor;
    cursor = board.getCursor();
    if(pos >= 0 && pos <= 8){


        if(comparePlayers(cursor[pos], player1)|| comparePlayers(cursor[pos], player2)){

            //std::cout << "\033[1;31mCaution:\033[0;m Invalid position! Please try again";// << std::endl;
            return false;
        }

        cursor[pos] = player;
        board.setCursor(cursor);
        return true;

    }else{
        //std::cout << "\033[1;31mCaution:\033[0;m Position not in range";// << std::endl;
        return false;
    }

}


bool TTTController::setSelection(int row, int col, int outerRow, int outerCol, int currentPlayer) {
    int outerPos = 3*outerRow+outerCol;
    std::array<Board,9> board = bigBoard.getLBoard();
    if(!(row>=0 && row <=2 && col >=0 && col <= 2)) return false;
    switch (currentPlayer) {
        case 1:
            if( setSelection(player1, (3 * row + col),board.at(outerPos)) ){
                bigBoard.setLBoard(board);
                return true;
            };
        case 2:
            if( setSelection(player2, (3 * row + col),board.at(outerPos)) ){
                bigBoard.setLBoard(board);
                return true;
            };
        default:
            //std::cout << "Invalid Player number" << std::endl;
            return false;
    }
}

//TODO expected to be changed
int TTTController::determineWinner() {

    std::array<Player,9> cursor;
    cursor = board.getCursor();
    //Check column match
    for(int i=0, j=3, k=6; i<3; i++, j++, k++){
        if(comparePlayers(cursor[i], cursor[j]) && comparePlayers(cursor[j], cursor[k])){
            //std::cout << "i:" << i;
            return comparePlayers(cursor[i], player1)?1:2;
        }
    }

    //check row match
    for(int i=0, j=1, k=2; i<9; i+=3, j+=3, k+=3){
        if(comparePlayers(cursor[i], cursor[j]) && comparePlayers(cursor[j], cursor[k])){
            return comparePlayers(cursor[i], player1)?1:2;
        }
    }
    //check diagonal match
    if((comparePlayers(cursor[0], cursor[4]) && comparePlayers(cursor[4], cursor[8])) || (comparePlayers(cursor[2], cursor[4]) &&
            comparePlayers(cursor[4], cursor[6]))){
        return comparePlayers(cursor[4], player1)?1:2;
    }

    //Is it a draw? or still running?
    for(int i=0; i < 9; i++){
        if(cursor[i].getId() <0)  {return 0;}
    }


    //Game is draw
    return 3;

    //None of the above cases worked?


}

int TTTController::determineWinner(Board& board) {

    std::array<Player,9> cursor;
    cursor = board.getCursor();
    //Check column match
    for(int i=0, j=3, k=6; i<3; i++, j++, k++){
        if(comparePlayers(cursor[i], cursor[j]) && comparePlayers(cursor[j], cursor[k])){
            //std::cout << "i:" << i;
            return board.setWinner(comparePlayers(cursor[i], board.getPlayer(1))?1:2);
        }
    }

    //check row match
    for(int i=0, j=1, k=2; i<9; i+=3, j+=3, k+=3){
        if(comparePlayers(cursor[i], cursor[j]) && comparePlayers(cursor[j], cursor[k])){
            return board.setWinner(comparePlayers(cursor[i], board.getPlayer(1))?1:2);
        }
    }
    //check diagonal match
    if((comparePlayers(cursor[0], cursor[4]) && comparePlayers(cursor[4], cursor[8])) || (comparePlayers(cursor[2], cursor[4]) &&
            comparePlayers(cursor[4], cursor[6]))){
        return board.setWinner(comparePlayers(cursor[4], board.getPlayer(1))?1:2);
    }

    //Is it a draw? or still running?
    for(int i=0; i < 9; i++){
        if(cursor[i].getId() <0)  {return 0;}
    }


    //Game is tie/no room available
    return 3;

    //None of the above cases worked?


}

int TTTController::determineWinner(BigBoard &bigBoard) {
    std::array<Board,9> lBoard;
    lBoard = bigBoard.getLBoard();

    //check column match
    for(int i=0, j=3, k=6; i<3; i++, j++, k++){
        if(compareBoards(lBoard[i],lBoard[j]) && compareBoards(lBoard[j],lBoard[k]))
            return lBoard[i].getWinner();
    }

    //check row match
    for(int i=0, j=1, k=2; i<9; i+=3, j+=3, k+=3){
        if(compareBoards(lBoard[i],lBoard[j]) && compareBoards(lBoard[j],lBoard[k]))
            return lBoard[i].getWinner();
    }

    //check diagonal match
    if((compareBoards(lBoard[0], lBoard[4]) && compareBoards(lBoard[4], lBoard[8])) || (compareBoards(lBoard[2], lBoard[4]) &&
                                                                                          compareBoards(lBoard[4], lBoard[6]))){
        return lBoard[4].getWinner();
    }


    //Is it a draw? or still running?
    for(int i=0; i < 9; i++){
        if(!lBoard[i].getWinner())  {return 0;}
    }


    //Game is tie/no room available
    return 3;

    //None of the above cases worked?
}

//done
std::string TTTController::getGameDisplay(bool isJson) {
    if(!isJson) return getGameDisplay();

    std::string cursorStr;
    cursorStr += "{\"gameBoard\":[";

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cursorStr += "{\"row\":"; cursorStr += std::to_string(i) ; cursorStr+= ",\"col\":"; cursorStr+= std::to_string(j) +
                    ",\"marker\":\""; cursorStr.push_back(board.getCursor()[3*i+j].getSymbol()); cursorStr += "\"},";
        }
    }
    cursorStr.pop_back();
    cursorStr += "]}";
    return cursorStr;
}

std::string TTTController::getGameCursor() {
    std::array<Player,9> cursor = board.getCursor();

    std::string cursorStr;

    for(int i=0; i<9; i++){
        if(cursor[i].getId() == player1.getId()) cursorStr.push_back('1');
        else if(cursor[i].getId() == player2.getId()) cursorStr.push_back('2');
        else cursorStr.push_back('0');
    }

    return cursorStr;
}

//TODO
std::string TTTController::getGameDisplay() {
    std::array<Player,9> cursor = board.getCursor();
    std::string out = "";
    std::string hor = "-----";
    std::string lver = "|  ";
    std::string rver = "  |";
    std::string ver = "  |  ";

    // out += "\033[8A";   //Clear 8 lines up
    out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  "\n";
    out +=  lver ; out +=  cursor[0].getSymbol() ; out +=  ver ; out +=  cursor[1].getSymbol() ; out +=  ver ; out +=  cursor[2].getSymbol() ; out +=  rver ; out +=  "\n";

    out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  "\n";
    out +=  lver ; out +=  cursor[3].getSymbol() ; out +=  ver ; out +=  cursor[4].getSymbol() ; out +=  ver ; out +=  cursor[5].getSymbol() ; out +=  rver ; out +=  "\n";

    out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  "\n";
    out +=  lver ; out +=  cursor[6].getSymbol() ; out +=  ver ; out +=  cursor[7].getSymbol() ; out +=  ver ; out +=  cursor[8].getSymbol() ; out +=  rver ; out +=  "\n";
    out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  hor ; out +=  "+" ; out +=  "\n";
    return out;
}

//done
bool TTTController::comparePlayers(const Player &p1, const Player &p2){
    return p1.getId() == p2.getId();
}

bool TTTController::compareBoards(const Board &b1, const Board &b2) {
    switch (b1.getWinner() * b2.getWinner()){
        case 1: return true;
        case 4: return true;
        default: return false;
    }

    return false;
}

//done - maybe tweaks required
void TTTController::partParseJson(std::string &json, std::string &key) {
    unsigned long endCursor =0;
    unsigned long cursor = json.find(":");

    if(json.find(":\"")!= std::string::npos){
        cursor+=2;
        key = json.substr(cursor,json.find("\"",cursor)-cursor);
        endCursor = json.find("\"",cursor)+2;
    }
    else if(json.find(",")!= std::string::npos){
        cursor+=1;
        key = json.substr(cursor,json.find(",",cursor)-cursor);
        endCursor = json.find(",",cursor)+2;
    }
    else {
        cursor+=1;
        key = json.substr(cursor,json.find("}",cursor)-cursor);
        endCursor = json.find("}",cursor)+1;
    }

    json = json.substr(endCursor);

}

//done - any tweaks above should reflect here too
void TTTController::partParseJson(std::string &json, int &key) {
    unsigned long endCursor =0;
    unsigned long cursor = json.find(":");

    if(json.find(":\"")!= std::string::npos){
        cursor+=2;
        key = std::stoi(json.substr(cursor,json.find("\"",cursor)-cursor));
        endCursor = json.find("\"",cursor)+2;
    }
    else if(json.find(",")!= std::string::npos){
        cursor+=1;
        key = std::stoi(json.substr(cursor,json.find(",",cursor)-cursor));
        endCursor = json.find(",",cursor)+2;
    }
    else {
        cursor+=1;
        key = std::stoi(json.substr(cursor,json.find("}",cursor)-cursor));
        endCursor = json.find("}",cursor)+1;
    }

    json = json.substr(endCursor);

}

int main(){
    TTTController ttt;

    std::string temp = "john2";
    rapidjson::Document document;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.SetObject();
    rapidjson::Value tmp_val;
    tmp_val.SetString(&temp[0],temp.length(),allocator);
    document.AddMember("name",tmp_val,allocator);
    document.AddMember("marker","j",allocator);
    document.AddMember("playerNum",1, allocator);
    document.Accept(writer);
    ttt.createPlayer(buffer.GetString());
    auto& val = document["playerNum"];
    val.SetInt(2);
    auto& val2 = document["marker"];
    val2.SetString("a");
    auto& val3 = document["name"];
    val3.SetString("RV");
    buffer.Clear();
    writer.Reset(buffer);
    document.Accept(writer);
    ttt.createPlayer(buffer.GetString());
    std::cout << (ttt.player2.getSymbol() == 'a') << std::endl;

//
//
}