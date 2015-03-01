#include <Led.h>

int val = 0;
Led* led1 = new Led(9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9800);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(0);
//  Serial.println(val/4);
  
  if (val/4 > 250){
    led1->fadeIn();
  }else{
    led1->fadeOut();
  }
  delay(100);
}
