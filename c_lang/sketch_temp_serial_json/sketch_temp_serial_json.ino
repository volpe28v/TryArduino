#include <Led.h>
#include <TFT.h>
#include <SPI.h>

#define cs   10
#define dc   9
#define rst  8 

#define LCDBUFF 256

TFT TFTscreen = TFT(cs, dc, rst);
int val0 = 0;

Led* led = new Led(4);
const int BUTTON = 7;

int preStatus = LOW;

long int nextTempTime;
long int tempInterval = 60000 * 60 * 2;

long int nextLcdTime;
long int lcdInterval = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  Serial.begin(9800);

  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
   
  TFTscreen.stroke(255,255,255);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Temp:\n ",10,4);
 
  TFTscreen.setTextSize(5);
  
  sendTemp();
  
  nextTempTime = millis() + tempInterval;
  nextLcdTime = millis() + lcdInterval;
}


void loop() {  
  // 温度を取得し計算する
  int nowStatus = digitalRead(BUTTON);
  if (nowStatus == HIGH && preStatus == LOW){
    sendTemp();
  }
  preStatus = nowStatus;
  
  if (nextTempTime < millis()){
    nextTempTime += tempInterval;
    sendTemp();
  }
  
  if (Serial.available() > 0){
    delay(100); //データ受信しきるまで待つ
    char command = Serial.read();
    if (command == 't'){
      sendTemp();    
      Serial.flush();
    }else{
      char msgBuff[LCDBUFF]; 
      memset(msgBuff,0,LCDBUFF);
      int i = 0;
      char readByte;
      while(( readByte = Serial.read()) > 0){
        msgBuff[i++] = readByte;
        if (i > LCDBUFF) { break; }
      }
      showMsgLCD(msgBuff);
    }
    led->on();
    nextLcdTime = millis() + lcdInterval;
  }else{
    if (nextLcdTime < millis()){     
      led->off();
      nextLcdTime = 0;
    }
  }
}

float temp = 0;
float val1 = 0;
void sendTemp(){
  val1 = analogRead(1);
  temp = ((5*val1) / 1024) * 100;
  
  sendSerial(temp);  
  showLCD(temp);
}

char trans[50];
void sendSerial(long int val){
    // シリアルからのデータ送信
  memset(trans, 0, 50);
  char *json = &trans[0];

  // 送信用のJSONデータの作成
  sprintf(json, "{\"msg\": \"Temp %ld.\" }",val);
  Serial.println(json);
}

char lcdBuffer[20];
void showLCD(long int val){
  TFTscreen.setTextSize(5);
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(lcdBuffer, 20, 30);

  sprintf(lcdBuffer, "%ldC",val);

  // set the font color
  TFTscreen.stroke(0,255,0);
  // print the sensor value
  TFTscreen.text(lcdBuffer, 20, 30);
}

char lcdMsgBuffer[LCDBUFF] = "\0";
void showMsgLCD(char * msg){
  TFTscreen.setTextSize(1);
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(lcdMsgBuffer, 20, 80);

  strcpy(lcdMsgBuffer, msg);

  // set the font color
  TFTscreen.stroke(0,0,255);
  // print the sensor value
  TFTscreen.text(lcdMsgBuffer, 20, 80);
}

