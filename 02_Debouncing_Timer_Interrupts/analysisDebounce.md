{\rtf1\ansi\ansicpg1252\cocoartf2709
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;\f1\froman\fcharset0 Times-Bold;}
{\colortbl;\red255\green255\blue255;\red0\green0\blue0;}
{\*\expandedcolortbl;;\cssrgb\c0\c0\c0;}
\margl1440\margr1440\vieww16000\viewh11380\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 # Debouncing \
\
## Concepts\
- Button bounce\
- Timer Interrupts\
- Sampling\
\
\
## Versions\
- Delay implementation\
- Millis() implementation\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 - Timer ISR implementation\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \
## Observations\
\
Multiple button presses are recorded for a single physical button press. Serial monitor shows multiple counter increments occurring at nearly identical time stamps - ISR triggered multiple times within a very short time interval. \
\
Millis() debounce method is effective at eliminating bounce - serial monitor shows stable and accurate output. \
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 In Timer ISR Implementation, the buttons are sampled at 1 second intervals. This means that the button needs to remain pressed long enough for it to be read when the timer interrupt occurs. If a button is pressed too quick it may be missed(button press occurs occurs between a sampling period). Reducing timer interval Increases sampling rate, which allows for shorter button presses to be detected. System feels much more responsive, though it is important to note that a faster sampling rate will increase CPU utilization - more CPU time spend servicing interrupts. \
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \kerning1\expnd0\expndtw0 \outl0\strokewidth0 \
\
## Notes\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 - Mechanical pushbuttons do not switch cleanly from open -> closed\
- When pressed, metal contacts vibrate, hit repeatedly, settle after a short duration - this is bounce. \
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 - Bouncing is much faster than humans can perceive. Usually occurs in the millisecond range. \
- Hardware debouncing is also possible (via RC filter)\
- A classic embedded systems problem -> Responsiveness vs CPU Utilization \
\
## Key Insights\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 Delay does not eliminate bounce, it only reduces how often the event is seen/printed. \
\
Millis() debounce method ignores any rising edges that occurred within 250ms of the previous valid press. However, this also seems to reduce responsiveness. Rapid button presses may not be recorded. 250ms is very safe, but a more practical value is often around 20-50ms. \
\
Event-driven system vs time-driven system: \
\
Time-driven systems do not wait on external triggers or flags. It uses a timer interrupt to automatically run a function when the timer reaches a target count. This is the core concept of sampling. \
\
Compare to previous interrupt 
\f1\b \expnd0\expndtw0\kerning0
attachInterrupt(button1.PIN, isr1, RISING); 
\f0\b0 where ISR runs only when an edge occurs - there is no polling, no periodic checking. This is an event-driven system. \kerning1\expnd0\expndtw0 \
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \
}