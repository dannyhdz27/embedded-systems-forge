
 
// const int buttonPin1 = D4;  
// const int buttonPin2 = D5;
const int ledPinRed = D8;     
const int ledPinGreen = D9;
const int ledPinYellow = D10;
 

int buttonState = 0;  //  pushbutton status 
 
void setup() { 
  // initialize the LED pin as an output: 
  pinMode(ledPinRed, OUTPUT); 
   pinMode(ledPinGreen, OUTPUT); 
    pinMode(ledPinYellow, OUTPUT); 

  Serial.begin(115200); 
} 
 
void loop() { 
  // CPU continuously asking: has any serial data arrived yet? 
  if (Serial.available() > 0){ 
  buttonState = Serial.read(); 
 
  // check if the pushbutton is pressed for Green. 
  if ((buttonState == 'G') || (buttonState == 'g')){ 
    // turn LED on: 
    digitalWrite(ledPinGreen, 1); 
  }  
  if ((buttonState == 'R') || (buttonState == 'r')){ 
    // turn LED on: 
    digitalWrite(ledPinRed, 1); 
  }  
  if ((buttonState == 'Y') || (buttonState == 'y')){ 
    // turn LED on: 
    digitalWrite(ledPinYellow, 1); 
  }  
  if (buttonState == 'O') { 
    // turn LED off: 
    digitalWrite(ledPinGreen, 0); 
    digitalWrite(ledPinRed, 0); 
    digitalWrite(ledPinYellow, 0); 
  } 
  } 
} 