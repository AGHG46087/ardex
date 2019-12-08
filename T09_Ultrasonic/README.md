# Test Example 09
## Meauring distance with a Ultrasonic sensor.


Ultrasonic sensors are a really cool thing for projects that may need/require to measure distance.  A roaming robot will of course need to utilize somthing such as this to avoid obstancles as an example:

This is a cool thing.  and probably can have quite a few applications.
This exercise required a HC-SR04 sensor module.

So to provide some insight in how this works.
1. We are going to send a IO trigger
2. The module will send out 40 kHz and detects a pulse and returns it signal
3. if the signal is back through the high level.  then we are going to use the time for sending

Here is the formula.

distance = (high level time × velocity of sound (340m/s) /2

