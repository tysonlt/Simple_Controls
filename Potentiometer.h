#ifndef THWAITES_CONTROLS_POTENTIOMETER_H
#define THWAITES_CONTROLS_POTENTIOMETER_H

#include "Arduino.h"

/**
 * Class to provide smooth, easy reading of a potentiometer.
 * 
 * Can be configured to do multiple reads, add a small delay per read, and use a smoothing algorithm.
 * There is an option to scale the output, which helps reduced jitter as well.
 * 
 * Inspired by JC_Button.
 */
class Potentiometer {

  /**
   * Maxiumum value of the potentiometer.
   */
  const int MAX = 1023;

  public:

    /**
     * Create a new potentiometer object.
     * 
     * @param int pin The pin the pot is connected to.
     * @param int resolution (Optional) Supply a number smaller than MAX(1023) to have output scaled.
     * @param byte smoothingFactor (Optional) The smoothing factor to use. Default is 4. Supply 0 to disable.
     * @param byte readCount (Optional) How many times to read the pin. Default is 1.
     * @param byte readDelay (Optional) Adds a small delay before each read. Default is 1. Supply 0 to disable.
     */
    Potentiometer(byte pin, int resolution = 0, byte smoothingFactor = 4, byte readCount = 1, byte readDelay = 1) : 
      _pin(pin), _resolution(resolution), _smoothingFactor(smoothingFactor), _readCount(readCount), _readDelay(readDelay) {}
  
    /**
     * Set the resolution to remap values to.
     * 
     * For example, for a MIDI control, set resolution to 128.
     */ 
    void setResolution(int resolution);

    /**
     * Set the smoothing factor to use.
     * 
     * Algorithm: value += (analogRead() - value) / smoothingFactor
     * 
     * Default is 4.
     */ 
    void setSmoothingFactor(byte smoothingFactor);

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
     * How many milliseconds to delay before reading the pin.
     * 
     * Increased delays may help reduce jitter, especially
     * if not using the smoothing algorithm.
     * 
     * Defaults to 1.
     */ 
    void setReadDelay(byte readDelay);

    /**
     * Initialise.
     * 
     * Does an initial read as a starting point, but
     * does not update the changed status or apply smoothing.
     */
    void begin();

    /**
     * Update current value of potentiometer
     * and test whether we have changed.
     * 
     * @return boolean Whether the value has changed since last read.
     */
    boolean read();

    /**
     * Whether the value has changed since the last read.
     */
    boolean changed();

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
     * Time since last change in millis.
     */
    int lastChange();

  private:
    byte _pin;
    int _resolution = 0;
    /*float _emaAlpha = 0.6;*/
    byte _smoothingFactor = 4;
    byte _readCount = 1; 
    byte _readDelay = 5;

    boolean _changed = false;
    int _value = 0, _lastValue = 0;
    int _time = 0, _lastChange = 0;

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
    int _smoothValue(int raw);
  
};

#endif