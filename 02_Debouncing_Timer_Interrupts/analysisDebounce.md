# Debouncing 

## Concepts
- Button bounce
- Timer Interrupts
- Sampling


## Versions
- Delay implementation
- Millis() implementation
- Timer ISR implementation

## Observations

Multiple button presses are recorded for a single physical button press. Serial monitor shows multiple counter increments occurring at nearly identical time stamps - ISR triggered multiple times within a very short time interval. 

Millis() debounce method is effective at eliminating bounce - serial monitor shows stable and accurate output. 

In Timer ISR Implementation, the buttons are sampled at 1 second intervals. This means that the button needs to remain pressed long enough for it to be read when the timer interrupt occurs. If a button is pressed too quick it may be missed(button press occurs occurs between a sampling period). Reducing timer interval Increases sampling rate, which allows for shorter button presses to be detected. System feels much more responsive, though it is important to note that a faster sampling rate will increase CPU utilization - more CPU time spend servicing interrupts. 


## Notes
- Mechanical pushbuttons do not switch cleanly from open -> closed
- When pressed, metal contacts vibrate, hit repeatedly, settle after a short duration - this is bounce. 
- Bouncing is much faster than humans can perceive. Usually occurs in the millisecond range. 
- Hardware debouncing is also possible (via RC filter)
- A classic embedded systems problem -> Responsiveness vs CPU Utilization 

## Key Insights
Delay does not eliminate bounce, it only reduces how often the event is seen/printed. 

Millis() debounce method ignores any rising edges that occurred within 250ms of the previous valid press. However, this also seems to reduce responsiveness. Rapid button presses may not be recorded. 250ms is very safe, but a more practical value is often around 20-50ms. 

Event-driven system vs time-driven system: 

Time-driven systems do not wait on external triggers or flags. It uses a timer interrupt to automatically run a function when the timer reaches a target count. This is the core concept of sampling. 

Compare to previous interrupt attachInterrupt(button1.PIN, isr1, RISING); where ISR runs only when an edge occurs - there is no polling, no periodic checking. This is an event-driven system. 

