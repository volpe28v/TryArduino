#include <Led.h>

int val0 = 0;

Led* led2 = new Led(9);
const int BUTTON = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  Serial.begin(9800);
}

int preStatus = LOW;
int nowTime = 0;
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
}

char trans[50];
void sendSerial(long int val){
  
  // シリアルからのデータ送信
  memset(trans, 0, 50);
  char *json = &trans[0];

  // 送信用のJSONデータの作成
  sprintf(json, "{\"msg\":\"Temp %ld.\" }",val);
  Serial.println(json);
}
