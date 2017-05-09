#include "string.h"

int strlen(char *w){
    int count=0;
    int i=0;
    while (w[i]!='\0')
    {
        count++;
        i++;
    }
    //cout<<"Length of word is:"<<count<<"\n";
    return count;

}

void reverse(char* s) {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

char* itoa(int n) {
	char s[512];
    int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
	 return s;
 }

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

String::String(int i) {
	this->str = itoa(i);
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