#include "common.h"

const string PlayerOneDef= "{\"name\": \"Player1\" ,\"marker\": \"X\"}";
const string PlayerOne= "{\"name\": \"Player1\" ,\"marker\": \"X\", \"playerNum\":1}";
const string PlayerTwo= "{\"name\": \"Player2\" ,\"marker\": \"O\", \"playerNum\":2}";

/* Main Function */
int main()
{
    TTTController controller;

#ifdef SET_PLAYER_DEF_PARA
    setPlayerDefaultPara(controller);
#else    
    setPlayer(controller);
#endif    
    
    controller.startNewGame();
    showGameDisplay(controller);
        
    testCase1(controller);
    
    controller.startNewGame();
    testCase2(controller);
    
     return 0;
}

void setPlayer(TTTController& controller){
controller.createPlayer(PlayerOne);
    controller.createPlayer(PlayerTwo);
    cout << "Testing setPlayer without default parameter" << endl;
}

void setPlayerDefaultPara(TTTController& controller){
    controller.createPlayer(PlayerOneDef);
    controller.createPlayer(PlayerTwo);
    cout << "Testing setPlayer with default parameter" << endl;
}

void showGameDisplay(TTTController& controller){
    string gameDisplay = "";
    bool isJson = true;
    gameDisplay = controller.getGameDisplay(isJson);
    cout << gameDisplay << endl;
}

void testCase1(TTTController& controller){

    bool bStatus = false;
    bool bSelect = false;
    int aWin = -1;

    // Test case for Player 2 to WIN
    //Step1
    bSelect = controller.setSelection("{\"row\":0, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase1: step1 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase1: step1 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step1", goto Cleanup);
    
    //Step2
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step2 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step2 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner(); 
    makeAssert(aWin == 0, "Failed testCase1 after step2", goto Cleanup);
     
    //Step3
    bSelect = controller.setSelection("{\"row\":0, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step3 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase1: step3 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step3", goto Cleanup);
    
    //Step4
    bSelect = controller.setSelection("{\"row\":2, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step4 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase1: step4 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step4", goto Cleanup);
    
    //Step5
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 2,\"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase1: step5 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 2,\"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step5 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step5", goto Cleanup);
    
    //Step6
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step6 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step6 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step6", goto Cleanup);
    
    //Step7
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase1: step7 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step7 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step7", goto Cleanup);
    
    //Step8
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step8 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step8 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step8", goto Cleanup);
    
    //Step9
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step9 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step9 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step9", goto Cleanup);
    
    
    //Step10
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step10 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase1: step10 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step10", goto Cleanup);
    
    
    //Step11
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step11 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step11 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step11", goto Cleanup);
        

    //Step12
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step12 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step12 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step12", goto Cleanup);
    
    
    //Step13
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase1: step13 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step13 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase1 after step13", goto Cleanup);
    
    //Step14
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase1: step14 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase1: step14 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 2, "Failed testCase1 after step14", goto Cleanup);
  
    bStatus = true;
Cleanup:
    if(bStatus){
        cout << "TestCase1 with  Player2  as winner is successful" << endl;
    }

    return;        
}

void testCase2(TTTController& controller){

    bool bStatus = false;
    bool bSelect = false;
    int aWin = -1;

    // Test case for TIE
    //Step1
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step1 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step1 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step1", goto Cleanup);
    

    //Step2
    bSelect = controller.setSelection("{\"row\":2, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step2 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step2 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step2", goto Cleanup);
    
    //Step3
    bSelect = controller.setSelection("{\"row\":1, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step3 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step3 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step3", goto Cleanup);
    

    //Step4
    bSelect = controller.setSelection("{\"row\":1, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step4 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step4 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step4", goto Cleanup);
    

    //Step5
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step5 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step5 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step5", goto Cleanup);
    
    
    //Step6
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step6 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step6 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step6", goto Cleanup);
    
    
    //Step7
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step7 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCas2: step7 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step7", goto Cleanup);
    
    
    //Step8
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step8 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step8 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step8", goto Cleanup);
    
    
    //Step9
    bSelect = controller.setSelection("{\"row\":0, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step9 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCas2: step9 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step9", goto Cleanup);
    
    
    //Step10
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step2 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step10 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step10", goto Cleanup);
    

    //Step11
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step11 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step11 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step11", goto Cleanup);
        

    //Step12
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step12 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step12 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step12", goto Cleanup);
    
    
    //Step13
    bSelect = controller.setSelection("{\"row\":0, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step13 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step13 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step13", goto Cleanup);
    
    
    //Step14
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step14 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step14 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step14", goto Cleanup);
    

    //Step15
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step15 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step15 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step15", goto Cleanup);
    

    //Step16
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step16 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step16 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step16", goto Cleanup);
    
    
    //Step17
    bSelect = controller.setSelection("{\"row\":1, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step17 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step17 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step17", goto Cleanup);
    

    //Step18
    bSelect = controller.setSelection("{\"row\":0, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step18 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step18 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step18", goto Cleanup);

    //Step19
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step19 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step19 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step19", goto Cleanup);
    

    //Step20
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step20 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step20 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step20", goto Cleanup);
    
    
    //Step21
    bSelect = controller.setSelection("{\"row\":0, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 2, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step21 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step21 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step21", goto Cleanup);
    
    
    //Step22
    bSelect = controller.setSelection("{\"row\":2, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step22 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 2, \"outerRow\": 2, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step22 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step22", goto Cleanup);
    

    //Step23
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 1}");
    makeAssert(bSelect, "Failed testCase2: step23 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step23 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step23", goto Cleanup);
    
    
    //Step24
    bSelect = controller.setSelection("{\"row\":0, \"col\":2, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step24 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":1, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step24 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step24", goto Cleanup);
    
    
    //Step25
    bSelect = controller.setSelection("{\"row\":2, \"col\":1, \"currentPlayer\": 1, \"outerRow\": 1, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step25 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":0, \"col\":1, \"currentPlayer\": 2, \"outerRow\": 1, \"outerCol\": 2}");
    makeAssert(bSelect, "Failed testCase2: step25 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 0, "Failed testCase2 after step25", goto Cleanup);
    
    
    //Step26
    bSelect = controller.setSelection("{\"row\":1, \"col\":0, \"currentPlayer\": 1, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step26 setSelection player1", goto Cleanup);
    bSelect = controller.setSelection("{\"row\":2, \"col\":0, \"currentPlayer\": 2, \"outerRow\": 0, \"outerCol\": 0}");
    makeAssert(bSelect, "Failed testCase2: step26 setSelection player2", goto Cleanup);
    aWin = controller.determineWinner();
    makeAssert(aWin == 3, "Failed testCase2 after step26", goto Cleanup);
    
    bStatus = true;
Cleanup:
    if(bStatus){
        cout << "TestCase2 with tie is successful" << endl;
    }

    return;
}
