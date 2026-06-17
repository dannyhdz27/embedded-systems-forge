struct Button{
  const uint8_t PIN; 
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 ={4,0,false};

// void IRAM_ATTR isr1(){
//   button1.numberKeyPresses++;
//   button1.pressed = true;
// }
volatile unsigned long button_time = 0;
volatile unsigned long last_button_time = 0;

void IRAM_ATTR isr1(){
  button_time = millis();
  if(button_time - last_button_time >250){ 
    
  button1.numberKeyPresses++;
  button1.pressed = true;
last_button_time = button_time;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN,isr1,RISING);

}

void loop() {
 if(button1.pressed){
  Serial.printf("button has been pressed %u times\n", button1.numberKeyPresses);
  button1.pressed = false;
 }
 // delay(200);
}
