// JavaScript Document
var cgiPath = "cgi-bin/ttt.cgi";
var gameType;
if($('meta[name="keywords"]').attr('content') == 'R') gameType = "regular";
else gameType = "ultimate";
//start-test //TODO delete
// $('.outer').each(function () {
//     if($(this).attr("pos") == 2){
//         $(this).children().hide()
//         $(this).text('x');
//     }
// });
//end-test

//Players
var player = {
    1:{ "name": "RV2",
        "marker" :'o',
        "stats" : {
            "regular" :{
                "win" :0,
                "loss" : 0,
                "tie" : 0
            },
            "ultimate" :{
                "win" :0,
                "loss" : 0,
                "tie" : 0
            }
        }

    }, 2:{"name": "SW",
        "marker" :'w',
        "stats" : {
            "regular" :{
                "win" :0,
                "loss" : 0,
                "tie" : 0
            },
            "ultimate" :{
                "win" :0,
                "loss" : 0,
                "tie" : 0
            }
        }

    },3:{
        "marker" : "X" //Game tie = 3
    }

};

var arePlayersSet = {
    1:false,
    2:false
};

var isGameRunning = false;

var allPlayers = {};

var currentPlayer = 1;

var winner = 0;
var recent ={
    "outerPos" : -1,
    "innerPos" : -1
};

//Cursors
var cursors = {};

function drawBorders(box) {
    $(box).each(function() {
        var pos = $(this).attr('pos');
        console.log(pos);
        pos = Number(pos);
        switch (pos){
            case 0: $(this).css('border-style','none solid solid none'); break;
            case 1: $(this).css('border-style','none solid solid solid'); break;
            case 2: $(this).css('border-style','none none solid solid'); break;
            case 3: $(this).css('border-style','solid solid solid none'); break;
            case 4: $(this).css('border-style','solid solid solid solid'); break;
            case 5: $(this).css('border-style','solid none solid solid'); break;
            case 6: $(this).css('border-style','solid solid none none'); break;
            case 7: $(this).css('border-style','solid solid none solid'); break;
            case 8: $(this).css('border-style','solid none none solid'); break;
        }
    });

}

