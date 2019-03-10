#include <Joystick.h>
#include <Potentiometer.h>

Potentiometer pot1 = Potentiometer(A0);

void setup() {

  Serial.begin(9600);

  //setup the potentiometer with defaults
  pot1.begin();

}

void loop() {
  
  //read the pot values
  //make sure to call this once every loop
  pot1.read();

  //now we are ready to read the values!
  if (pot1.changed()) {

    //jitter should be gone!
    Serial.println(pot1.getValue());

  }

}