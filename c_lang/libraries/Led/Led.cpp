#include "Arduino.h"
#include "Led.h"

Led::Led(int pin)
{
  this->pin = pin;
  this->fadeIndex = 0;
  this->fadeMode = FadeIn;
  pinMode(this->pin, OUTPUT);
}

void Led::on(void)
{
  digitalWrite(this->pin, HIGH);
}

void Led::off(void)
{
  digitalWrite(this->pin, LOW);
}

void Led::initFade(FadeMode mode)
{
  this->fadeMode = mode;
  if (mode == FadeIn){
    this->fadeIndex = 0;
  }else{
    this->fadeIndex = 255;
  }
}

void Led::fade(void)
{
  if (this->fadeMode == FadeIn){
    this->fadeIndex++;
    if (this->fadeIndex >= 256){
      this->fadeMode = FadeOut;
      this->fadeIndex = 255;
    }
  }else{
    this->fadeIndex--;
    if (this->fadeIndex < 0){
      this->fadeMode = FadeIn;
      this->fadeIndex = 0;
    }
  }

  analogWrite(this->pin, this->fadeIndex);
}
