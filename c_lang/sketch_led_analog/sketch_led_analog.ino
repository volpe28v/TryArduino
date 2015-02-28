const int LED = 9; // PWM が対応したとこじゃないとダメ
const int LED2 = 10;
int i = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  for (i = 0; i < 255; i++){
    analogWrite(LED,i);
    analogWrite(LED2,i);
    delay(10);    
  }
  for (i = 255; i > 0; i--){
    analogWrite(LED,i);
    analogWrite(LED2,i);
    delay(10);
  }
}
