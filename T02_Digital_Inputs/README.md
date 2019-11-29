# Test Example 02
## Digital Inputs

This example makes use of a momentary button switches.  Pressing one button will turn on a LED and the the depressing of the second will of course turn off the LED.

A switch as is pressed or flipped will connect to contacts. and electricity can flow.  
As the first button is pressed,  we will write to the digitalwrite pin to have the LED lite up.
The second button,  when it low will shut off the LED.
These types of switches may seem backward.  theyare normally HIGH and have a differential in voltage.  When pressed they are low to ground and therefore no differential. and we are going to use these low values as the triggers.


![Wiring Diagram](https://github.com/AGHG46087/ardex/blob/master/T02_Digital_Inputs/T02_Wiring.jpg "Wiring Diagram")

