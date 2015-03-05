var five = require("johnny-five"),
    // or "./lib/johnny-five" when running from the source
    board = new five.Board();

var devhub_url = "http://127.0.0.1:3000";
var socket = require('socket.io-client')(devhub_url,{'force new connection': true, query: 'from=chrome'});

board.on("ready", function() {
  var led = new five.Led(8);
  var button = new five.Button(7);

  var isTuneOn = false;

  // タクトスイッチを押すたびに LED を ON/OFF するよ
  button.on("down", function() {
    isTuneOn = !isTuneOn;
    if (isTuneOn){
      led.on();
    }else{
      led.off();
    }
  });

  button.on("hold", function() {
  });

  button.on("up", function() {
  });

  socket.on('connect', function(){
    console.log("connect: " + devhub_url);
  });

  socket.on('message', function(data){
    console.log(data);
  });
  socket.on('disconnect', function(){});

});
