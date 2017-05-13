#include "string.h"
//#include "../memory/memory.h"

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

String::String() {
	this->str = "";
}

String::String(char c) {

	this->str = (char*)c;
}

String::String(const char* str) {
	this->str = str;
}

String::String(String& s) {
	this->str = s.toCharArray();
}

String::String(bool b) {
    if (b == true) {
        this->str = "true";
    } else if (b == false) {
        this->str = "false";
    } else {
        this->str = "NULL";
    }
}

String::String(int n) {
    this->str = itoa(n, 10);
}

int String::getLength() {
	size_t len = 0;
	while (this->str[len])
		len++;
	return len;
}

bool String::equals(const char* compare) {
    String me(compare);

    
    return (*this == me);
}

bool String::equals(String& s) {
    return (*this == s);
}


const char* String::toCharArray() {
	return this->str;
}

char String::operator[] (int j)
{
    if (j > this->getLength()) return 0;
    return this->str[j];
}


bool String::operator== (String& lhs) {
    if (lhs.getLength() != this->getLength()) return false;

    unsigned cap = lhs.getLength();
    unsigned int n = 0;
    while ((n < cap) && (lhs.toCharArray()[n] == this->toCharArray()[n])) n++;
    return (n == cap);
}

bool String::operator== (const char* str) {

    String nigga(str);
    return (*this == nigga);
}

String& String::operator+= (String& c) {

    String ret;
        int length = this->getLength();
        int length2 = c.getLength();
        int len = length+length2;
    char str[len];

    for (int j=0; j < length; j++)
        str[j] = this->str[j];

    for (int i=0; i < c.getLength(); i++)
        str[length+i] = c[i];

    length = len;
    ret   = str;
    return ret; 
}
