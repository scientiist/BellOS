#include "string.h"
// API specifications in "string.h"


String::String() {
	this->str = "";
}

String::String(char c) {
	this->str = ""+c;
}

String::String(const char* str) {
	this->str = str;
}

String::String(String& s) {
	this->str = s.toCharArray();
}

int String::length() {
	size_t len = 0;
	while (this->str[len])
		len++;
	return len;
}

const char* String::toCharArray() {
	return this->str;
}