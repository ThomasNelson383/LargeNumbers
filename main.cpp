#include "LargeNumber.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	long long numberToConvert = 6849846827558465456;
	cout << numberToConvert   << endl;
	LargeNumber ln(numberToConvert);
	cout << ln.toString(true) << " is " << ln.toString(true).length() << endl;
	cout << ln.toString() 	  << " is " << ln.toString().length()     << endl;

	//unsigned int x = 1;
	//x = x << 31; // use operator<< for left shift
    //std::cout << x; // use operator<< for output

	return 0;
}
