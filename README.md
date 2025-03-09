A Tesla scanner for ESP32 devices. (with bluetooth) 

Tesla uses the same device naming convention for the bluetooth door lock or whatever for all of their vehicles, 
first letter is "S" and the eighteenth is "C".

This program will constantly scan for devices in the area fitting that convention, and (in this case) flash the 
LED when one is found. Flashing speed/length is dependent on signal intensity, sort of war movie radar style.
It's a fun game when driving, but can become obnoxious in certain areas.

You can of course modify this program to control whatever your little heart desires. 

Written in the Arduino IDE and uses several libraries included with the ESP32 boards.
