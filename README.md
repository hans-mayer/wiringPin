
wiringPin is a small piece of software. It's part of a project to implement a 
stratum 0 server for a NTP service. Hardware plattform is a Banana PI M1. 
The idea is to use a 10 MHz rubidium frequnecy standadrd as time source.
An additional hardware is dividing the 10 MHz signal by 10 to the power of 7
into a 1PPS ( one puls per second ) which is needed for "ntpd" 

This software controls the hardware in a limited way. It is possible: 
* to insert additional pulses - GPIO3 
* to strip off some pulses of the 10 MHz source - GPIO2 

Example 1:  
Add about 1000 pulses to PIN 27 so that the time source is 1 ms ahead.  
  wiringPin -i 27 1000

Example 2:  
Delay the time source for about 1000 us on PIN 22  
  wiringPitest -d 22 1000 

Dependencies:
It is neccessary to have WiringBP installed. 
WiringBP can be found https://github.com/LeMaker/WiringBP

![schaltplan](/schaltplan10p7.png) 

