#include "LargeNumber.h"

void convertIntBitList(unsigned int value, bitLink *&first, bitLink *&last) {
	bitLink *lastSaved = NULL;
	for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
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
	convertIntBitList(v, leastSB, mostSB);
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
std::string LargeNumber::toBinaryString() const {
	std::string str = isPostive ? "" : "-";
	bitLink *toStr = leastSB;
	while (toStr != NULL) {
		str.insert(1, toStr->value ? "1" : "0");
		toStr = toStr->next;
	}
	if(str == "") {
		str = "NULL";
	}
	return str;
}
int charToNumber(char c) {
	return (int)c - 48; //ascii 48 = 0
}
//Value must be 0-9
char NumberToChar(int value) {
	return (char)(value + 48); //ascii 48 = 0
}
void addValueToString(int value, std::string &string) {
	int i = string.length() - 1;
	while(value) {
		//Hit the top of the numbers
		if(i == -1) {
			while(value > 0) {
				int removeNumber = value % 10;
				char replaceChar = NumberToChar(removeNumber);
				string.insert(0, &replaceChar);
				value -= removeNumber;
				value /= 10;
			}
			return;
		}
		value += charToNumber(string[i]);
		//put it back in to the string
		int removeNumber = value % 10;
		char replaceChar = NumberToChar(removeNumber);
		string.replace(i, 1, &replaceChar);
		value -= removeNumber;
		//Finshed the place, moving up the decimal
		value /= 10;
		--i;
	}
}

void muitply2String(std::string &string) {
	std::string oringalString = string;
	//adding the first number with itself and moving up
	for(int i = string.length() - 1; i >= 0; --i) {
		int place = ((string.length() - i) * 10);
		place = place ? place : 1; //zero's place is really ones
		addValueToString(NumberToChar(oringalString[i]) * place, string);
	}
}
std::string LargeNumber::toDecString() const {
	//http://www.robotroom.com/NumberSystems2.html
	//step - 1 staritng with 0
	std::string str = "0";
	//Step - 2 taking the MSB
	bitLink *toStr = mostSB;
	//Step - 3 stoping
	while (toStr != NULL) {
		//step 2 - adding the MSB if it's a 1
		addValueToString(toStr->value, str);
		//Step 4 - Muiplying by 2
		muitply2String(str);
		//Step - 2 taking the next MSB
		toStr = toStr->previous;
	}

	if(str == "") {
		str = "NULL";
	}
	return str;
}
std::string LargeNumber::toString(bool isBinary) const {
	if(isBinary) {
		return toBinaryString();
	} else {
		return toDecString();
	}
}
