

// constants used here to set pin numbers:
const int buttonPin1 = D3; 
const int buttonPin2 = D4; 
const int ledRED = D8;  
const int ledGREEN = D9;
const int ledYELLOW = D10;  

int buttonState1 = 0; 
int buttonState2 = 0; // initial button state

void setup() {
  // initialize LED pins as an output:
  pinMode(ledRED, OUTPUT);
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledYELLOW, OUTPUT);
  // initialize pushbutton pins as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

    Serial.begin(115200); // serial communication for debugging
}

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
   Serial.print("buttonState1: ");
    Serial.print(buttonState1);

     Serial.print(" buttonState2: ");
    Serial.println(buttonState2);

// turn LEDs off each loop cycle
 digitalWrite(ledRED, LOW); 
digitalWrite(ledGREEN, LOW);
digitalWrite(ledYELLOW, LOW);

if (buttonState1 == HIGH && buttonState2 == HIGH) {
  digitalWrite(ledYELLOW, HIGH);
}
else if (buttonState1 == HIGH) {
  digitalWrite(ledRED, HIGH);
}
else if (buttonState2 == HIGH) {
  digitalWrite(ledGREEN, HIGH);
}
  delay(100);
}
