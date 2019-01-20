#pragma once

#include "Arduino.h"

/**
 * A simple Multiplexer.
 * 
 * Does not handle actually reading the signal pin.
 * 
 * Based on https://github.com/mikedotalmond/Arduino-Mux-CD74HC4067
 */ 
class Multiplexer {

    public:

        /**
         * 
         */ 
        Multiplexer(byte pin0, byte pin1, byte pin2, byte pin3, byte enablePin = 0) {
            _pins[0] = pin0;
            _pins[1] = pin1;
            _pins[2] = pin2;
            _pins[3] = pin3;
            _enablePin = enablePin;    
            _setup();
        }

        /**
         * Turn the mux on, if enable pin was set
         * @return Whether the enable pin is set (ie, whether this operation did anything)
         */
        boolean setEnabled(boolean enabled) {
            if (_enablePin) {
                digitalWrite(_enablePin, enabled ? LOW : HIGH);
            }
            return _enablePin; 
        }

        /**         
         * Set the current mux channel [0-15] using 4 digtal pins to write the 4 bit integer
         */
        void setChannel(byte channel) {
            for (byte i=0; i<4; i++) {                       
                digitalWrite(_pins[i], bitRead(channel, i));
            }
        }

    private:
        byte _pins[4];
        byte _enablePin; 

        /**
         * Set pin modes and enable pin.
         * @private
         */ 
        void _setup() {
                        
            //set pin modes
            for (byte i=0; i<4; i++) {            
                pinMode(_pins[i], OUTPUT);                
            }

            //enable
            if (_enablePin) {
                pinMode(_enablePin, OUTPUT);	
                setEnabled(true);
            }


        }

};
