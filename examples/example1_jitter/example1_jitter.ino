#include <Joystick.h>
#include <Potentiometer.h>

Potentiometer pot1 = Potentiometer(A0);

void setup() {

  Serial.begin(9600);

  //setup the potentiometer with no smoothing or delay
  pot1.begin();
  pot1.setSmoothingFactor(0);
  pot1.setReadDelay(0);

}

void loop() {
  
  //read the pot values
  //make sure to call this once every loop
  pot1.read();

  //now we are ready to read the values!
  if (pot1.changed()) {

    //you should see this jittering - flickering back and forth 
    //occasionally even if you don't touch the potentiometer
    Serial.println(pot1.getValue());

  }

}