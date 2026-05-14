

// constants used here to set pin numbers:
const int buttonPin1 = D3; 
const int buttonPin2 = D4; 
const int ledRED = D8;  
const int ledGREEN = D9;
const int ledYELLOW = D10;  

 // no longer need initial button state - global variables
// int buttonState1 = 0; 
//int buttonState2 = 0;

//volatile to precent compiler optimization/caching 
volatile bool buttonChanged = false;

//ISR updates buttonChanged to true when it is called. set flag.
void IRAM_ATTR handleButtonChange() {
  buttonChanged = true;
}

void setup() {

  Serial.begin(115200); // serial communication for debugging
  
  // initialize LED pins as an output:
  pinMode(ledRED, OUTPUT);
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledYELLOW, OUTPUT);
  // initialize pushbutton pins as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

// attach interrupts to hardware 
    attachInterrupt(digitalPinToInterrupt(buttonPin1), handleButtonChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin2), handleButtonChange, CHANGE);
}

/*
Observation: loop() is still continously running, but instead of continuously reading GPIO hardware, 
loop() continously checks software flag. 
*/
void loop() {
  // we no longer need to continuously read pin in loop
 // buttonState1 = digitalRead(buttonPin1);
  //buttonState2 = digitalRead(buttonPin2);
  if (buttonChanged) {
    buttonChanged = false;

//only read pins if buttonChanged
    int button1 = digitalRead(buttonPin1);
    int button2 = digitalRead(buttonPin2);

/*
Observation: bounce - multiple "presses" observed in serial monitor when the button is only
pressed once. This happens sporadically. 
*/
    Serial.print("B1: ");
    Serial.print(button1);
    Serial.print(" B2: ");
    Serial.println(button2);

    digitalWrite(ledRED, LOW);
    digitalWrite(ledGREEN, LOW);
    digitalWrite(ledYELLOW, LOW);

    if (button1 == HIGH && button2 == HIGH) {
      digitalWrite(ledYELLOW, HIGH);
    }
    else if (button1 == HIGH) {
      digitalWrite(ledRED, HIGH);
    }
    else if (button2 == HIGH) {
      digitalWrite(ledGREEN, HIGH);
    }
  }
}
