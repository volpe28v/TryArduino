const int LED = 8;
const int BUTTON = 7;

int val = 0;
bool isTuneOn = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);  
}

void loop() {
  // スイッチを押すたびにLEDのON/OFFを切り替える  
  int currentVal = digitalRead(BUTTON);

  if (val != currentVal && currentVal == HIGH){
    if (isTuneOn = !isTuneOn){
      digitalWrite(LED, HIGH);
    }else{
      digitalWrite(LED, LOW);      
    }
  }
  
  val = currentVal;
}
