const int LED = 8;
const int BUTTON = 7;

int val = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);  
}

void loop() {
  val = digitalRead(BUTTON);
  
  if (val == HIGH){
    digitalWrite(LED, HIGH);
    digitalWrite(LED, LOW);
  }
}
