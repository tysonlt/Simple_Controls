// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#include "SC_Button.h"

/*----------------------------------------------------------------------*
/ initialize a Button object and the pin it's connected to.             *
/-----------------------------------------------------------------------*/
void Button::begin() {
    pinMode(_pin, _puEnable ? INPUT_PULLUP : INPUT);    
    _state = digitalRead(_pin);
    if (_invert) _state = !_state;
    _lastState = _state;
    _time = millis();
    _lastChange = _time;
    _changed = false;
}

/*----------------------------------------------------------------------*
/ returns the state of the button, true if pressed, false if released.  *
/ does debouncing, captures and maintains times, previous state, etc.   *
/-----------------------------------------------------------------------*/
boolean Button::read() {    

    uint32_t ms = millis();
    boolean pinVal = digitalRead(_pin);
    if (_invert) pinVal = !pinVal;
    if (ms - _lastChange < _dbTime) {
        _changed = false;
    } else {
        _lastState = _state;
        _state = pinVal;
        _changed = (_state != _lastState);				                
        if (_changed) {
            _lastChange = ms;
        }
    }
    _time = ms;
    return _state;
}

/*----------------------------------------------------------------------*
 * isPressed() and isReleased() check the button state when it was last *
 * read, and return false (0) or true (!=0) accordingly.                *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
boolean Button::isPressed() {
    return _state;
}

boolean Button::isReleased() {
    return !_state;
}

/*----------------------------------------------------------------------*
 * wasPressed() and wasReleased() check the button state to see if it   *
 * changed between the last two reads and return false (0) or           *
 * true (!=0) accordingly.                                              *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
boolean Button::wasPressed() {
    return _state && _changed;
}

boolean Button::wasReleased() {
    return !_state && _changed;
}

/*----------------------------------------------------------------------*
 * pressedFor(ms) and releasedFor(ms) check to see if the button is     *
 * pressed (or released), and has been in that state for the specified  *
 * time in milliseconds. Returns false (0) or true (!=0) accordingly.   *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
boolean Button::pressedFor(uint32_t ms) {
    return _state && _time - _lastChange >= ms;
}

boolean Button::releasedFor(uint32_t ms) {
    return !_state && _time - _lastChange >= ms;
}

/*----------------------------------------------------------------------*
 * lastChange() returns the time the button last changed state,         *
 * in milliseconds.                                                     *
 *----------------------------------------------------------------------*/
uint32_t Button::lastChange() {
    return _lastChange;
}
