/**
 * Joystick class to simplify reading a joystick.
 * 
 * Does not handle the joystick button, that's just a normal analog button. 
 * Use JC_Button for that!
 * 
 * If you set a threshold, change will not be registered until the stick has
 * moved by at least that amount in any direction. This is useful if you want
 * to 'nudge' the joystick, ie for text entry. This also helps to reduce jitter.
 * 
 * Inspired by https://github.com/JChristensen/JC_Button.
 */

#include "SC_Joystick.h"

/**
 * Saves the current x/y as the centre.
 */
void Joystick::begin() { 
    _lastFlags = 0;
    _flags = 0;
    _time = millis();
    _lastChange = _time;
    _readPins();
    _centreX = _x;
    _centreY = _y;
}

/**
 * Update current x/y. 
 * 
 * This should be called once in the Arduino loop().
 */
boolean Joystick::read() {

    //get time of read
    _time = millis();

    //save last state
    _lastFlags = _flags;
    _flags = 0;

    //read the pins
    _readPins();

    //set flags for x axis
    if (_x > _centreX + _threshold) {
        _flags |= RIGHT;
    } else if (_x < _centreX - _threshold) {
        _flags |= LEFT;
    }

    //set flags for y axis (both axes can change at once)
    if (_y < _centreY - _threshold) {
        _flags |= UP;
    } else if (_y > _centreY + _threshold) {
        _flags |= DOWN;
    }

    //have we changed since last read?
    _changed = _flags != _lastFlags;
    if (_changed) {
        _lastChange = _time;
    }

    return _changed;
    
}

/**
 * Returns the current x value.
 */ 
int Joystick::getX() { 
    return _x; 
}

/**
 * Returns the current y value.
 */ 
int Joystick::getY() { 
    return _y; 
}

/**
 * The current distance from the centre of the joystick.
 */ 
int Joystick::getDeltaX() { 
    return _x - _centreX; 
}

/**
 * The current distance from the centre of the joystick.
 */
int Joystick::getDeltaY() { 
    return _y - _centreY; 
}

/**
 * Whether the joystick is currently moving left.
 */ 
boolean Joystick::movingLeft() { 
    return _flags & LEFT; 
}

/**
 * Whether the joystick is currently moving right.
 */
boolean Joystick::movingRight() { 
    return _flags & RIGHT; 
}

/**
 * Whether the joystick is currently moving up.
 */
boolean Joystick::movingUp() { 
    return _flags & UP; 
}

/**
 * Whether the joystick is currently moving down.
 */
boolean Joystick::movingDown() { 
    return _flags & DOWN; 
}

/**
 * Whether the joystick has moved left since last read.
 */ 
boolean Joystick::movedLeft() { 
    return _changed && movingLeft(); 
}

/**
 * Whether the joystick has moved right since last read.
 */
boolean Joystick::movedRight() { 
    return _changed && movingRight(); 
}

/**
 * Whether the joystick has moved up since last read.
 */
boolean Joystick::movedUp() { 
    return _changed && movingUp(); 
}

/**
 * Whether the joystick has moved down since last read.
 */
boolean Joystick::movedDown() { 
    return _changed && movingDown(); 
}

/**
 * Whether the joystick has been moving left for ms milliseconds.
 */
boolean Joystick::heldLeftFor(int ms) { 
    return movingLeft() && _time - _lastChange > ms; 
}

/**
 * Whether the joystick has been moving right for ms milliseconds.
 */
boolean Joystick::heldRightFor(int ms) { 
    return movingRight() && _time - _lastChange > ms; 
}

/**
 * Whether the joystick has been moving up for ms milliseconds.
 */
boolean Joystick::heldUpFor(int ms) { 
    return movingUp() && _time - _lastChange > ms; 
}

/**
 * Whether the joystick has been moving down for ms milliseconds.
 */
boolean Joystick::heldDownFor(int ms)  { 
    return movingDown() && _time - _lastChange > ms; 
}
