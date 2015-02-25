var five = require("johnny-five"),
    // or "./lib/johnny-five" when running from the source
    board = new five.Board();

board.on("ready", function() {

  var led = new five.Led(8);
  var button = new five.Button(7);

  var isTuneOn = false;

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
});
