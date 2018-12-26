/**
 * Class to provide smooth, easy reading of a potentiometer.
 * 
 * Can be configured to do multiple reads, add a small delay per read, and use a smoothing algorithm.
 * There is an option to scale the output, which helps reduced jitter as well.
 * 
 * Inspired by https://github.com/JChristensen/JC_Button.
 */

#include "SC_Potentiometer.h"

/**
 * Initialise.
 * 
 * Does an initial read as a starting point, but
 * will not update the changed status.
 */
void Potentiometer::begin() { 
    _value = analogRead(_pin);
    _lastValue = _value;
    _time = millis();
    _lastChange = _time;    
}

/**
 * Update current value of potentiometer
 * and test whether we have changed.
 * 
 * This should be called once in the Arduino loop().
 */
boolean Potentiometer::read() {

    //get time of read
    _time = millis();

    //read the pin
    _readPin();

    //have we changed since last read?
    _calculateChanged();

    return _changed;
    
}

/**
 * Set the resolution to remap values to.
 * 
 * For example, for a MIDI control, set resolution to 128.
 */ 
void Potentiometer::setResolution(int resolution) {
    _resolution = resolution;
}

/**
 * Set the smoothing factor to use.
 * 
 * Uses Exponential Moving Average to smooth the output.
 * 
 * Default is 0.6.
 */ 
void Potentiometer::setSmoothingFactor(float smoothingFactor) {
    _smoothingFactor = smoothingFactor;
}

/**
 * Set how many times to read the pin.
 * 
 * Multiple reads may help reduce jitter, especially
 * if not using the smoothing algorithm.
 * 
 * Default is 1.
 */ 
void Potentiometer::setReadCount(byte readCount) {
    _readCount = readCount;
}

/**
 * How many milliseconds to delay before reading the pin.
 * 
 * Increased delays may help reduce jitter, especially
 * if not using the smoothing algorithm.
 * 
 * Defaults to 1.
 */ 
void Potentiometer::setReadDelay(unsigned int readDelay) {
    _readDelay = readDelay;
}

/**
 * Get the current potentiometer value at the configured resolution.
 */
int Potentiometer::getValue() {
    return _applyResolution(_value);
}

/**
 * Get current value, ignoring resolution.
 */
int Potentiometer::getRawValue() {
    return _value;
}

/**
 * Read pin using various anti-jitter strategies, if requested.
 */
void Potentiometer::_readPin() {

    int raw = 0;
    
    //save old value
    _lastValue = _value;

    //read as many times as asked to (may help prevent jitter)
    for (byte i=0; i<_readCount; i++) {

        //this may help prevent jitter and interference with other pins
        if (_readDelay > 0) {
            delayMicroseconds(_readDelay);
        }

        //read the pin
        raw = analogRead(_pin);
        
    }

    //smooth the value if requested
    _value = _smoothValue(raw);
        
}

/**
 * Smooth the value based on smoothing strategy and settings.
 */ 
int Potentiometer::_smoothValue(const int raw) {

    if (_smoothingFactor <= 0) {

        //no smoothing configured
        return raw; 

    } else {

        //use current value (don't change it)
        int v = _value;
        
        //Exponential moving average
        //calculate the smoothed value (see https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/)
        v = (_smoothingFactor * raw) + ((1 - _smoothingFactor) * v);
        
        return v;
    
    }
    
}

/**
 * Calculate whether to set _changed based on resolution.
 */
void Potentiometer::_calculateChanged() {

    //compare values at the desired resolution
    _changed = _applyResolution(_value) != _applyResolution(_lastValue);
    if (_changed) {
        _lastChange = _time;
    }

}

/**
 * Change value to configured resolution.
 */
int Potentiometer::_applyResolution(int raw) {
    if (_resolution > 0) {
        return map(raw, 0, MAX, 0, _resolution);
    } else {
        return raw;
    }
}
