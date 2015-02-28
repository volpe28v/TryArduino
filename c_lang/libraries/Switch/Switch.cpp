#include "Switch.h"
#include "arduino.h"

Switch::Switch(int pin){
  this->pin = pin;
  this->isPreUp = true;
  pinMode(this->pin, INPUT);
}

bool Switch::isUp(){
  return digitalRead(this->pin) == LOW ? true : false;
}

bool Switch::isDown(){
  return !this->isUp();
}

bool Switch::isJustUp(){
  bool ret = false;

  bool isUp = this->isUp();
  if (isUp == true && this->isPreUp == false){
    ret = true;
  }

  this->isPreUp = isUp;
  return ret;
}

bool Switch::isJustDown(){
  bool ret = false;

  bool isDown = this->isDown();
  if (isDown == true && this->isPreUp == true){
    ret = true;
  }

  this->isPreUp = !isDown;
  return ret;
}
