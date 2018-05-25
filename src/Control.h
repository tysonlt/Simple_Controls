#ifndef THWAITES_CONTROLS_CONTROL_H
#define THWAITES_CONTROLS_CONTROL_H

#include "Arduino.h"

/**
 * Virtual class with basic features.
 * 
 * Includes support for multiplexing, copied from https://github.com/waspinator/CD74HC4067. 
 * Code has been copied due to simplicity and to reduce need for dependances.
 */ 
class Control {

    public:

        /**
         * Initialise.
         * 
         * May read the pin to get an initial value, but
         * changed() will always return false until read() 
         * is called.
         */
        virtual void begin() =0;

        /**
         * Update current value of the control and test whether we have changed.
         * 
         * This should be called once in the Arduino loop().
         * 
         * @return boolean Whether the value has changed since last read.
         */
        virtual boolean read() =0;

        /**
         * Whether the value has changed since the last read.
         */
        inline boolean changed() { return _changed; }

        /**
         * Time since last change in millis.
         */
        inline int lastChange() { return _lastChange; }

        /**
         * Set control pins used for multiplexing.
         */ 
        inline void setControlPins(uint8_t control1, uint8_t control2, uint8_t control3, uint8_t control4) {
            
            _control1 = control1;
            _control2 = control2;
            _control3 = control3;
            _control4 = control4;

            pinMode(_control1, OUTPUT);
            pinMode(_control2, OUTPUT);
            pinMode(_control3, OUTPUT);
            pinMode(_control4, OUTPUT);

        }

        /**
         * Set the mux channel used for this control.
         */ 
        inline void setMultiplexChannel(uint8_t channel) { 
            _channel = channel; 
        }

    protected:

        /**
         * Automatically applies the mux channel, if set.
         */ 
        inline int digitalRead(uint8_t pin) {
            switchChannel();
            return ::digitalRead(pin);
        }

        /**
         * Automatically applies the mux channel, if set.
         */ 
        inline void digitalWrite(uint8_t pin, uint8_t val) {
            switchChannel();
            ::digitalWrite(pin, val);
        }

        /**
         * Automatically applies the mux channel, if set.
         */ 
        inline int analogRead(uint8_t pin) {
            switchChannel();
            return ::analogRead(pin);
        }

        /**
         * Automatically applies the mux channel, if set.
         */ 
        inline void analogWrite(uint8_t pin, int val) {
            switchChannel();
            ::analogWrite(pin, val);
        }

    protected:
        uint8_t _control1, _control2, _control3, _control4;
        int _channel = -1; 
        int _time = 0, _lastChange = 0;
        boolean _changed = false;

        /**
         * Switch the channel, if configured.
         */ 
        inline void switchChannel() {

            if (_channel > -1) {
                digitalWrite(_control1, _CHANNEL_VALUES[_channel][0]);
                digitalWrite(_control2, _CHANNEL_VALUES[_channel][1]);
                digitalWrite(_control3, _CHANNEL_VALUES[_channel][2]);
                digitalWrite(_control4, _CHANNEL_VALUES[_channel][3]);
            }
            
        }

    private:
        /**
         * @see https://github.com/waspinator/CD74HC4067. 
         */ 
        const uint8_t _CHANNEL_VALUES[16][4] = {
          //s0,  s1, s2, s3     channel
            {0,  0,  0,  0}, // 0
            {1,  0,  0,  0}, // 1
            {0,  1,  0,  0}, // 2
            {1,  1,  0,  0}, // 3
            {0,  0,  1,  0}, // 4
            {1,  0,  1,  0}, // 5
            {0,  1,  1,  0}, // 6
            {1,  1,  1,  0}, // 7
            {0,  0,  0,  1}, // 8
            {1,  0,  0,  1}, // 9
            {0,  1,  0,  1}, // 10
            {1,  1,  0,  1}, // 11
            {0,  0,  1,  1}, // 12
            {1,  0,  1,  1}, // 13
            {0,  1,  1,  1}, // 14
            {1,  1,  1,  1}  // 15
        };

};

#endif