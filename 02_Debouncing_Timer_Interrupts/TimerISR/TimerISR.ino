// Two input switches connected to GPIO 5 and GPIO 6
const int switch1 = 4;
const int switch2 = 5;

// Three LED outputs connected to GPIO 7, 8, and 9
#define LEDRED 7
#define LEDGREEN 8
#define LEDYELLOW 9

// Pointer to hardware timer
hw_timer_t *timer = NULL;


// The ISR function executes automatically every time the hardware timer reaches the alarm value.

void IRAM_ATTR onTimer() {

    // Both switches are closed (HIGH) - Turn RED LED on 
  if (digitalRead(switch1) && digitalRead(switch2)) {
        digitalWrite(LEDRED, HIGH);
    }
    else{digitalWrite(LEDRED, LOW);}

    // switch1 HIGH and switch2 LOW
    // Only switch1 is pressed - Turn YELLOW LED on
  if(digitalRead(switch1) && !(digitalRead(switch2))) {
        digitalWrite(LEDYELLOW, HIGH);
    }
    else{digitalWrite(LEDYELLOW, LOW);}

    // switch1 LOW and switch2 HIGH
    // Only switch2 is pressed - Turn GREEN LED on
  if(!(digitalRead(switch1)) && digitalRead(switch2)) {
      
        digitalWrite(LEDGREEN, HIGH);
    }
  
    else{digitalWrite(LEDGREEN, LOW);}


}


void setup() {

    Serial.begin(115200);

    // Configure switch pins as inputs

    pinMode(switch1, INPUT);
    pinMode(switch2, INPUT);

    // Configure LED pins as outputs
    pinMode(LEDRED, OUTPUT);
    pinMode(LEDGREEN, OUTPUT);
    pinMode(LEDYELLOW, OUTPUT);

   
    // Creates a timer running at 1 MHz (1 Million ticks per second)
    timer = timerBegin(1000000);

    // Attach the ISR function to the timer
    timerAttachInterrupt(timer, &onTimer);

    // Enable alarm
    timerAlarm(timer, 1000000, true, 80);
}

void loop() {

    delay(20);
}