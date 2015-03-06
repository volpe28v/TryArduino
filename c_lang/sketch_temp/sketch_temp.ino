#include <Led.h>

int val0 = 0;
float val1 = 0;
float temp = 0;

Led* led2 = new Led(9);
const int BUTTON = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {  
  // 温度を取得し計算する
  val1 = analogRead(1);  
  temp = ((5*val1) / 1024) * 100;
  
  Serial.println(temp);
  
  // しきい値以上ならLCDをON
  if (temp > 22){
    led2->on();
  }else{
    led2->off();
  }
  delay(1000);
}
