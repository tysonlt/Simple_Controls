#ifndef THWAITES_CONTROLS_POTENTIOMETER_H
#define THWAITES_CONTROLS_POTENTIOMETER_H

#include "Arduino.h"
#include "TC_Control.h"

/**
 * Class to provide smooth, easy reading of a potentiometer.
 * 
 * Can be configured to do multiple reads, add a small delay per read, and use a smoothing algorithm.
 * There is an option to scale the output, which helps reduced jitter as well.
 * 
 * Inspired by https://github.com/JChristensen/JC_Button.
 * Smoothing algorithm is from https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/
 */
class Potentiometer : public Control {

  /**
   * Maxiumum value of the potentiometer.
   */
  const int MAX = 1023;

  public:

    /**
     * Create a new potentiometer object.
     * 
     * @param int pin The pin the pot is connected to.
     * @param float smoothingFactor (Optional) The smoothing factor to use. Default is 0.6. Supply 0 to disable.
     * @param int resolution (Optional) Supply a number smaller than MAX(1023) to have output scaled.
     * @param byte readCount (Optional) How many times to read the pin. Default is 1.
     * @param byte readDelay (Optional) Adds a small delay before each read. Default is 1. Supply 0 to disable.
     */  
    Potentiometer(byte pin, int resolution = 0, float smoothingFactor = 0.6, byte readCount = 1, unsigned int readDelay = 1, Multiplexer *mux=nullptr, byte muxChannel=0) : 
      _pin(pin), _resolution(resolution), _smoothingFactor(smoothingFactor), _readCount(readCount), _readDelay(readDelay) {
      setMultiplexer(_mux, muxChannel);
    }
  
    /**
     * Initialise.
     * 
     * May read the pin to get an initial value, but
     * changed() will always return false until read() 
     * is called.
     */
    virtual void begin();

    /**
     * Update current value of the control and test whether we have changed.
     * 
     * This should be called once in the Arduino loop().
     * 
     * @return boolean Whether the value has changed since last read.
     */
    virtual boolean read();

    /**
     * Set the resolution to remap values to.
     * 
     * For example, for a MIDI control, set resolution to 128.
     */ 
    void setResolution(int resolution);

    /**
     * Set the smoothing alpha factor to use.
     * 
     * Uses Exponential Moving Average to smooth the output.
     * 
     * Default is 0.6.
     */ 
    void setSmoothingFactor(float smoothingFactor);

    /**
     * Set how many times to read the pin.
     * 
     * Multiple reads may help reduce jitter, especially
     * if not using the smoothing algorithm.
     * 
     * Default is 1.
     */ 
    void setReadCount(byte readCount);

    /**
     * How many microseconds to delay before reading the pin.
     * 
     * Increased delays may help reduce jitter, especially
     * if not using the smoothing algorithm.
     * 
     * Defaults to 1.
     */ 
    void setReadDelay(unsigned int readDelay);

    /**
     * Get the current potentiometer value at the configured resolution.
     * 
     * Smoothing and resolution mapping will be applied if configured.
     */
    int getValue();

    /**
     * Get raw pin value, ignoring smoothing and resolution.
     */
    int getRawValue();

    /**
     * Whether the value has changed since the last read.
     */
    inline boolean changed() { return _changed; }

    /**
     * Sometimes required to convince the pot it hasn't changed. Bit of a hack.
     */ 
    inline void resetChanged() { _changed = false; }

    /**
     * Time since last change in millis.
     */
    inline int lastChange() { return _lastChange; }

  private:
    byte _pin;
    int _resolution;
    float _smoothingFactor;
    byte _readCount; 
    unsigned int _readDelay;
    int _time = 0, _lastChange = 0;
    int _value, _lastValue;
    boolean _changed = false;
    
    /**
     * Calculate whether to set _changed based on resolution.
     */
    void _calculateChanged();

    /**
     * Change value to configured resolution.
     */
    int _applyResolution(int raw);
    
    /**
     * Read pin using various anti-jitter strategies, if requested.
     */
    void _readPin();

    /**
     * Smooth the value based on smoothing strategy and settings.
     */ 
    int _smoothValue(const int raw);
  
};

#endif