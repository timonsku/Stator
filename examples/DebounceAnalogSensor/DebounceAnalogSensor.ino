#include <Stator.h>

// you can use this with any type or class f.e. the String class
Stator<int> sensor;

void setup() {
  Serial.begin(115200);
  // Set a point where we consider our state to have crossed a threshold from false to true
  sensor.setThreshold(370);
  // Set an error margin, so anything below 362 will be considered below threshold
  // and everything above 378 will be considered above threshold
  // this avoids getting spammed when the sensor reads close to the threshold
  sensor.setErrorMargin(8);
  // set intial state
  sensor = 0;
}

void loop() {
  sensor = analogRead(0);
  // Lets avoid being spammed if the sensor value fluctuates a little
  // we will only be notified of a change when the sensor changed by more than 6
  // since the previous reading. Be cautious if you got a slowly drifiting sensor!
  if(sensor.changedBy(6) && sensor.isAboveThreshold()){
    Serial.print(sensor);
    Serial.println(": Sensor is above threshold");
  }else if(sensor.changedBy(6) && sensor.isBelowThreshold()){
    Serial.print(sensor);
    Serial.println(": Sensor is below threshold");
  }
  
  delay(50);
}
