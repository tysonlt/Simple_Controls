# Simple Controls
Simple control classes to interface with joysticks and potentiometers.

## License
Arduino Potentiometer/Joystick Library Copyright (C) 2018 Tyson LT GNU GPL v3.0

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License v3.0 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/gpl.html>


## Potentiometers
This library is intended to make it easier to use potentiometers and joysticks. It was inspired by JC_Button's approach to debouncing, which I found simpler and more elegant than some other solutions. I tried to apply the same philosophy in this library.

One of the problems I ran into as a new Arduino user was the 'jitter' inherent in potentiometers. I was writing a MIDI program that sent Control Change messages whenever the potentiometer value changed, so this jitter causes a few random messages to be sent every few seconds. This jitter was usually about +/- 1, but I was not satisfied just adding `if (changed > 1)` in my code.

After a hunt on the Arduino forums, I came across three strategies for reducing jitter:

### 1. Multiple reads
Some suggested just reading the pin twice. Interesting idea, but it didn't work for me. I was using an old potentiometer that I salvaged from a *very* poor quality guitar effects unit, so maybe jitter was worse than usual. 

### 2. Delay
Putting a small delay before and/or after reading the pin is not a bad idea. Apparenty there's a capacitor in there somewhere that needs time to charge/discharge, which seems reasonable. Adding a 20ms delay certainly helped... but I lost the responsive feel of my MIDI knobs.

### 3. Smoothing algorithms
Now when I found this idea, I got excited. The best algorithm I came across was an Exponential Moving Average (EMA) algorithm from  https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/. This worked really well! I then found out about the ResponsiveAnalogRead library, which does **way** more than I am doing here. The only reason I don't use that is that it uses quite a few more bytes than I have to spare, and it can't do internal scaling - I would have to scale it _after_ receiving a change which may not matter in a smaller scale. Apart from that, ResponsiveAnalogRead is vastly superior, so use that if you need a real precision instrument!

### Resolution
Another issue I had was the need to convert the potentiometer values into MIDI values, which range from 0-127. Although this is as simple as dividing the potentiometer value by 8, I wanted to add this to the class so that it could only fire the change event when this _scaled_ value had changed, not the raw potentiometer value. I have added a `resolution` property, which if non-zero simply calls `map(0, 2013, 0, resolution)` on the potentiometer value. Not only is this convenient, it also *greatly* reduced the jitter and the need for multiple reads and delays. Along with the smoothing algorithm, changing the resolution gave me extremely smooth pots that I could trust would not tell me they had changed unless I had deliberatly tweaked them. Success!!

However, note that due the way the EMA algorithm works, it is unlikely that you will ever get a maximum value. This is apparent when you set the resolution to 100 to get percentages: you will get values from 0 to 99. This is fine for my MIDI application, as setting the resolution to 128 gives me values from 0-127, but if you want a percentage from 0-100, you may have to set the resolution to 101 (and because I don't really understand the maths, maybe double-check that you're never getting 101 in your code! :) )


## Joysticks
I implemented a joystick class for the specific purpose of helping me enter text. I wanted a left/right 'jog' to move a cursor left and right, and up/down to change characters. Of course, just reading the joystick axes like potentiometers made the cursor shoot wildly left and right! 

### Threshold movement
To get a smooth experience, I add a threshold to the joystick class that makes it ignore changes that are less than `threshold` away from the centre of each axis (which is read on initialisation.) The default threshold is 150, but you can set it to 0 for maximum sensitivity. Additionally, I added a JC_Button style `changed()` method that only returns true if this threshold has been passed this loop(), so it will only 'jog' the cursor once per cycle.

### Holding the joystick 
If you want to hold the joystick for multiple jumps, just check for `joystick.changed() || joystick.heldLeftFor(ms)`, and take the same action for each case. Then when you hold it, you will get a single event, then after the delay, multiple events however fast you want to process them. Of course, you can always just ask for the raw x/y as well. 

### Delta, movedLeft(), and movingLeft()
As well as detecting basic changes, you can also ask how far the joystick has been moved from the centre by calling `getDeltaX()` or `getDeltaY()`. If you want to know if the stick has been moved in a direction since the last update loop, call `movedLeft()`. This will only return true if this value has *changed* since the last update. If you want to know if the joystick is moving left right now, regardless of its previous state, call `movingLeft()`.
