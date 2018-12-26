#pragma once

#include "Arduino.h"
#include "SC_Control.h"

/**
 * Joystick class to simplify reading a joystick.
 * 
 * Does not handle the joystick button, that's just a normal analog button.
 * 
 * If you set a threshold, change will not be registered until the stick has
 * moved by at least that amount in any direction. This is useful if you want
 * to 'nudge' the joystick, ie for text entry. This also helps to reduce jitter.
 * 
 * Inspired by https://github.com/JChristensen/JC_Button.
 */
class Joystick : public Control {

  const int  DEFAULT_THRESHOLD  = 150;
  const byte LEFT               = 1<<0;
  const byte RIGHT              = 1<<1;
  const byte UP                 = 1<<2;
  const byte DOWN               = 1<<3;

  public:

    /**
     * Supply pins for x and y axis.
     */
    Joystick(byte pinX, byte pinY, int threshold = 150) : 
      _pinX(pinX), _pinY(pinY), _threshold(threshold) {}

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
     * Returns the current x value.
     */ 
    int getX();

    /**
     * Returns the current y value.
     */ 
    int getY();

    /**
     * The current distance from the centre of the joystick.
     */ 
    int getDeltaX();
    
    /**
     * The current distance from the centre of the joystick.
     */
    int getDeltaY();
    
    /**
     * Whether the joystick is currently moving left.
     */ 
    boolean movingLeft();
    
    /**
     * Whether the joystick is currently moving right.
     */
    boolean movingRight();
    
    /**
     * Whether the joystick is currently moving up.
     */
    boolean movingUp();
    
    /**
     * Whether the joystick is currently moving down.
     */
    boolean movingDown();
  
    /**
     * Whether the joystick has moved left since last read.
     */ 
    boolean movedLeft() ;
    
    /**
     * Whether the joystick has moved right since last read.
     */
    boolean movedRight();
    
    /**
     * Whether the joystick has moved up since last read.
     */
    boolean movedUp();
    
    /**
     * Whether the joystick has moved down since last read.
     */
    boolean movedDown();
  
    /**
     * Whether the joystick has been moving left for ms milliseconds.
     * 
     * @param int milliseconds to consider.
     */
    boolean heldLeftFor(int ms);
    
    /**
     * Whether the joystick has been moving right for ms milliseconds.
     * 
     * @param int milliseconds to consider.
     */
    boolean heldRightFor(int ms);
    
    /**
     * Whether the joystick has been moving up for ms milliseconds.
     * 
     * @param int milliseconds to consider.
     */
    boolean heldUpFor(int ms);
    
    /**
     * Whether the joystick has been moving down for ms milliseconds.
     * 
     * @param int milliseconds to consider.
     */
    boolean heldDownFor(int ms);

    /**
     * Whether the value has changed since the last read.
     */
    inline boolean changed() { return _changed; }

    /**
     * Time since last change in millis.
     */
    inline int lastChange() { return _lastChange; }
  
  protected:
    byte _pinX;
    byte _pinY;
    int _threshold;
    int _x, _y, _centreX, _centreY;
    byte _lastFlags = 0, _flags = 0;
    int _time = 0, _lastChange = 0;
    boolean _changed = false;

    /**
     * Read the pins.
     */ 
    virtual void _readPins() {
      _x = analogRead(_pinX);
      _y = analogRead(_pinY);
    }

};
