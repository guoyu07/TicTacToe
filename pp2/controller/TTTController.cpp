//
// Created by rchowda on 9/7/2016.
//

#include <iostream>
#include <cstring>
#include <limits>
#include "TTTController.h"
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
            json["name"].IsString() &&
            json["marker"].IsString())
        if(json.HasMember("playerNum") && json["playerNum"].IsInt())
            createPlayer(json["name"].GetString(),json["marker"].GetString(),json["playerNum"].GetInt());
        else
            createPlayer(json["name"].GetString(),json["marker"].GetString());
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

//done
std::string TTTController::getAllSavedPlayers() {
    PlayerDao playerDao;
    std::list<Player> playerList = playerDao.getAllPlayers();

    rapidjson::Document json;
    json.SetObject();
    auto& allocator = json.GetAllocator();
    rapidjson::Value players(rapidjson::kArrayType);
    for(auto p : playerList){
        rapidjson::Value player(rapidjson::kObjectType);
        rapidjson::Value tmp_val;
        tmp_val.SetString(p.getNameChar(),p.getName().length(),allocator);
        player.AddMember("name", tmp_val, allocator);
        tmp_val.SetString(p.getSymbolChar(),1,allocator);
        player.AddMember("marker", tmp_val,allocator);
        //Ultimate scores
        rapidjson::Value ultimate(rapidjson::kObjectType);
        ultimate.AddMember("win",tmp_val.SetInt(p.getUltStats()[0]),allocator);
        ultimate.AddMember("loss",tmp_val.SetInt(p.getUltStats()[1]), allocator);
        ultimate.AddMember("tie", tmp_val.SetInt(p.getUltStats()[2]), allocator);
        //Regular scores
        rapidjson::Value regular(rapidjson::kObjectType);
        regular.AddMember("win", tmp_val.SetInt(p.getRegStats()[0]), allocator);
        regular.AddMember("loss",tmp_val.SetInt(p.getRegStats()[1]), allocator);
        regular.AddMember("tie", tmp_val.SetInt(p.getRegStats()[2]), allocator);
        //Group scores
        rapidjson::Value stats(rapidjson::kObjectType);
        stats.AddMember("ultimate",ultimate,allocator);
        stats.AddMember("regular",regular,allocator);

        //Add stats to player info
        player.AddMember("stats",stats,allocator);

        //Append to final json array
        players.PushBack(player,allocator);
    }
    json.AddMember("players",players,allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json.Accept(writer);
    return buffer.GetString();

}

//done - maybe later tweak
void TTTController::startNewGame() {
    board = Board(player1,player2);
    bigBoard = BigBoard(player1,player2);
}

void TTTController::startNewGame(bool isGameRegular) {
    if(isGameRegular) {
        TTTController::isGameRegular = isGameRegular;
        board = Board(player1,player2);
    } else
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
            return setSelectionBB(json["row"].GetInt(), json["col"].GetInt(), json["outerRow"].GetInt(),
                                  json["outerCol"].GetInt(), json["currentPlayer"].GetInt());
        else
            return setSelection(json["row"].GetInt(), json["col"].GetInt(),json["currentPlayer"].GetInt());
    else
        return false;
}

//done -- used by Regular
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

//done -- used by Regular
bool TTTController::setSelection(int pos, int currentPlayer) {
    switch(currentPlayer){
        case 1: return setSelection(player1,pos);
        case 2: return setSelection(player2,pos);
        default: return false;
    }
}

//done -- used by Regular
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

//done inherently -- used by Ultimate
bool TTTController::setSelectionBB(const Player &player, int pos, Board &board) {

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

bool TTTController::setSelectionBB(int row, int col, int outerRow, int outerCol, int currentPlayer){
    if(!(row>=0 && row <=2 && col >=0 && col <= 2)) return false;
    if(!(outerRow>=0 && outerRow <=2 && outerCol >=0 && outerCol <= 2)) return false;
    int outPos = 3*outerRow+outerCol;
    int inPos  = 3 * row + col;
    return setSelectionBB(inPos,outPos,currentPlayer);
}

//done -- used by Ultimate
bool TTTController::setSelectionBB(int inPos, int outPos, int currentPlayer) {
    if(inPos<0 || inPos >8 || outPos <0 || outPos >8) return false;
    std::array<Board,9> board = bigBoard.getLBoard();
    switch (currentPlayer) {
        case 1:
            if(setSelectionBB(player1, inPos, board.at(outPos)) ){
                bigBoard.setLBoard(board);
                return true;
            };
        case 2:
            if(setSelectionBB(player2, inPos, board.at(outPos)) ){
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
    //game: R - Regular, U - Ultimate
    //result: 1 - win , 2 - loss, 3 - tie
    PlayerDao playerDao;
    char game_char;
    int winner;
    if(isGameRegular) {
        game_char = 'R';
        winner = determineWinner(board);
    }else{
        game_char = 'U';
        winner = determineWinner(bigBoard);
    }
        switch (winner){
            case 1: playerDao.updatePlayerScore(player1,game_char,1);
                playerDao.updatePlayerScore(player2,game_char,2); break;
            case 2: playerDao.updatePlayerScore(player1,game_char,2);
                playerDao.updatePlayerScore(player2,game_char,1); break;
            case 3: playerDao.updatePlayerScore(player1,game_char,3);
                playerDao.updatePlayerScore(player2,game_char,3); break;
        }
    return winner;

    
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
    return board.setWinner(3);

    //None of the above cases worked?


}

int TTTController::determineWinner(BigBoard &bigBoard) {
    std::array<Board,9>& lBoard = bigBoard.getLBoard();

    for(Board& b : lBoard){
        determineWinner(b);
    }

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


std::string TTTController::getGameDisplay(bool isJson) {
    if(!isJson) return getGameDisplay();

    const std::array<Board,9>lBoard = bigBoard.getLBoard();
    rapidjson::Document json;
    json.SetObject();
    auto& allocator = json.GetAllocator();

    rapidjson::Value index, cursor, winner;
    rapidjson::Value boardCursor;
    boardCursor.SetObject();
    std::string tmp_cursor;

    if(isGameRegular){
        tmp_cursor = getGameCursor(board);
        index.SetString("0",1,allocator);
        cursor.SetString(tmp_cursor.c_str(),tmp_cursor.length(),allocator);
        winner.SetInt(determineWinner(board));

        boardCursor.AddMember("cursor",cursor,allocator);
        boardCursor.AddMember("winner",winner,allocator);

        json.AddMember(index,boardCursor,allocator);
    }else

        for(unsigned int i = 0; i < 9; i++){
            boardCursor.SetObject();
            boardCursor.RemoveAllMembers();

            Board b = lBoard.at(i);

            index.SetString(std::to_string(i).c_str(),1,allocator);
            tmp_cursor = getGameCursor(b);

            winner.SetInt(determineWinner(b));
            cursor.SetString(tmp_cursor.c_str(),tmp_cursor.length(),allocator);

            boardCursor.AddMember("cursor",cursor,allocator);
            boardCursor.AddMember("winner",winner,allocator);

            json.AddMember(index,boardCursor,allocator);
        }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json.Accept(writer);

    return buffer.GetString();
}

std::string TTTController::getGameCursor(const Board& board) {
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
    if(isGameRegular) return getGameDisplay(board);
    else
        return  getGameDisplay(bigBoard);

}

std::string TTTController::getGameDisplay(Board& board) {
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

std::string TTTController::getGameDisplay(BigBoard &bigBoard) {
    std::string returnStr;
    int i=1;
    for(Board b : bigBoard.getLBoard()){
        returnStr += std::to_string(i++) + ":\n";
        returnStr += getGameDisplay(b);
    }
    return returnStr;
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

//int main(){
//    TTTController ttt;
//
//    std::cout << ttt.getAllSavedPlayers() <<std::endl;
//    std::string temp = "Raghuvaran6";
//    rapidjson::Document document;
//    rapidjson::StringBuffer buffer;
//    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
//    document.SetObject();
//    rapidjson::Value tmp_val;
//    tmp_val.SetString(&temp[0],temp.length(),allocator);
//    document.AddMember("name",tmp_val,allocator);
//    document.AddMember("marker","j",allocator);
//    document.AddMember("playerNum",1, allocator);
//    document.Accept(writer);
//    ttt.createPlayer(buffer.GetString());
//    auto& val = document["playerNum"];
//    val.SetInt(2);
//    auto& val2 = document["marker"];
//    val2.SetString("2");
//    auto& val3 = document["name"];
//    val3.SetString("Raghuvaran5");
//    buffer.Clear();
//    writer.Reset(buffer);
//    document.Accept(writer);
//    ttt.createPlayer(buffer.GetString());
//    std::cout << (ttt.player2.getSymbol() == 'R') << std::endl;
//    ttt.startNewGame(0);
    //diagonal check
//    std::cout << ttt.setSelectionBB(0,0,0,0,2);
//    std::cout << ttt.setSelectionBB(1,1,0,0,2);
//    std::cout << ttt.setSelectionBB(2,2,0,0,2);
//
//    std::cout << ttt.setSelectionBB(0,0,1,1,2);
//    std::cout << ttt.setSelectionBB(1,1,1,1,2);
//    std::cout << ttt.setSelectionBB(2,2,1,1,2);
//
//    std::cout << ttt.setSelectionBB(0,0,2,2,2);
//    std::cout << ttt.setSelectionBB(1,1,2,2,2);
//    std::cout << ttt.setSelectionBB(2,2,2,2,2);

    //column check
//    std::cout << ttt.setSelectionBB(0,0,0,0,1);
//    std::cout << ttt.setSelectionBB(0,1,0,0,1);
//    std::cout << ttt.setSelectionBB(0,2,0,0,1);
//
//    std::cout << ttt.setSelectionBB(0,0,1,0,1);
//    std::cout << ttt.setSelectionBB(0,1,1,0,1);
//    std::cout << ttt.setSelectionBB(0,2,1,0,1);
//
//    std::cout << ttt.setSelectionBB(0,0,2,0,1);
//    std::cout << ttt.setSelectionBB(0,1,2,0,1);
//    std::cout << ttt.setSelectionBB(0,2,2,0,1);

    //row check
//    std::cout << ttt.setSelectionBB(0,0,0,0,1);
//    std::cout << ttt.setSelectionBB(1,0,0,0,1);
//    std::cout << ttt.setSelectionBB(2,0,0,0,1);
//
//    std::cout << ttt.setSelectionBB(0,0,0,1,1);
//    std::cout << ttt.setSelectionBB(1,0,0,1,1);
//    std::cout << ttt.setSelectionBB(2,0,0,1,1);
//
//    std::cout << ttt.setSelectionBB(0,0,0,2,1);
//    std::cout << ttt.setSelectionBB(1,0,0,2,1);
//    std::cout << ttt.setSelectionBB(2,0,0,2,1);

    //tie 1
//
//    std::cout << ttt.setSelectionBB(0,0,0,0,1);
//    std::cout << ttt.setSelectionBB(1,1,0,0,1);
//    std::cout << ttt.setSelectionBB(2,2,0,0,1);
//    std::cout << ttt.setSelectionBB(0,0,0,1,2);
//    std::cout << ttt.setSelectionBB(1,1,0,1,2);
//    std::cout << ttt.setSelectionBB(2,2,0,1,2);
//    std::cout << ttt.setSelectionBB(0,0,0,2,1);
//    std::cout << ttt.setSelectionBB(1,1,0,2,1);
//    std::cout << ttt.setSelectionBB(2,2,0,2,1);
//
//    std::cout << ttt.setSelectionBB(0,0,1,0,2);
//    std::cout << ttt.setSelectionBB(1,1,1,0,2);
//    std::cout << ttt.setSelectionBB(2,2,1,0,2);
//    std::cout << ttt.setSelectionBB(0,0,1,1,2);
//    std::cout << ttt.setSelectionBB(1,1,1,1,2);
//    std::cout << ttt.setSelectionBB(2,2,1,1,2);
//    std::cout << ttt.setSelectionBB(0,0,1,2,1);
//    std::cout << ttt.setSelectionBB(1,1,1,2,1);
//    std::cout << ttt.setSelectionBB(2,2,1,2,1);
//
//    std::cout << ttt.setSelectionBB(0,0,2,0,1);
////    std::cout << ttt.setSelection(1,1,2,0,1);
//    std::cout << ttt.setSelection("{\"row\":1,\"col\":1,\"currentPlayer\":1,\"outerRow\":2,\"outerCol\":0}");
//    std::cout << ttt.setSelectionBB(2,2,2,0,1);
//    std::cout << ttt.setSelectionBB(0,0,2,1,1);
//    std::cout << ttt.setSelectionBB(1,1,2,1,1);
//    std::cout << ttt.setSelectionBB(2,2,2,1,1);
//    std::cout << ttt.setSelectionBB(0,0,2,2,2);
//    std::cout << ttt.setSelectionBB(1,1,2,2,2);
//    std::cout << ttt.setSelectionBB(2,2,2,2,2);
//
//
//
//    std::cout << ttt.getGameDisplay(ttt.bigBoard) << std::endl;
//    std::cout << ttt.determineWinner() << std::endl;
//
//    std::cout << ttt.getGameDisplay(true) << std::endl;

//
//    rapidjson::Document document1;
//    std::string sample = "{\"identifier\":\"P\",\"gameType\":\"U\",\"player1\":{\"name\":\"Raghu\",\"marker\":9},\"player2\":{\"name\":\"Raghu\",\"marker\":9},\"cursors\":{\"0\":{\"cursor\":110011022}}}";
//    document1.Parse(sample.c_str());
//    int i = 0;
//    std::cout << document1["cursors"][std::to_string(i).c_str()]["cursor"].GetInt();
//
//
//
//
//}