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
            : m_pin(pin), m_dbTime(dbTime), m_puEnable(puEnable), m_invert(invert) {
                setMultiplexer(mux, muxChannel);
            }

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
        inline boolean changed() { return m_changed; }

    private:
        uint8_t m_pin;          // arduino pin number connected to button
        uint32_t m_dbTime;      // debounce time (ms)
        boolean m_puEnable;        // internal pullup resistor enabled
        boolean m_invert;          // if true, interpret logic low as pressed, else interpret logic high as pressed
        boolean m_state;           // current button state, true=pressed
        boolean m_lastState;       // previous button state
        boolean m_changed;         // state changed since last read
        uint32_t m_time;        // time of current state (ms from millis)
        uint32_t m_lastChange;  // time of last state change (ms)
        
};
