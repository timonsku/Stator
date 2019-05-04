#ifndef STATOR_H
#define STATOR_H

#include <type_traits>

#ifdef ARDUINO
	#include "Arduino.h"
	#define MILLIS millis
#else
	#include <chrono>
	#define MILLIS std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count
#endif

template <class T, typename = void>
class Stator {
public:
  T getLast(){
    return _lastState;
  }

  bool changed(){
    if(_state != _lastState){
      return true;
    }else{
      return false;
    }
  }

  bool operator==(Stator& t) {
      return (_state == t);
  }

  void operator = (T state) { 
    _lastState = _state;
    _state = state;
  }

  long msSinceLastAssign(){
    return MILLIS()-_msLastAssign;
  }

  operator T() { return _state; }
private:
  T _state;
  T _lastState;
  long _msLastAssign = 0;
};



template <typename T>
class Stator <T, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
public:
  T getLast(){
    return _lastState;
  }

  bool changed(){
    if(_state != _lastState){
      return true;
    }else{
      return false;
    }
  }

  bool changedBy(T amount){
    if(abs(abs(_state)-abs(_lastState)) >= amount){
      return true;
    }else{
      return false;
    }
  }

  bool changedByWithin(T amount, long ms){
    if((abs(abs(_state)-abs(_lastState)) >= amount) && msSinceLastAssign() < ms){
      return true;
    }else{
      return false;
    }
  }

  bool changedByAfter(T amount, long ms){
    if((abs(abs(_state)-abs(_lastState)) >= amount) && msSinceLastAssign() > ms){
      return true;
    }else{
      return false;
    }
  }

  void setThreshold(T threshold){
  	_threshold = threshold;
  }

  void setErrorMargin(T margin){
  	_margin = margin;
  }

  bool isAboveThreshold(){
  	if(_state > _threshold+_margin){
    	return true;
  	}else{
  		return false;
  	}
  }

  bool isBelowThreshold(){
    if(_state < _threshold-_margin){
    	return true;
  	}else{
  		return false;
  	}
  }

  bool isAmbigiuous(){
    return !isBelowThreshold() && !isAboveThreshold();
  }

  long msSinceLastAssign(){
    return MILLIS()-_msLastAssign;
  }

  bool operator==(Stator& t) {
    return (_state == t);
  }

  void operator = (T state) { 
    _lastState = _state;
    _state = state;
    _msLastAssign = MILLIS();
    
  }

  operator T() { return _state; }

private:
  T _state;
  T _lastState;
  T _threshold = 0;
  T _margin = 0;
  long _msLastAssign = 0;
};



#endif // STATOR_H
