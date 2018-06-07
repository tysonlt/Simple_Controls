#ifndef THWAITES_CONTROLS_CONTROL_H
#define THWAITES_CONTROLS_CONTROL_H

#include <TC_Multiplexer.h>

/**
 * Mux-aware base class.
 * 
 * Overrides basic pin read/write functions to apply mux if applicable.
 */ 
class Control {

    protected:
        byte _muxChannel = 0;
        Multiplexer *_mux = nullptr;

        /**
         * Overloaded to apply mux channel first.
         */ 
        int digitalRead(uint8_t pin) {
            applyChannel();
            return ::digitalRead(pin);
        }

        /**
         * Overloaded to apply mux channel first.
         */ 
        void digitalWrite(uint8_t pin, uint8_t val) {
            applyChannel();
            ::digitalWrite(pin, val);
        }

        /**
         * Overloaded to apply mux channel first.
         */ 
        int analogRead(uint8_t pin) {
            applyChannel();
            return ::analogRead(pin);
        }

        /**
         * Overloaded to apply mux channel first.
         */ 
        void analogWrite(uint8_t pin, int val) {
            applyChannel();
            ::analogWrite(pin, val);
        }

        /**
         * Apply mux channel, if configured
         */ 
        void applyChannel() {
            if (_mux) {
                _mux->setChannel(_muxChannel);
            }
        }

};

#endif