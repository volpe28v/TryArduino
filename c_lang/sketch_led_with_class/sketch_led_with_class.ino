#include <Led.h>

Led * led1 = new Led(9);
Led * led2 = new Led(10);

void setup() {
  // put your setup code here, to run once:
//  led1->on();
//  led2->on();
  led1->initFade(Led::FadeOut);  
  led2->initFade(Led::FadeIn);  
}

void loop() {
  // put your main code here, to run repeatedly:
  led1->fade();
  led2->fade();
  delay(10);
}
