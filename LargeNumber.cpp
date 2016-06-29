#include "LargeNumber.h"

void convertIntBitList(unsigned long long value, bitLink *&first, bitLink *&last) {
	bitLink *lastSaved = NULL;
	for (int i = sizeof(unsigned long long) * 8 - 1; i >= 0; --i) {
		unsigned long long test = 1ULL << i;	//pow(2, i);
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
void LargeNumber::fromInt(const unsigned long long value,  const bool _isPostive) {
	//Dealing with just postive numbers
	isPostive = _isPostive;
	//Coverting value binary
	convertIntBitList(value, leastSB, mostSB);
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

LargeNumber::LargeNumber(const long long value) {
	unsigned long long posValue = value;
	if(value < 0) {
		posValue *= -1;
	}
	fromInt(posValue, value > 0);
}
LargeNumber::LargeNumber(const unsigned long long value, const bool _isPostive) {
	fromInt(value, _isPostive);
}
LargeNumber::LargeNumber(const LargeNumber &value) {
	fromLargeNumber(value);
}
LargeNumber::LargeNumber(const std::string &value) {

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

LargeNumber& LargeNumber::operator=(const long long other) {
	unsigned long long posValue = other;
	if(other < 0) {
		posValue *= -1;
	}
	fromInt(posValue, other > 0);
	return *this;
}
LargeNumber& LargeNumber::operator=(const unsigned long long other) {
	fromInt(other, true);
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
std::string LargeNumber::toBinaryString() const {
	if(leastSB == NULL) {
		return "NULL";
	}
	std::string str = "";
	bitLink *toStr = leastSB;
	while (toStr != NULL) {
		str.insert(0, toStr->value ? "1" : "0");
		toStr = toStr->next;
	}
	return str;
}
int charToNumber(const char c) {
	//Must be a Number between 0-9
	if(c < 48 || c > 57) {
		return -1;
	}
	return (int)c - 48; //ascii 48f  = 0
}
char NumberToChar(const int value) {
	//Value must be 0-9
	if(value < 0 || value > 9) {
		return 'E';
	}
	return (char)(value + 48); //ascii 48 = 0
}
void addValueToString(int value, int place, std::string &string) {
	int i = string.length() - 1 - place;
	while(value) {
		//Hit the top of the numbers
		if(i == -1) {
			while(value > 0) {
				int adding = value % 10;
				char addingChar = NumberToChar(adding);
				string = addingChar + string;
				value -= adding;
				value /= 10;
			}
			return;
		}
		value += charToNumber(string[i]);
		//put it back in to the string
		int removeNumber = value % 10;
		string[i] = NumberToChar(removeNumber);
		value -= removeNumber;
		//Finshed the place, moving up the decimal
		value /= 10;
		--i;
	}
}
void muitply2String(std::string &string) {
	const std::string oringalString(string);
	//adding the first number with itself and moving up
	for(int i = oringalString.length() - 1; i >= 0; --i) {
		//Power of 10
		int place = ((oringalString.length() - 1)- i);
		addValueToString(charToNumber(oringalString[i]), place, string);
	}
}
std::string LargeNumber::toDecString() const {
	if(mostSB == NULL) {
		return "NULL";
	}
	//http://www.robotroom.com/NumberSystems2.html
	//step - 1 staritng with 0
	std::string str = "0";
	//Step - 2.1 taking the MSB
	bitLink *toStr = mostSB;
	//Step - 3 stoping
	while (toStr != NULL) {
		//Step 4 - Muiplying by 2
		muitply2String(str);
		//step 2.2 - adding the MSB if it's a 1
		addValueToString(toStr->value, 0, str);
		//Step - 2.1 taking the next MSB
		toStr = toStr->previous;
	}
	return str;
}
std::string LargeNumber::toString(bool isBinary) const {
	std::string s;
	if(isBinary) {
		s = toBinaryString();
	} else {
		s = toDecString();
	}
	if(!isPostive) {
		s.insert(0, "-");
	}
	return s;
}
