/**
 * Inspired by JC_Button.
 */
class Joystick {

  const int  DEFAULT_THRESHOLD  = 150;
  const byte LEFT               = 1<<0;
  const byte RIGHT              = 1<<1;
  const byte UP                 = 1<<2;
  const byte DOWN               = 1<<3;

  public:

    /**
     * Supply pins for x and y axis.
     */
    Joystick(byte pin_x, byte pin_y, int threshold = 150) : 
      _pin_x(pin_x), _pin_y(pin_y), _threshold(threshold) {}
    
    /**
     * Saves the current x/y as the centre.
     */
    void begin() { 
      _last_flags = 0;
      _flags = 0;
      _time = millis();
      _lastChange = _time;
      _centre_x = analogRead(_pin_x);
      _centre_y = analogRead(_pin_y);
    }
  
    /**
     * Update current x/y. 
     */
    boolean read() {

      //get time of read
      _time = millis();
  
      //save last state
      _last_flags = _flags;
      _flags = 0;
  
      //read the pins
      _x = analogRead(_pin_x);
      _y = analogRead(_pin_y);

      //set flags for x axis
      if (_x > _centre_x + _threshold) {
        _flags |= RIGHT;
      } else if (_x < _centre_x - _threshold) {
        _flags |= LEFT;
      }
  
      //set flags for y axis (both axes can change at once)
      if (_y < _centre_y - _threshold) {
        _flags |= UP;
      } else if (_y > _centre_y + _threshold) {
        _flags |= DOWN;
      }
  
      //have we changed since last read?
      _changed = _flags != _last_flags;
      if (_changed) {
        _lastChange = _time;
      }

      return _changed;
      
    }

    /**
     * Time since last change in millis.
     */
    int lastChange() {
      return _lastChange;
    }

    int getX() { return _x; }
    int getY() { return _y; }

    int getDeltaX() { return _x - _centre_x; }
    int getDeltaY() { return _y - _centre_y; }
    
    boolean movingLeft()  { return _flags & LEFT; }
    boolean movingRight() { return _flags & RIGHT; }
    boolean movingUp()    { return _flags & UP; }
    boolean movingDown()  { return _flags & DOWN; }
  
    boolean movedLeft()   { return _changed && movingLeft(); }
    boolean movedRight()  { return _changed && movingRight(); }
    boolean movedUp()     { return _changed && movingUp(); }
    boolean movedDown()   { return _changed && movingDown(); }
  
    boolean heldLeftFor(int ms)  { return movingLeft()  && _time - _lastChange > ms; }
    boolean heldRightFor(int ms) { return movingRight() && _time - _lastChange > ms; }
    boolean heldUpFor(int ms)    { return movingUp()    && _time - _lastChange > ms; }
    boolean heldDownFor(int ms)  { return movingDown()  && _time - _lastChange > ms; }
  
  private:
    byte _pin_x;
    byte _pin_y;
    int _threshold;
    boolean _changed = false;
    int _x, _y, _centre_x, _centre_y;
    byte _last_flags = 0, _flags = 0;
    int _time = 0, _lastChange = 0;
  
};

