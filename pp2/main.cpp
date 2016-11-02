#include <iostream>
#include <sstream>
#include <fstream>

#include "controller/TTTController.h"
#include "lib/rapidjson/document.h"
#include "lib/rapidjson/stringbuffer.h"
#include "lib/rapidjson/writer.h"

std::string stringOf(rapidjson::Value& json){
    if(json.GetType() == 6) return std::to_string(json.GetInt());
    else if(json.GetType() == 5) return json.GetString();
    else return std::string();
}

int main() {
    std::string stringOf(rapidjson::Value& json);
    std::cout << "content-type: text/html\n\n";

    //receive json into string
    std::stringstream inBuff;

    std::string inJsonRequest = inBuff.str();
    std::cin >> inJsonRequest;
    rapidjson::Document json;
    json.Parse(inJsonRequest.c_str());


    TTTController tttController;

    //switch with purpose of request -> "identifier" has purpose
    switch (json["identifier"].GetString()[0]) {
        case 'G':
            std::cout << tttController.getAllSavedPlayers(); break;
        //'G' -> @return getAllSavedPlayers
        case 'P': {
            //'P' -> has
            /*
             * Player1: Name, Marker
             * Player2: Name, Marker
             * Cursor: All positions; 1- as P1 marker, 2- as P2 marker, 0- as not yet marked
             *
             * @return: getGameDisplay(true); determineWinner
             * */
            std::array<std::string,9> cursor;
            //TODO validate json before using

            //parse and create new players
            tttController.createPlayer(json["player1"]["name"].GetString(), stringOf(json["player1"]["marker"]), 1);
            tttController.createPlayer(json["player2"]["name"].GetString(), stringOf(json["player2"]["marker"]), 2);

            //start desired game
            tttController.startNewGame(json["gameType"].GetString()[0] == 'R');

            //parse boardCursor into array
            for(unsigned int i=0; i<9; i++){
                cursor.at(i) = stringOf(json["cursors"][std::to_string(i).c_str()]["cursor"]);
            }

            // setSelection accordingly
            for(int outer = 0; outer < 9; outer++) {
                std::string board = cursor[outer];
                for (int inner = 0; inner < 9; inner++) {

                    if (board[inner] == '1') tttController.setSelectionBB(inner, outer, 1);
                    else if (board[inner] == '2') tttController.setSelectionBB(inner, outer, 2);
                }
            }

            // return boards with respective cursors and winner
            rapidjson::Document returnJson;
            returnJson.SetObject();
            std::string gameDisplay = tttController.getGameDisplay(true);
            json.Parse(gameDisplay.c_str());
            rapidjson::Value& tmp_val = json;
            //tmp_val.SetString(gameDisplay.c_str(),gameDisplay.length(),returnJson.GetAllocator());
            returnJson.AddMember("cursors",tmp_val,returnJson.GetAllocator());
            int winner = tttController.determineWinner();
            tmp_val.SetInt(winner);
            returnJson.AddMember("winner",tmp_val,returnJson.GetAllocator());
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            returnJson.Accept(writer);
            std::cout << buffer.GetString();

            break;
        }
        case 'X': {
            std::string player_name, player_marker;
            tttController.partParseJson(inJsonRequest, player_name);
            tttController.partParseJson(inJsonRequest, player_marker);
            if (player_name == "" || player_marker == "") {}
            else tttController.createPlayer(player_name, player_marker, 1);
        }
        case 'Y':{
            std::string player_name, player_marker;
            tttController.partParseJson(inJsonRequest, player_name);
            tttController.partParseJson(inJsonRequest, player_marker);
            if(player_name =="" || player_marker =="") {}
                else tttController.createPlayer(player_name, player_marker, 2);


            tttController.startNewGame();
            std::string players;

            players += "{\"players\":[";
            players += "{\"name\":\"" + tttController.player1.getName() + "\",\"marker\":\"" + tttController.player1.getSymbol() + "\",\"id\":" +  std::to_string(tttController.player1.getId()) + "},";
            players += "{\"name\":\"" + tttController.player2.getName() + "\",\"marker\":\"" + tttController.player2.getSymbol() + "\",\"id\":" + std::to_string(tttController.player2.getId()) + "}";
            players += "]}";
            std::cout << players;
            break;
        }
        default:
        std::cout << "{\"error\":147}";
    }
}