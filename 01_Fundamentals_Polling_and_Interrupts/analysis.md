# Fundamentals

## Concepts
- GPIO input/output
- Polling
- Interrupts

## Versions
- Polling implementation
- Interrupt implementation

## Observations
Interrupts reduce constant CPU polling and move toward event-driven design. Button bounce is still an issue that appears in both implementations. 

## Polling Notes
- CPU constantly reads pin input. digitalRead(button)
- Simple but inefficient
- Loop keeps running continuously

## Interrupt Notes
- Hardware triggers ISR automatically
- Need debounce handling
- ISR should stay short. blocking/latency becomes an issue in larger systems. 

## Key Insights
Polling is software-driven.
Interrupts are hardware/event-driven. loop() is still continuously running, but instead of reading GPIO hardware, loop() is checking for a software flag. 

Even interrupt-based embedded systems will have while(1) or loop() running forever because embedded systems are continuous real-time systems. 

Serial.available() => CPU is continuously asking, has any serial data arrived yet? Still polling-based event detection. 