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
	LargeNumber(const long long value = 0LL);
	LargeNumber(const unsigned long long value, const bool _isPostive = true);
	LargeNumber(const std::string &value);	//a dec string
	LargeNumber(const LargeNumber &value);	//Copy Contector
	~LargeNumber();

	LargeNumber& operator=(const long long other);
	LargeNumber& operator=(const unsigned long long other);
	LargeNumber& operator=(const LargeNumber &other);

	/*LargeNumber operator*(const int right);
	LargeNumber operator*(const LargeNumber &right);

	LargeNumber operator+(const int right);
	LargeNumber operator+(const LargeNumber &right);*/

	std::string toString(bool isBinary = false) const;	//Output a dec string
private:
	bool isPostive;

	bitLink *leastSB = NULL;
	bitLink *mostSB = NULL;

	void fromInt(const unsigned long long value, const bool _isPostive);
	void fromLargeNumber(const LargeNumber &other);

	std::string toBinaryString() const;
	std::string toDecString() const;
};
