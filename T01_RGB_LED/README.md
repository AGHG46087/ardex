# Test Example 01
## RGB_LED

RGB LEDs look similar to ordinary LEDs.  However, the LED housing there are actuallly 3 LEDs, one of each, Red, Green, Blue. And it can be done in such a way that each LED can control the brightness independently and therefore create nearly every color you may weant. 
On the RGB many have a common cathode. They are from flat side to opposite.
Red, Cathode, Green, Blue

The reason that we can mix nearly any color by varying the quantities of red, green and blue light is that the human eye has three types of light receptor in it (red, green and blue). Your eye and brain process the amounts of red, green and blue and convert it into a color of the spectrum.

If we set the brightness of all three LEDs to be the same, then the overall color of the light will be white. If we consider color and their compliments.
  Red  |  Green |  Blue  | Result
:----: | :----: | :----: | :----:
  on   |   off  |  off   |  Red
  off  |   on   |  off   | Green
  off  |   off  |  on    | Blue
  off  |   on   |  on    | Cyan
  on   |   off  |  on    | Magenta
  on   |   on   |  off   | Yellow

If we turn off the blue LED, so that just the red and green LEDs are the same brightness, then the light will appear yellow.

Making use of the AnalogWrite function we can control the power to each LED,  which should give us what we want.

Making use of the Pulse Width Modulation to control the power - So `analogWrite(0)` will not produce any pulse at all and `analogWrite(255)` will produce a pulse that lasts all the way until the next pulse.

The rate of speed in the change is actually faster than the eye can detect. approximatly 1/500 fo a second.  since we cann not detect the on off,  it just appears to us as the brightness is changing.  

![Wiring Diagram](https://github.com/AGHG46087/ardex/blob/master/T01_RGB_LED/T01_Wiring.jpg "Wiring Diagram")

