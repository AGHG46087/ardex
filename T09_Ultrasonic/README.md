# Test Example 09
## Meauring distance with a Ultrasonic sensor.


Ultrasonic sensors are a really cool thing for projects that may need/require to measure distance.  A roaming robot will of course need to utilize somthing such as this to avoid obstancles as an example:

This is a cool thing.  and probably can have quite a few applications.
This exercise required a HC-SR04 sensor module.

So to provide some insight in how this works.
1. We are going to send a IO trigger
2. The module will send out 40 kHz and detects a pulse and returns it signal
3. if the signal is back through the high level.  then we are going to use the time for sending

The timing trigger only needs a 10µs pulse to being the ranging.  the moduile it self will send out 8 cycle bursts in the 40kHz range for the echos.  The range is then calcuculated using the time interval between the trigger and echo signal retrieved.  

Here is the formula.

distance = (high level time × velocity of sound (340m/s) /2

* Formula: `Range = high level time * velocity (340M/S)/2`
* Metric (centimeters):  `µs / 58`
* US (inches): `µs / 148`


![Wiring Diagram](https://github.com/AGHG46087/ardex/blob/master/T09_Ultrasonic/T09_Wiring.jpg "Wiring Diagram")
