#pragma once

#include <SC_Multiplexer.h>

/**
 * Mux-aware base class.
 * 
 * Overrides basic pin read/write functions to apply mux if applicable.
 */ 
class Control {    

    public:

        /**
         * Initialize a control object and the pin it's connected to.
         */ 
        virtual void begin();

        /**
         * Read the pin and update internal state.
         */ 
        virtual boolean read();        

        /**
         * Whether the value has changed since the last read.
         */
        virtual boolean changed();

        /**
         * Use Multiplexer when reading pin.
         */ 
        void setMultiplexer(Multiplexer *mux, byte channel) {
            _mux = mux;
            _muxChannel = channel;            
        }

    protected:
        byte _muxChannel = 0;
        Multiplexer *_mux = nullptr;
        boolean _changed = false;

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
