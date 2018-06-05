#ifndef THWAITES_CONTROLS_MULTIPLEXER_H
#define THWAITES_CONTROLS_MULTIPLEXER_H

#include "Arduino.h"
#include "TC_Control.h"

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
        Multiplexer(byte pin0, byte pin1, byte pin2, byte pin3, byte enablePin = -1) {
            _pins[0] = pin0;
            _pins[1] = pin1;
            _pins[2] = pin2;
            _pins[3] = pin3;
            _enablePin = enablePin;    
            _setup();
        }

        /**
         * Turn the mux on, if enable pin was set
         */
        void setEnabled(bool enabled) {
            if (_enablePin > -1) {
                digitalWrite(_enablePin, enabled ? LOW : HIGH);
            }
        }

        /**         
         * Set the current mux channel [0-15] using 4 digtal pins to write the 4 bit integer
         */
        void setChannel(int channel) {
            for (byte i=0; i<4; i++) {                       
                digitalWrite(_pins[i], bitRead(channel, i));
            }
        }

    private:
        byte _pins[4];
        int _enablePin = -1; 

        /**
         * Set pin modes and enable pin.
         * @private
         */ 
        void _setup() {
                        
            //set pin modes
            for (byte i=0; i<4; i++) {            
                pinMode(_pins[i], OUTPUT);
                setEnabled(true);
            }

            //enable
            if (_enablePin > -1) {
                pinMode(_enablePin, OUTPUT);	
                digitalWrite(_enablePin, LOW); // start enabled
            }


        }

};

#endif