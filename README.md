
wiringPin is a small piece of software. It's part of a project to implement a
stratum 0 source for a stratum 1 server as NTP service. Hardware platform is a Banana PI M1.
The idea is to use a 10 MHz rubidium frequency standard as time source.
An additional hardware is dividing the 10 MHz signal by 10 to the power of 7
into a 1PPS ( one puls per second ) signal which is needed for "ntpd"

This software controls the hardware in a limited way. It is possible:
* to insert additional pulses - GPIO3
* to strip off (delay) some pulses of the 10 MHz source - GPIO2

A delay with less than 100 usec is not possible

Example 1:  
Add about 1000 pulses to PIN 27 so that the time source is 1 ms ahead.  
  wiringPin -i 27 1000

Example 2:  
Delay the time source for about 1000 us on PIN 22  
  wiringPin -d 22 1000

Dependencies:
It is neccessary to have WiringBP installed.
WiringBP can be found https://github.com/LeMaker/WiringBP

A detailed description of the PC board can be found here: https://github.com/hans-mayer/teiler10e7

![schaltplan](/schaltplan10p7.png)
