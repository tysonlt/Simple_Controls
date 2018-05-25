#ifndef THWAITES_CONTROLS_JOYSTICK_H
#define THWAITES_CONTROLS_JOYSTICK_H

#include "Control.h"

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
    Joystick(byte pin_x, byte pin_y, int threshold = 150) : 
      _pin_x(pin_x), _pin_y(pin_y), _threshold(threshold) {}

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

    virtual void begin();
    virtual boolean read();
  
  private:
    byte _pin_x;
    byte _pin_y;
    int _threshold;
    int _x, _y, _centre_x, _centre_y;
    byte _last_flags = 0, _flags = 0;

};

#endif