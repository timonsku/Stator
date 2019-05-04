#include <Stator.h>

// you can use this with any type or class f.e. the String class
Stator<int> apples;
Stator<int> bananas;

void setup() {
	Serial.begin(115200);
	// set intial state
	apples.set(18);
	bananas.set(12);
}

void loop() {
	apples.set(32);
	bananas.set(32);
	if(bananas.changed() && apples.changed()){
		// shorthand for comparing current states
		if(bananas == apples){
			Serial.println("bananas and apples changed and they are the same!");
		}
	}
	// change them again
	apples.set(18);
	bananas.set(12);
	delay(2000);

}