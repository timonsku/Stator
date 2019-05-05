
Stator
======
A library for keeping track of state changes. Turning your dumb numbers and strings into smart objects that know what was happening to them and when. You can use them just as you are used to with a normal variable but will be provided with some extended functionality.

It's goal is to improve readability of typical constructs used in Arduino sketches and other C++ environments and make a lot of code easier to write.

I got sick of writing the same things over and over again. So I made this library to make my life easier.

While targeted at Arduino, it supports standard C++11. There is no dependency on the Arduino API.
So feel free to use this in f.e. openFrameworks or your stand-alone C++ Raspberry Pi app.




Examples
--------
Lets say you want to measure something with an analog sensor and depending on some threshold you want to decide if something is happening or not happening.
Usually this would involve a fair few tracking variables and a lot of 'if else' statements to be declared which get hard to read very quickly.
Now you can do it like this:

```C++
#include <Stator.h>

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
    Serial.println("Sensor is above threshold");
  }else if(sensor.changedBy(6) && sensor.isBelowThreshold()){
    Serial.println("Sensor is below threshold");
  }
}
```

You are probably also familiar with this structure and if you worked with Arduino for a bit you probably have used it countless times already.
(Skipping the setup() for clarity sake)
```C++
int lastState = 0; 
int state = 0;

void loop() {
	state = getSomeStuff();

	if(state != lastState){
		Serial.println(state);
		digitalWrite(LED_BUILTIN,HIGH);
		lastState = state;
	}
}
```

I got a bit tired of the clutter this adds to even simple code if you have to track more than one state. So lets make it more readable.
This helps especially if you got multiple different things to keep track off. Stator can work with any type, built-in or custom.

With Stator the above code could change to:
```C++
Stator<int> myStuff;

void loop() {
	myStuff = getSomeStuff();

	if(myStuff.changed()){
		Serial.println(myStuff);
		digitalWrite(LED_BUILTIN,HIGH);
	}
}
```
The effect becomes more obvious if you introduce a second state variable
```C++
Stator<int> myStuff;
Stator<int> myOtherStuff;

void loop() {
	myStuff = getSomeStuff();
	myOtherStuff = getSomeOtherStuff();
	
	if(myStuff.changed() && myOtherStuff.changed()){
		Serial.println(myStuff);
		digitalWrite(LED_BUILTIN,HIGH);
	}
}
```
Previously this would have looked like this:
```C++
int lastState = 0; 
int otherLastState = 0;
int state = 0;
int otherState = 0;

void loop() {
	state = getSomeStuff();
	otherState = getSomeOtherStuff();
	
	if((state != lastState) && (otherState != otherLastState)){
		Serial.println(state);
		digitalWrite(LED_BUILTIN,HIGH);
		lastState = state;
		otherLastState = otherState;
	}
}
```
This will get old very quickly if you would introduce a third of forth variable.
Another solution would be a finite state machine but more often than not you really just need something simple like this.

Reference
----------

**For NON arithmetic types (stuff that doesn't support math like C++ Strings).**
T stands for the type or class you are using Stator with.

`T getLast()`
	Returns the value that was previously assigned

`bool changed()`
	Whether the variable has changed since its last assignment

`long msSinceLastAssign()`
	The duration in ms since the last assignment happened


**Additionally for types or classes that support arithmetic (can do math):**

`bool changedBy(T amount)`
	True if latest assignment changed value since the previous assignment by at least the value of `amount`

`bool changedByWithin(T amount, long ms)`
	True when value changed by `amount` within the time frame of `ms`

`bool changedByAfter(T amount, long ms)`
	True when value changed by `amount` and it took at least `ms` since the previous assignment was made

`void setThreshold(T threshold)`
	Set the threshold hold value used to determine if something is above or below the threshold

`void setErrorMargin(T margin)`
	A margin that is added above and below the threshold value. 
	So a threshold of 120 and error margin of 5 would mean that only values
	below 115 and above 125 would be considered to be valid. Anything in between is considered ambiguous.

`bool isAboveThreshold()`
	True when value crossed above threshold plus error margin

`bool isBelowThreshold()`
	True when value crossed below threshold minus error margin

`bool isAmbigiuous()`
	True when value is within error margin
