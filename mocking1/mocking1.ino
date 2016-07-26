//mocking program only- copy to new, final arduino program once
//parts arrive
const int pot1 = A3;
const int pot2 = A5;
const int buzzer = 12;
int button = 11;
int pot1Val = 0; // value of Pot 1
int pot2Val = 0; // value of Pot 2
int ledPin = 5;
int button_state = 0;
int buttonValue = 0; // bool value of button press
void setup() {
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  pinMode(button, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(115200);
}
void loop() {
pot1Val = analogRead(pot1);
pot2Val = analogRead(pot2);
buttonValue = digitalRead(button);
if (buttonValue == LOW) {
  digitalWrite(ledPin, HIGH);
  tone(12, 1000);
}
else {
  digitalWrite(ledPin, LOW);
  noTone(12);
}
Serial.print("Pot1 Value:");
Serial.println(pot1Val);
Serial.print("Pot2 Value:");
Serial.println(pot2Val);
Serial.print("Button State:");
Serial.println(buttonValue);
delay(500);
}
