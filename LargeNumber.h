#pragma once
#include <string>
#include <iostream>

struct bitLink {
	bitLink *previous = NULL;
	bitLink *next = NULL;
	bool value;	//Or 0

	bitLink(const bool _value = 0, bitLink *_previous = NULL, bitLink *_next = NULL) {
		value = _value;
		previous = _previous;
		next = _next;
	}
};

class LargeNumber {
public:
	LargeNumber(const int value = 0);
	LargeNumber(const LargeNumber &value);	//Copy Contector
	~LargeNumber();

	LargeNumber& operator=(const int other);
	LargeNumber& operator=(const LargeNumber &other);

	/*LargeNumber operator*(const int right);
	LargeNumber operator*(const LargeNumber &right);

	LargeNumber operator+(const int right);
	LargeNumber operator+(const LargeNumber &right);*/

	std::string toString() const;
private:
	bool isPostive;

	bitLink *leastSB = NULL;
	bitLink *mostSB = NULL;

	void fromInt(const int value);
	void fromLargeNumber(const LargeNumber &other);
};
