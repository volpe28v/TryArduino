
/**
 * Module dependencies.
 */

var express = require('express');
var http = require('http');
var path = require('path');
var moment = require('moment');
var serialport = require('serialport');

var app = express();

// all environments
app.set('port', process.env.PORT || 3000);
app.set('devhub', process.env.DEVHUB);
app.set('room_id', process.env.ROOM_ID || 1);
app.use(express.favicon());
app.use(express.logger('dev'));
app.use(express.json());
app.use(express.urlencoded());
app.use(express.methodOverride());
app.use(express.bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(app.router);

// development only
if ('development' == app.get('env')) {
  app.use(express.errorHandler());
}

var portName = "/dev/cu.usbmodem1411";
var sp = new serialport.SerialPort(portName, {
    baudRate: 115200,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
    parser: serialport.parsers.readline("\n")
});

var io = require('socket.io-client');
var url = app.get('devhub');
var name = 'Arduino';

var socket = io.connect(url);
socket.on('connect', function(){
  console.log("connect: " + app.get('devhub'));
  socket.emit('name', {name: name});
});

socket.on('message', function(data){
  var command = "";
  if (data.msg.match(/arduino/i)){
    command = "t";
  }else{
    command = "m" + data.msg;
  }

  sp.write(command, function(err, bytes) {
    console.log('bytes written: ', bytes);
    console.log(command);
  });
});
socket.on('disconnect', function(){});

sp.on('data', function(input) {
  var buffer = new Buffer(input, 'utf8');
  console.log(buffer);

  var jsonData;
  try {
    jsonData = JSON.parse(buffer);
    socket.emit('message',{name:name, room_id: app.get('room_id'), msg: 'volpeさんの部屋の温度は ' + jsonData.temp + ' 度です。'});
    console.log('serial: ' + jsonData.temp);
  } catch(e) {

    console.log(e);
    // データ受信がおかしい場合無視する
    return;
  }
});


