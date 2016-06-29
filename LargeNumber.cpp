#include "LargeNumber.h"

void convertIntBitList(unsigned int value, bitLink *first, bitLink *last) {
	bitLink *lastSaved = NULL;
	for (int i = sizeof(int) * 8 - 1; i >= 0 && value > 0; --i) {
		unsigned int test = 1 << i;	//pow(2, i);
		if (value >= test) {
			value -= test;
			if(lastSaved != NULL) {
				lastSaved = lastSaved->previous = new bitLink(1, NULL, lastSaved);
			} else {
				last = lastSaved = new bitLink(1, NULL, NULL);
			}
		} else if (last != NULL) {	//Skipping all the leading zeros
			lastSaved = lastSaved->previous = new bitLink(0, NULL, lastSaved);
		}
	}
	first = lastSaved;
}
void LargeNumber::fromInt(const int value) {
	//Dealing with just postive numbers
	isPostive = value >= 0;
	int v = value * (isPostive ? 1 : -1);
	//Coverting value binary
	convertIntBitList(v, leastSB, leastSB);
}
void LargeNumber::fromLargeNumber(const LargeNumber &other) {
	leastSB = new bitLink(other.leastSB->value, NULL, NULL);

	bitLink *lastSave = leastSB;
	bitLink *toSave = other.leastSB->next;
	while (toSave != NULL) {
		lastSave = lastSave->next = new bitLink(toSave->value, lastSave, NULL);
		toSave = toSave->next;
	}

	leastSB = lastSave;
	isPostive = other.isPostive;
}

LargeNumber::LargeNumber(const int value) {
	fromInt(value);
}
LargeNumber::LargeNumber(const LargeNumber &value) {
	fromLargeNumber(value);
}
LargeNumber::~LargeNumber() {
	bitLink *toDelete = leastSB;
	while (toDelete != NULL) {
		bitLink *next = toDelete->next;
		delete toDelete;
		toDelete = next;
	}

	isPostive = false;
	leastSB = NULL;
	mostSB = NULL;
}
LargeNumber& LargeNumber::operator=(const int other) {
	fromInt(other);
	return *this;
}
LargeNumber& LargeNumber::operator=(const LargeNumber &other) {
	fromLargeNumber(other);
	return *this;
}
/*LargeNumber LargeNumber::operator*(const int right) {

}
LargeNumber LargeNumber::operator*(const LargeNumber &right) {

}

LargeNumber LargeNumber::operator+(const int right) {

}
LargeNumber LargeNumber::operator+(const LargeNumber &right) {

}*/
std::string LargeNumber::toString() const {
	std::string str = "";
	bitLink *toStr = leastSB;
	while (toStr != NULL) {
		str.insert(0, toStr->value ? "1" : "0");
		toStr = toStr->next;
	}
	if (!isPostive) {
		str.append("-");
	}
	if(str == "") {
		str = "NULL";
	}
	return str;
}
