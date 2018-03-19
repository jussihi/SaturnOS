#include "string.h"

unsigned int strlen(const char* w_istr)
{
	const char* orig = w_istr;
	while(*(w_istr++));
	return (unsigned int)(w_istr - orig - 1);
}