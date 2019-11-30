# Test Example 05
## Multiple RGB

With this example we are using a 74hc595 IC shift register.  to drive several LEDS to shift up and down in the lighting sequencing, the sequencing is in many parts slower than other chips,  however it is speed is still 500,000 times a second, which is way faster than than the human eye can detect.  

You can think of the Chip as one that is 8 memory locations represented as either `1` or `0` we turn items on or off 

The clock pin needs to recieve 8 pulses.  on a high a `1` is poushed and of course low a `0`

Anyway,  I am adding the schematic as well to see how this chip is connected and the wiring diagram.

![Wiring Diagram](https://github.com/AGHG46087/ardex/blob/master/T05_Multi_RGB_Driver/T05_Wiring.jpg "Wiring Diagram")

![Schematic Diagram](https://github.com/AGHG46087/ardex/blob/master/T05_Multi_RGB_Driver/T05_Schematic.jpg "Schematic Diagram")

