const int LED = 9; // PWM が対応したとこじゃないとダメ
int i = 0;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  for (i = 0; i < 255; i++){
    analogWrite(LED,i);
    delay(10);
    
  }
  for (i = 255; i > 0; i--){
    analogWrite(LED,i);
    delay(10);
  }
}
