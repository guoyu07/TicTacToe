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

    /*
     * Test input string:
     * {"identifier":"P","gameType":"U","player1":{"name":"Raghuvaran6","marker":"R"},"player2":{"name":"Raghuvaran5","marker":"V"},"cursors":{"0":{"cursor":"121212121"},"1":{"cursor":"222000000"},"2":{"cursor":"121212121"},"3":{"cursor":"121212121"},"4":{"cursor":"011222001"},"5":{"cursor":"121222121"},"6":{"cursor":"121222121"},"7":{"cursor":"110221111"},"8":{"cursor":"121212121"}}}
     * */

    std::string inJsonRequest = inBuff.str();
    std::cin >> inJsonRequest;
    rapidjson::Document json;
    json.Parse(inJsonRequest.c_str());


    TTTController tttController;

    //switch with purpose of request -> "identifier" has purpose
    switch (json["identifier"].GetString()[0]) {
        case 'C': {
            if (json["name"].IsString() && json["marker"].IsString())
                tttController.createPlayer(json["name"].GetString(), json["marker"].GetString(), 1);
        }
        // 'C' Creates new player and returns all players; Hence no break statement
        case 'G': {
            std::cout << tttController.getAllSavedPlayers();
            break;
        }
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
            returnJson.AddMember("cursors",tmp_val,returnJson.GetAllocator());
            int winner = tttController.determineWinner();
            tmp_val.SetInt(winner);
            returnJson.AddMember("winner",tmp_val,returnJson.GetAllocator());

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            returnJson.Accept(writer);

            std::cout << buffer.GetString();

            /*Expected output for test input:
             *
             * {"cursors":{"0":{"cursor":"121212121","winner":1},"1":{"cursor":"222000000","winner":2},"2":{"cursor":"121212121","winner":1},"3":{"cursor":"121212121","winner":1},"4":{"cursor":"011222001","winner":2},"5":{"cursor":"121222121","winner":2},"6":{"cursor":"121222121","winner":2},"7":{"cursor":"110221111","winner":1},"8":{"cursor":"121212121","winner":1}},"winner":3}

             * */

            break;
        }

        default:
        std::cout << "{\"error\":147}";
    }
}