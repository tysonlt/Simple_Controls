// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#pragma once

#include <Arduino.h>
#include "SC_Control.h"

class Button : public Control
{
    public:

        Button() {
            setPullupEnable(true);
            setInverted(true);
            setDebounceTime(25);
        }

        // Button(pin, dbTime, puEnable, invert) instantiates a button object.
        //
        // Required parameter:
        // pin      The Arduino pin the button is connected to
        //
        // Optional parameters:
        // dbTime   Debounce time in milliseconds (default 25ms)
        // puEnable true to enable the AVR internal pullup resistor (default true)
        // invert   true to interpret a low logic level as pressed (default true)
        Button(uint8_t pin, uint32_t dbTime=25, uint8_t puEnable=true, uint8_t invert=true, Multiplexer *mux=nullptr, byte muxChannel=0)
            : _pin(pin), _dbTime(dbTime), _puEnable(puEnable), _invert(invert) {
                setMultiplexer(mux, muxChannel);
            }

        inline void setPin(uint8_t pin) { _pin = pin; }
        inline void setDebounceTime(uint32_t dbTime) { _dbTime = dbTime; }
        inline void setPullupEnable(uint8_t puEnable) { _puEnable = puEnable; }
        inline void setInverted(uint8_t invert) { _invert = invert; }

        // Initialize a control object and the pin it's connected to
        virtual void begin();

        // Returns the current debounced button state, true for pressed,
        // false for released. Call this function frequently to ensure
        // the sketch is responsive to user input.
        virtual boolean read();

        // Returns true if the button state was pressed at the last call to read().
        // Does not cause the button to be read.
        boolean isPressed();

        // Returns true if the button state was released at the last call to read().
        // Does not cause the button to be read.
        boolean isReleased();

        // Returns true if the button state at the last call to read() was pressed,
        // and this was a change since the previous read.
        boolean wasPressed();

        // Returns true if the button state at the last call to read() was released,
        // and this was a change since the previous read.
        boolean wasReleased();

        // Returns true if the button state at the last call to read() was pressed,
        // and has been in that state for at least the given number of milliseconds.
        boolean pressedFor(uint32_t ms);

        // Returns true if the button state at the last call to read() was released,
        // and has been in that state for at least the given number of milliseconds.
        boolean releasedFor(uint32_t ms);

        // Returns the time in milliseconds (from millis) that the button last
        // changed state.
        uint32_t lastChange();

        /**
         * Whether the value has changed since the last read.
         */
        inline boolean changed() { return _changed; }

    protected:
        uint8_t _pin;          // arduino pin number connected to button
        uint32_t _dbTime;      // debounce time (ms)
        boolean _puEnable;     // internal pullup resistor enabled
        boolean _invert;       // if true, interpret logic low as pressed, else interpret logic high as pressed
        boolean _state;        // current button state, true=pressed
        boolean _lastState;    // previous button state
        uint32_t _time;        // time of current state (ms from millis)
        uint32_t _lastChange;  // time of last state change (ms)
        
};
