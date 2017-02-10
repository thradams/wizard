#pragma once

typedef char * String;
#define STRING_INIT 0

int    String_Init(String* pString, const char* source);
void   String_Destroy(String* pString);
void   String_Swap(String* pA, String* pB);
int    String_Set(String *pS1, const char* psz1);

