#include <Switch.h>
#include <Led.h>

Led* led1 = new Led(9);
Led* led2 = new Led(10);
Switch* switch1 = new Switch(7);

void setup() {
//  led1->on();
//  led2->on();
  led1->initFade(Led::FadeOut);  
  led2->initFade(Led::FadeIn);  
}

bool isWork = false;
void loop() {
  // スイッチを押している間だけフェードする
  if (switch1->isDown()){
    led1->fade();
  }

  // スイッチを押すたびにフェードのON/OFFする  
  if (switch1->isJustDown()){
    isWork = !isWork;
  }
  
  if (isWork){
    led2->fade();
  }
  delay(10);
}
