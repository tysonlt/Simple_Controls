#pragma once

#include "Arduino.h"
#include "TC_Joystick.h"

/**
 * Extension of joystick to work with a multiplexer.
 */
class MultiplexingJoystick : public Joystick {

    public:

        /**
         * Mux version.
         */ 
        MultiplexingJoystick(byte signalPin, Multiplexer *mux, byte muxChannelX, byte muxChannelY, int threshold = 150) : 
            Joystick(0, 0, threshold), _channelX(muxChannelX), _channelY(muxChannelY) {        
                _pinX = signalPin; //use x as the sig pin
                setMultiplexer(mux, 0); //mux channel will be set for each axis at read time
        }

    protected:
        byte _channelX, _channelY;

        /**
         * Switch mux channel before reading each pin.
         */ 
        void _readPins() override {
            
            _muxChannel = _channelX;
            _x = analogRead(_pinX);

            _muxChannel = _channelY;
            _y = analogRead(_pinX);

        }

};