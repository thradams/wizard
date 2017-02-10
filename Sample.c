// CPP2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include "Array.h"
#include <string.h>
#include <stdlib.h>

#include "Generated.h"
#define ASSERT(x)


typedef struct Token
{
  String Lexeme;
} Token;



int main()
{
  TokenMap tokenMap = TOKENMAP_INIT;
  //TokenArray_Push(&tokens, Token_Create());
  //TokenArray_Destroy(&tokens);
  TokenMap_SetAt(&tokenMap, "a", Token_Create());
  //TokenMap_Lookup(&tokenMap, "a", Token_Create());
  TokenMap_Destroy(&tokenMap);

  TokenArray tokens = TOKENARRAY_INIT;
  TokenArray_Push(&tokens, Token_Create());
  TokenArray_Destroy(&tokens);
  return 0;
}

