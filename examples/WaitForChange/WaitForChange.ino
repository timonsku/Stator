#include <Stator.h>

// you can use this with any type or class f.e. the String class
Stator<int> sensor;

void setup() {
  Serial.begin(115200);
  // Set a point where we consider our state to
  // have crossed a threshold from false to true
  sensor.setThreshold(370);
  // Set an error margin, so anything below 112
  // will be considered below threshold
  // and everything above 128 will be considered
  // above threshold. This avoids getting spammed
  // when the sensor reads close to the threshold
  sensor.setErrorMargin(8);
  // set intial state
  sensor = 0;
}

void loop() {
  sensor = analogRead(0);
  // Only notify us when the value changed rapidly within 1ms by more than 20
  if(sensor.changedByWithin(20,1) && sensor.isAboveThreshold()){
    Serial.print(sensor);
    Serial.println(": Sensor is above threshold");
  }

}