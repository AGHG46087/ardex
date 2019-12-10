# Test Example 11
## Demonstration of a Infra Red sensor.


Infrared sensors is a common control in everday life.  Remote controls, TVs, DVRs, stereos, etc.
They are simple and easy to use.  Essentially they are small microchips with a photcell that tuned into Infrared light.

Inside the remote control is also a Infrared LED.  which can emit IR pulses to provide a signal that will perform an action that is defined by the software.

As afrementioned, Infrared sensors are tuned for Infrared lught,  that are not good at all for detecting visible light.  And likewise Photocells that detect yellow/green light are not good at detecting infrared light.  

IR sensors look for Pulse wave modulatated signal at 38 kHZ and a steady shining IR LED will not be detected.  They either detect there was a signal and output 0V or they do not and output 5V.  This is in contrast to how standard photcells work where the resistance changes depending on how much light they are exposed to.

In this project I purchased a IR sensor module and remote control.  However later tried other remote controls around the house and found that these too also work in terms of sending and detecting a signal.  

**Maybe using a TV remote to control a robot.** 😎

![Wiring Diagram](https://github.com/AGHG46087/ardex/blob/master/T11_IR_Receiver/T11_Wiring.jpg "Wiring Diagram")





