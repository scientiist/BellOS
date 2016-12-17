#include "string.h"
// API specifications in "string.h"
size_t String::GetLength(const char* string) {
	size_t len = 0;
	while (string[len])
		len++;
	return len;
}

int String::GetChar(const char* string, char findme) {

	size_t strLength = this->GetLength(string);

	for (int i = 0; i < strLength; i++) {

	}
	return false;
}



bool String::GetEquals(const char* string1, const char* string2) {

	size_t str1Length = this->GetLength(string1);
	size_t str2Length = this->GetLength(string2);

	// if string2 is bigger than string1 or they are the same
	for(int i = 0; i < str1Length; i++) {
       	if(string1[i] != string2[i]) {
           	return false;
       	}
    }
    return true;
}

char* String::Append(const char* string1, const char* string2) {

}

char String::Upper(char c) {
	if (c >= 'a' && c <= 'z') {
		return c-32;
	}
	return c;
}

char String::Lower(char c) {
	if (c >= 'a' && c <= 'z') {
		return c+32;
	}
	return c;
}

char* String::Upper(const char* string) {

	size_t stringLength = this->GetLength(string);

	static char* retString;

	for (int i = 0;i<=stringLength;i++) {
		retString[i] = this->Upper(string[i]);
	}



	return retString;
}

char* String::Lower(const char* string) {
	size_t stringLength = this->GetLength(string);

	static char* retString;

	for (int i = 0;i<=stringLength;i++) {
		retString[i] = this->Lower(string[i]);
	}


	return retString;

}