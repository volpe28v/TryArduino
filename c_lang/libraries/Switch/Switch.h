#ifndef SWITCH_H
#define SWITCH_H

class Switch {
public:
  Switch(int pin);
  bool isUp();
  bool isDown();

  bool isJustUp();
  bool isJustDown();
private:
  int pin;
  bool isPreUp;
};
#endif
