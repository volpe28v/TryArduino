#include <Led.h>
#include <TFT.h>
#include <SPI.h>

#define cs   10
#define dc   9
#define rst  8 

TFT TFTscreen = TFT(cs, dc, rst);
int val0 = 0;

Led* led2 = new Led(9);
const int BUTTON = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  Serial.begin(9800);

  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
   
  TFTscreen.stroke(255,255,255);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Temp :\n ",0,0);
 
  TFTscreen.setTextSize(6);
  
  sendTemp();
}

int preStatus = LOW;
long int nowTime = 0;
long int limitTime = 60000 * 60 * 1;
int delayInterval = 100;
void loop() {  
  // 温度を取得し計算する
  int nowStatus = digitalRead(BUTTON);
  if (nowStatus == HIGH && preStatus == LOW){
    sendTemp();
  }
  preStatus = nowStatus;
  
  if (nowTime > limitTime){
    nowTime = 0;
    sendTemp();
  }else{
    nowTime += delayInterval;
  }
  delay(delayInterval);
//  sendSerial(limitTime);
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
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(lcdBuffer, 20, 30);

  sprintf(lcdBuffer, "%ldC",val);

  // set the font color
  TFTscreen.stroke(0,255,0);
  // print the sensor value
  TFTscreen.text(lcdBuffer, 20, 30);
}