function highlightBox(pos,set){
    pos = Number(pos);
    if(cursors[pos].winner) return;
    //Highlight or un-highlight all if pos is '9'
    if(pos == 9) {
        for(var i=0; i<9; i++){
            highlightBox(i,set);
        }
        return;
    }
    $('.outer').each(function() {
        if($(this).attr('pos') == pos){
            if(set)  $(this).addClass('boxHighlight');
            else  $(this).removeClass('boxHighlight');
        }
    });

}


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

                    if(currentPlayer == 1){
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

function setMarkerOnBoard(outerPos,marker,winner) {
    $('.outer').each(function () {
        if($(this).attr("pos") == outerPos){
            $(this).children().hide();
            $(this).text(marker);

            if(currentPlayer == 1){
                temp_char = '1';
            }else {
                temp_char = '2';
            }

            var temp_cur = cursors[0].cursor;

            temp_cur = temp_cur.substring(0,outerPos) + temp_char + temp_cur.substring(outerPos+1);
            cursors[0].cursor = temp_cur;

            $(this).addClass('innerWinner');
            if(winner == 3) $(this).addClass('innerTie');
        }
    })

}

function togglePlayer(){
    var focus = 'bs-callout-primary';
    if(currentPlayer == 1){
        currentPlayer = 2;
        $('#playerBoard1').removeClass(focus);
        $('#playerBoard2').addClass(focus);
    }
    else {
        currentPlayer = 1;
        $('#playerBoard2').removeClass(focus);
        $('#playerBoard1').addClass(focus);
    }
    console.log(currentPlayer);
}



//***********Play starts here ********************//

initializeGame();

function initializeGame() {

    player = {
        1:{ "name": "RV2",
            "marker" :'o',
            "stats" : {
                "regular" :{
                    "win" :0,
                    "loss" : 0,
                    "tie" : 0
                },
                "ultimate" :{
                    "win" :0,
                    "loss" : 0,
                    "tie" : 0
                }
            }

        }, 2:{"name": "SW",
            "marker" :'w',
            "stats" : {
                "regular" :{
                    "win" :0,
                    "loss" : 0,
                    "tie" : 0
                },
                "ultimate" :{
                    "win" :0,
                    "loss" : 0,
                    "tie" : 0
                }
            }

        },3:{
            "marker" : "X" //Game tie = 3
        }

    };

    arePlayersSet = {
        1:false,
        2:false
    };

    isGameRunning = false;

    allPlayers = {};
    currentPlayer = 1;

    winner = 0;
    recent ={
        "outerPos" : -1,
        "innerPos" : -1
    };

    cursors = {
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

    drawBorders('.outer');
    drawBorders('.inner');
    getAllPlayers();
}

function startGame() {
    //clear screen
    $('#createPlayer').children()
        .removeClass('show')
        .addClass('hide');

    //
    isGameRunning = true;

    //to focus initial player
    currentPlayer = 2;
    togglePlayer();

    lockAllBoard(false); //unlocks all board pieces
}
//getAttentionOfBB(1,false);






//***********Play ends here ********************//

function getAttentionOfBB(board, set) {
    var outerPos = Number(board);
    set = Boolean(set);
    highlightBox(board,set);
    $('.outer').each(function () {
        if($(this).attr("pos") == board){
            $(this).children().children('.inner').each(function () {

                var innerPos = $(this).attr("pos");

                var onClickHandler =  function (event){
                    //$(div).text(marker);
                    setMarkerInCell(outerPos,innerPos,player[currentPlayer].marker);
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

function getAttentionOfB(board, set) {
    var outerPos = Number(board);
    set = Boolean(set);
    $('.outer').each(function () {
        if($(this).attr("pos") == board){
            
            var onClickHandler =  function (event){
                //$(div).text(marker);
                setMarkerOnBoard(outerPos,player[currentPlayer].marker);
                console.log("Board:" + outerPos);
                console.log(cursors);
                //$(this).off('click',onClickHandler);
                //update @recent variable
                recent.outerPos = outerPos;

                //inform() will take care of locking and unlocking
                inform();

                togglePlayer();
            };
            
            
            console.log("Is board "+board+" locked? "+set);
            //TODO donot unlock if cursor at @innerPos is '0'
            if(set && cursors[0].cursor[outerPos] == 0){
                console.log("Unlocked"+board);
                $(this).on('click',onClickHandler);
            }
            else {
                console.log("Locked"+board);
                // $(this).off('click',onClickHandler);
                $(this).unbind('click');
            }
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
        "gameType" : "",                                           //*//
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
    if(gameType == "regular")
        request.gameType = "R";
    else request.gameType = "U";
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

            if(gameType == "regular") processRegular();
            else processUltimate();

        }

    };

}

function processUltimate() {
    //Mark board  //TODO may be cell too?
    for(var i=0; i<9; i++){
        //Set Marker of player[winner]
        if(cursors[i].winner) setMarkerOnBoard(i,player[cursors[i].winner].marker,cursors[i].winner);
    }

    //Did anyone win?
    if(winner){
        //Declare
        console.log("Game won by : " + winner); //TODO
        getAllPlayers();
        declareWinner();
    }else {

        //whats next board?
        var toBeUnlocked = nextBoard();
        console.log("toBeUnlocked : " + toBeUnlocked);
        //unlock board accordingly
        if(toBeUnlocked<0){
            lockAllBoard(false);
        }else{
            getAttentionOfBB(toBeUnlocked,true);
        }
    }
}

function processRegular() {

    //Did anyone win?
    if(winner){
        //Declare
        console.log("Game won by : " + winner); //TODO
        getAllPlayers();
        declareWinner();
    }else {
        for(var i=0; i<9; i++){
            if(cursors[0].cursor[i] == 0)
                getAttentionOfB(i,true);
        }
    }
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
        if(gameType == "regular"){
            console.log('Unlock R');
            getAttentionOfB(i,!lock);
        }
        else {
            console.log('Unlock U');
            getAttentionOfBB(i, !lock);
        }

    }
}

function declareWinner() {
    var p1 = '#playerBoard1';
    var p2 = '#playerBoard2';
    $(p1).removeClass('bs-callout-primary');
    $(p2).removeClass('bs-callout-primary');
    switch(winner){
        case 1: $(p1).addClass('bs-callout-success');
            $(p2).addClass('bs-callout-danger');break;
        case 2: $(p1).addClass('bs-callout-danger');
            $(p2).addClass('bs-callout-success');break;
        case 3: $(p1).addClass('bs-callout-warning');
            $(p2).addClass('bs-callout-warning');break;
    }
}


//***********Players***********************//

var sel1 = document.getElementById('select1');
var sel2 = document.getElementById('select2');

sel1.addEventListener('change',function () {
    updatePlayerBySelect('#select1',1,'#playerBoard1');

});
sel2.addEventListener('change',function () {
    updatePlayerBySelect('#select2',2,'#playerBoard2');
});

function getAllPlayers(){
    var outJson = {};
    outJson.identifier="G";

    var xhttp2 = new XMLHttpRequest();
    xhttp2.open("POST",cgiPath,true);
    xhttp2.send(JSON.stringify(outJson));


    xhttp2.onreadystatechange = function () {

        if(this.readyState == 4 && this.status == 200) {
            var inJson = JSON.parse(this.responseText);

            console.log(inJson);
            allPlayers = inJson.players;
            UpdatePlayersSelectors();
            updateCurrentPlayers();
            updatePlayerBoard('#playerBoard1',1);
            updatePlayerBoard('#playerBoard2',2);
        }
    };


}

$('#newPlayer').click(function () {
    $('#newPlayer').addClass('hide');
    $('#createPlayerPanel').addClass('show')
});

$('#createDone').click(function () {
    var name = $('#pName').val();
    var marker = $('#pMarker').val();
    if(name != "" && marker != ""){
        createPlayer(name, marker);
    }else{
        alert('Name or marker can\'t be empty fields');
    }
});

function createPlayer(name, marker) {
    var request = {
        "identifier" : "",
        "name" : "",
        "marker" : ""
    };
    request.identifier="C";
    request.name = name;
    request.marker = marker;

    var xhttp = new XMLHttpRequest();
    xhttp.open("POST",cgiPath,true);
    xhttp.send(JSON.stringify(request));
    console.log(JSON.stringify(request));

    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            var inJson = JSON.parse(this.responseText);

            console.log(inJson);
            allPlayers = inJson.players;
            UpdatePlayersSelectors();
            $('#createPlayerPanel').removeClass('show');
            $('#createPlayerPanel').addClass('hide');
            $('#newPlayer').addClass('show');
        }
    }
}

function UpdatePlayersSelectors() {

    $('#select1').find('option')
        .remove()
        .end()
        .append('<option>--Select--</option>');
    $('#select2').find('option')
        .remove()
        .end()
        .append('<option>--Select--</option>');

    allPlayers.forEach(function (player) {
        console.log(player);
        var listItem = document.createElement("option");var listItem2 = document.createElement("option");
        var item = document.createTextNode(player.name + " (" + player.marker + ")");var item2 = document.createTextNode(player.name + " (" + player.marker + ")");
        listItem.appendChild(item);listItem2.appendChild(item2);
        sel1.appendChild(listItem);
        sel2.appendChild(listItem2);
    })

}

//select players
function updatePlayerBySelect(selector, whichSelector, boardId){
    selectorObj = document.getElementById(selector.substr(1));
    if(selectorObj.selectedIndex == 0) return;
    if(whichSelector <1 || whichSelector >2) return;

    //Update local variables
    player[whichSelector] = allPlayers[selectorObj.selectedIndex - 1];


    //hide select
    $(selector).parent().removeClass('show');
    $(selector).parent().addClass('hide');

    //update & show playerBoard
    updatePlayerBoard(boardId, whichSelector);
    $(boardId).removeClass('hide');
    $(boardId).addClass('show');

    //change player status to set
    arePlayersSet[whichSelector] = true;

    if( arePlayersSet[1] && arePlayersSet[2]) {
        startGame();
    }

}

function updatePlayerBoard(boardId, whichBoard) {
    $(boardId).find('name').text(player[whichBoard].name + ' ('+player[whichBoard].marker + ')');
    $(boardId).find('win').text(player[whichBoard].stats[gameType].win);
    $(boardId).find('loss').text(player[whichBoard].stats[gameType].loss);
    $(boardId).find('tie').text(player[whichBoard].stats[gameType].tie);

}

function updateCurrentPlayers() {
    if(!isGameRunning) return;
    for(var i=0; i<allPlayers.length; i++){

        if(allPlayers[i].name == player[1].name) {
            console.log(allPlayers[i], player[1]);
            player[1] = allPlayers[i];
            console.log(player);
            console.log(allPlayers[i] == player[1]);
        }
        if(allPlayers[i].name == player[2].name){
            console.log("p.name:"+allPlayers[i].name+', p1.name:'+player[2].name);
            player[2] = allPlayers[i];
        }
    }


}