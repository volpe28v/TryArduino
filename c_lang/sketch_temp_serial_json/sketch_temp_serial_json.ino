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
  
  sendSensorValue();
  
  nextTempTime = millis() + tempInterval;
  nextLcdTime = millis() + lcdInterval;
}


void loop() {  
  // 温度を取得し計算する
  int nowStatus = digitalRead(BUTTON);
  if (nowStatus == HIGH && preStatus == LOW){
    sendSensorValue();
  }
  preStatus = nowStatus;
  
  if (nextTempTime < millis()){
    nextTempTime += tempInterval;
    sendSensorValue();
  }
  
  if (Serial.available() > 0){
    delay(100); //データ受信しきるまで待つ
    char command = Serial.read();
    if (command == 't'){
      sendSensorValue();    
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
float temp_val = 0;
int light = 0;
void sendSensorValue(){
  temp_val = analogRead(1);
  temp = ((5*temp_val) / 1024) * 100;
  
  light = analogRead(3);  
  
  sendSerial(temp, light);  
  showTempToLCD(temp);
  showLightToLCD(light);
}

char trans[50];
void sendSerial(long int temp, long int light){
    // シリアルからのデータ送信
  memset(trans, 0, 50);
  char *json = &trans[0];

  // 送信用のJSONデータの作成
  sprintf(json, "{\"msg\": \"Temp %ld. Light %ld\" }",temp, light);
  Serial.println(json);
}

char lcdTempBuffer[20];
void showTempToLCD(long int temp){
  TFTscreen.setTextSize(5);
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(lcdTempBuffer, 20, 30);

  sprintf(lcdTempBuffer, "%ldC",temp);

  // set the font color
  TFTscreen.stroke(0,255,0);
  // print the sensor value
  TFTscreen.text(lcdTempBuffer, 20, 30);
}

char lcdLightBuffer[20];
void showLightToLCD(long int light){
  TFTscreen.setTextSize(2);
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(lcdLightBuffer, 20, 80);

  sprintf(lcdLightBuffer, "Light: %ld",light);

  // set the font color
  TFTscreen.stroke(255,0,0);
  // print the sensor value
  TFTscreen.text(lcdLightBuffer, 20, 80);
}

char lcdMsgBuffer[LCDBUFF] = "\0";
void showMsgLCD(char * msg){
  TFTscreen.setTextSize(1);
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(lcdMsgBuffer, 20, 110);

  strcpy(lcdMsgBuffer, msg);

  // set the font color
  TFTscreen.stroke(0,0,255);
  // print the sensor value
  TFTscreen.text(lcdMsgBuffer, 20, 110);
}

