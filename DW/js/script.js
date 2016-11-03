// JavaScript Document

$('.outer > .row').children().each(function () {
    if($(this).attr("pos") == 2){
        $(this).text("I'm 2");
    }
});

//Players
var player = {
    1:{ "name": "RV",
        "marker" :'o'

    }, 2:{

    }

};

//Cursors
var cursors = {
    0: {"cursor" : "000000000"},
    1: {"cursor" : "000000000"},
    2: {"cursor" : "000000000"},
    3: {"cursor" : "000000000"},
    4: {"cursor" : "000000000"},
    5: {"cursor" : "000000000"},
    6: {"cursor" : "000000000"},
    7: {"cursor" : "000000000"},
    8: {"cursor" : "000000000"}
};


console.log(cursors[0].cursor);


// outerPos = 0...9;
// innerPos = 0...9
// marker = Player marker
function setMarker(outerPos, innerPos, marker) {
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
var marker = 'o';


$('.outer').each(function () {
    var outerPos = $(this).attr("pos");

    $(this).children().children('.inner').each(function () {
        var div = this;
        var innerPos = $(div).attr("pos");

        var onClickHandler =  function (){
            //$(div).text(marker);
            setMarker(outerPos,innerPos,marker);
            console.log("Board:" + innerPos + ", at: " + outerPos);
            console.log(cursors);
            $(div).off('click',onClickHandler);

            //prepare request and send it

            //send it
        };


        $(this).on('click',onClickHandler);


    });
});

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

    //Get game cursors
    var cursors = {};


    //send it

    //parse it
}