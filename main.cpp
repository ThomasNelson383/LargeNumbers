#include "LargeNumber.h"
#include <iostream>

int main(int argc, char **argv) {
	LargeNumber ln = 2;
	std::cout << ln.toString();

	//unsigned int x = 1;
	//x = x << 31; // use operator<< for left shift
    //std::cout << x; // use operator<< for output

	return 0;
}
