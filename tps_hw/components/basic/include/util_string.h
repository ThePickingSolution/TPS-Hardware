#ifndef _UTIL_STRING_
#define _UTIL_STRING_

#include "datatypes.h"

char* str_part(char* str, char delimiter, int32 index);

void str_part_free(char* pointer);

#endif // _UTIL_STRING_