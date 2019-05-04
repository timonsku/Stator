#include "src/Stator.h"
#include <iostream>

// This is an example for use outside of Arduino. It uses std::chrono in the background instead of milis()
// So be sure to compile this with atleast C++11

Stator<int> myState;

using namespace std;

int main(int argc, char const *argv[])
{
	myState = 345;
	cout << myState;
	cout << myState.lastChangeWas();
	return 0;
}