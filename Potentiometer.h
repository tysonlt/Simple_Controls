/**
 * Inspired by JC_Button.
 * 
 * Can be configured to do multipe reads, add a small delay per read, and use a smoothing algorithm.
 * There is an option to scale the output, which helps reduced jitter as well.
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
     * Initialise.
     * 
     * Does an initial read as a starting point, but
     * will not update the changed status.
     */
    void begin() { 
      _value = analogRead(_pin);
      _lastValue = _value;
      _time = millis();
      _lastChange = _time;
    }

    /**
     * Update current value of potentiometer
     * and test whether we have changed.
     */
    boolean read() {

      //get time of read
      _time = millis();
  
      //read the pin
      _readPin();
  
      //have we changed since last read?
      _calculateChanged();

      return _changed;
      
    }

    /**
     * Whether the value has changed since the last update.
     */
    boolean changed() {
      return _changed;
    }

    /**
     * Get the current potentiometer value at the configured resolution.
     */
    int getValue() {
      return _applyResolution(_value);
    }

    /**
     * Get current value, ignoring resolution.
     */
    int getRawValue() {
      return _value;
    }
  
    /**
     * Time since last change in millis.
     */
    int lastChange() {
      return _lastChange;
    }

  private:
    byte _pin;
    int _resolution = 0;
    /*float _smoothingFactor = 0.6;*/
    byte _smoothingFactor = 4;
    byte _readCount = 1; 
    byte _readDelay = 5;

    boolean _changed = false;
    int _value = 0, _lastValue = 0;
    int _time = 0, _lastChange = 0;

    /**
     * Calculate whether to set _changed based on resolution.
     */
    void _calculateChanged() {

      //compare values at the desired resolution
      int current = _applyResolution(_value);
      int last = _applyResolution(_lastValue);
  
      //have we changed since last read?
      _changed = current != last;
      if (_changed) {
        _lastChange = _time;
      }

    }

    /**
     * Change value to configured resolution.
     */
    int _applyResolution(int raw) {
      if (_resolution > 0) {
        return map(raw, 0, MAX, 0, _resolution);
      } else {
        return raw;
      }
    }
    
    /**
     * Read pin using various anti-jitter strategies, if requested.
     */
    void _readPin() {

      int raw = 0;
      
      //save old value
      _lastValue = _value;

      //read as many times as asked to (may help prevent jitter)
      for (byte i=0; i<_readCount; i++) {

        //this may help prevent jitter and interference with other pins
        if (_readDelay > 0) {
          delay(_readDelay);
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
    int _smoothValue(int raw) {

      if (_smoothingFactor <= 0) {

        //no smoothing
        return raw; 

      } else {

        //use current value
        int v = _value;

        /*
        //Exponential moving average
        //calculate the smoothed value (see https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/)
        v = (_smoothingFactor * raw) + ((1 - _smoothingFactor) * v);
        */

        //this is as simple as it is brilliant...
        //https://electronics.stackexchange.com/questions/64677/how-to-smooth-potentiometer-values
        v += (raw - v) / _smoothingFactor;

        return v;
        
      }
      
    }
  
};

