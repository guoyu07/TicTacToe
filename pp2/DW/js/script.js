// JavaScript Document
var cgiPath = "cgi-bin/ttt.cgi";

//start-test //TODO delete
// $('.outer').each(function () {
//     if($(this).attr("pos") == 2){
//         $(this).children().hide()
//         $(this).text('x');
//     }
// });
var marker = 'o';
//end-test

//Players
var player = {
    1:{ "name": "RV",
        "marker" :'o'

    }, 2:{"name": "SW",
        "marker" :'w'

    },3:{
        "marker" : "X" //Game tie = 3
    }

};

var currentPlayer = {
    "name" : "",
    "marker" : ""
};

var winner = 0;
var recent ={
    "outerPos" : -1,
    "innerPos" : -1
};

currentPlayer = player[1];

//Cursors
var cursors = {
    0: {"cursor" : "000000000", "winner" : 0},
    1: {"cursor" : "000000000", "winner" : 0},
    2: {"cursor" : "000000000", "winner" : 0},
    3: {"cursor" : "000000000", "winner" : 0},
    4: {"cursor" : "000000000", "winner" : 0},
    5: {"cursor" : "000000000", "winner" : 0},
    6: {"cursor" : "000000000", "winner" : 0},
    7: {"cursor" : "000000000", "winner" : 0},
    8: {"cursor" : "000000000", "winner" : 0}
};


// outerPos = 0...9;
// innerPos = 0...9
// marker = Player marker
function setMarkerInCell(outerPos, innerPos, marker) {
    outerPos = Number(outerPos);
    innerPos = Number(innerPos);
$('.outer').each(function () {
    //Every 'outer' div comes-into $this
    if($(this).attr("pos") == outerPos){
        //Board at @outerPos comes-into $this; But we have 3 '.rows' <div>s inside each board
        $(".row",this).children().each(function () {
            //All 9 '.inner' <div>s come-into $this
            if($(this).attr("pos") == innerPos){
                //<div> at @innerPos comes-into $this
                $(this).text(marker);
                //Update local @cursors
                var temp_char = '0';

                if(marker == player[1].marker){
                    temp_char = '1';
                }else {
                    temp_char = '2';
                }

                var temp_cur = cursors[outerPos].cursor;

                temp_cur = temp_cur.substring(0,innerPos) + temp_char + temp_cur.substring(innerPos+1);
                cursors[outerPos].cursor = temp_cur;
            }
        })
    }
})

}

function setMarkerOnBoard(outerPos,marker) {
$('.outer').each(function () {
    if($(this).attr("pos") == outerPos){
        $(this).children().hide()
        $(this).text(marker);
    }
})

}

function togglePlayer(){
    if(currentPlayer == player[1]) currentPlayer = player[2];
    else currentPlayer = player[1];
}



//***********Play starts here ********************//
lockAllBoard(false); //unlocks all board pieces

getAttentionOf(1,false);






//***********Play ends here ********************//

function getAttentionOf(board,set) {
    var outerPos = Number(board);
    set = Boolean(set);
    $('.outer').each(function () {
        if($(this).attr("pos") == board){
            $(this).children().children('.inner').each(function () {

                var innerPos = $(this).attr("pos");

                var onClickHandler =  function (event){
                    //$(div).text(marker);
                    setMarkerInCell(outerPos,innerPos,currentPlayer.marker);
                    console.log("Board:" + innerPos + ", at: " + outerPos);
                    console.log(cursors);
                    //$(this).off('click',onClickHandler);
                    //update @recent variable
                    recent.outerPos = outerPos;
                    recent.innerPos = innerPos;

                    //inform() will take care of locking and unlocking
                    inform();

                    togglePlayer();
                };
                console.log("Is board "+board+" locked? "+set);
                //TODO donot unlock if cursor at @innerPos is '0'
                if(set && cursors[outerPos].cursor[innerPos] == 0){
                    console.log("Unlocked"+board);
                    $(this).on('click',onClickHandler);
                }
                else {
                    console.log("Locked"+board);
                    // $(this).off('click',onClickHandler);
                    $(this).unbind('click');
                }
            })
        }
    })
}

function getCursor(boardNumber) {
    boardNumber = 0;
    //innerPos = index of @boardNumber in game
    //cursor = final string with 1's and 2's respectively for players 1 and 2 and available slots with 0
    var innerPos, markerBuff,  cursor = "000000000";
    $('.outer').each(function () {
        if($(this).attr("pos") == boardNumber){
            $('.row', this).children().each(function () {
                innerPos = $(this).attr("pos");
                markerBuff = $(this).text();
                cursor = cursor.substring(0,innerPos-1) + '1' + cursor.substring(innerPos,9);
            })
        }
    })

}

function inform(){
    //lock all board
    lockAllBoard(true);

    //Get game cursors**********************************************//*//
    var request = {                                                 //*//
        "identifier" : "P",                                         //*//
        "gameType" : "U",                                           //*//
        "player1" :{                                                //*//
            "name": "",                                             //*//
            "marker": ""                                            //*//
        },                                                          //*//
        "player2" :{                                                //*//
            "name": "",                                             //*//
            "marker": ""                                            //*//
        },                                                          //*//
        "cursors": {}                                               //*//
    };                                                              //*//
    request.player1 = player[1];                                    //*//
    request.player2 = player[2];                                    //*//
    request.cursors = cursors;                                      //*//

    //send it
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST",cgiPath,true);
    xhttp.send(JSON.stringify(request));
    console.log(JSON.stringify(request));


    //on receiving response from CGI
    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200) {
            //parse it
            var response = JSON.parse(this.responseText);
            console.log(JSON.stringify(response));

            //update cursors
            cursors = response.cursors;
            winner = Number(response.winner);

            //Mark board  //TODO may be cell too?
            for(var i=0; i<9; i++){
                //Set Marker of player[winner]
                if(cursors[i].winner) setMarkerOnBoard(i,player[cursors[i].winner].marker);
            }

            //Did anyone win?
            if(winner){
                //Delcare
                console.log("Game won by : " + winner); //TODO
            }else {

                //whats next board?
                var toBeUnlocked = nextBoard();
                console.log("toBeUnlocked : " + toBeUnlocked);
                //unlock board accordingly
                if(toBeUnlocked<0){
                    lockAllBoard(false);
                }else{
                    getAttentionOf(toBeUnlocked,true);
                }
            }
        }

    };

}


function nextBoard() {
    //current input
    //and
    //next board status i.e. if no room is available

   // var outerPos = Number(recent.outerPos);
    var innerPos = Number(recent.innerPos);

    if(cursors[innerPos].winner){
        return -1;
    }else{
        return innerPos;
    }

}


function lockAllBoard(lock) {
    lock = Boolean(lock);
    console.log("lock:"+ lock);
    console.log("!lock:"+ !lock);
    for (var i = 0; i < 9; i++) {
        getAttentionOf(i,!lock);
    }
}