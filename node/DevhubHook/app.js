
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
app.set('memo_no', process.env.NO);
app.set('memo_line', process.env.LINE);
app.set('server_host', process.env.SERVER_HOST);
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

var socket = io.connect(url);
socket.on('connect', function(){
  console.log("connect: " + app.get('devhub'));
  socket.emit('name', {name: 'Arduino'});
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
    socket.emit('message',{name:'Arduino',msg: jsonData.msg});
    console.log('serial: ' + jsonData.msg);
  } catch(e) {

    console.log(e);
    // データ受信がおかしい場合無視する
    return;
  }
});


