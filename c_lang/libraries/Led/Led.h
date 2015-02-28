#ifndef LED_H
#define LED_H

class Led
{
public:
  enum FadeMode {
    FadeIn,
    FadeOut 
  };

  Led(int pin);
  void on();
  void off();
  void initFade(FadeMode mode);
  void fade();

private:
  int pin;
  int fadeIndex;
  FadeMode fadeMode;
};

#endif
