#include <Stator.h>

// you can use this with any type or class f.e. the String class
Stator<int> myState;

void setup() {
	Serial.begin(115200);
	// set intial state
	myState = 53;
}

void loop() {
	myState = 53;
	// changed() will return false because the previous state was also 53
	if (!myState.changed()){
		Serial.print("myState has not changed");
	}
	delay(1000);
	myState = 40;
	// changed() will return true as the last state was not 40
	if (myState.changed()){
		Serial.print("myState changed to ");
		Serial.println(myState.get());
	}
	myState = 53;
	delay(2000);
}