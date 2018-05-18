# Thwaites Controls
Simple control classes for buttons, joysticks, and potentiometers.

README file  

## License
Arduino Potentiometer/Joystick Library Copyright (C) 2018 Tyson LT GNU GPL v3.0

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License v3.0 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/gpl.html>

## Introduction
This library is intended to make it easier to use potentiometers and joysticks. One of the problems I ran into as a new Arduino user was the 'jitter' inherent in potentiometers. I was writing a MIDI program that sent Control Change messages whenever the potentiometer value changed, so this jitter causes a few random messages to be sent every few seconds. This jitter was usually about +/- 1, but I was not satisfied just adding `if (changed > 1)` in my code.

After a hunt on the wonderful Arduino forums, I came across three strategies for reducing jitter:

### 1. Multiple reads
Some suggested just reading the pin twice. Interesting idea, but it didn't work for me. I was using an old potentiometer that I salvaged from a *very* poor quality guitar effects unit, so maybe jitter was worse than usual. 

### 2. Delay
Putting a small delay before and/or after reading the pin is not a bad idea. Apparenty there's a capacitor in there somewhere that needs time to charge/discharge, which seems reasonable. Adding a 20ms delay certainly helped... but I lost the responsive feel of my MIDI knobs.

### 3. Smoothing algorithms
Now when I found this idea, I got excited. The first algorithm I came across was an Exponential Moving Average (EMA) algorithm from  https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/. This worked really well! However I also wanted to test the second algorithm I found, which was contributed at https://electronics.stackexchange.com/questions/64677/how-to-smooth-potentiometer-values. I was stunned by the simplicity and effectiveness of this idea, so I ended up implementing this one. (The EMA approach is still in the code, commented out.)

`value += (raw - value) / smoothingFactor; //as simple as it is effective.`


