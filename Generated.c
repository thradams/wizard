#include "stdafx.h"
#include "Generated.h"

#include <stdlib.h>


typedef struct Token
{
  String Lexeme;
} Token;


void Token_Init(Token * p)
{
  Token temp = TOKEN_INIT;
  *p = temp;
}

void Token_Destroy(Token * p)
{
  String_Destroy(&p->Lexeme);
}

void Token_Swap(Token * pA, Token * pB)
{
  Token temp = *pA;
  *pA = *pB;
  *pB = temp;
}

Token* Token_Create()
{
  Token* p = (Token*)malloc(sizeof(Token));

  if (p != 0)
  {
    Token t = TOKEN_INIT;
    *p = t;
  }

  return p;
}

void Token_Delete(Token * p)
{
  if (p != 0)
  {
    Token_Destroy(p);
    free(p);
  }
}



//#include "TokenArray.h"
//#include <stdlib.h>

int TokenArray_Reserve(TokenArray* p, int nelements)
{
  return Array_Reserve((Array*)p, nelements);
}

int TokenArray_Grow(TokenArray* p, size_t nelements)
{
  return Array_Grow((Array*)p, nelements);
}

void TokenArray_Pop(TokenArray* p)
{
  void* pItem =
    Array_Pop((Array*)p);
  Token_Delete((Token*)pItem);
}

Token* TokenArray_Top(TokenArray* p)
{
  return (Token*)Array_Top((Array*)p);
}

int TokenArray_Push(TokenArray* p, Token* pItem)
{
  int r = Array_Push((Array*)p, pItem);

  if (r == -1)
  {
    Token_Delete(pItem);
  }

  return r;
}

void TokenArray_Clear(TokenArray* p)
{
  for (int i = 0; i < p->Size; i++)
  {
    Token_Delete((Token*)p->pItems[i]);
  }

  Array_Clear((Array*)p);
}


void TokenArray_Init(TokenArray* p)
{
  TokenArray temp = TOKENARRAY_INIT;
  *p = temp;
}

TokenArray* TokenArray_Create()
{
  TokenArray* p = (TokenArray*)malloc(sizeof * p);

  if (p)
  {
    TokenArray_Init(p);
  }

  return p;
}

void TokenArray_Destroy(TokenArray* st)
{
  TokenArray_Clear(st);
}

void TokenArray_Swap(TokenArray* p1, TokenArray* p2)
{
  TokenArray temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

void TokenArray_Delete(TokenArray* st)
{
  TokenArray_Destroy(st);
  free(st);
}

Token* TokenArray_Begin(TokenArray* p)
{
  return p->pItems[0];
}

Token* TokenArray_End(TokenArray* p)
{
  return p->pItems[p->Size];
}

void TokenArray_RemoveAt(TokenArray* p, int index)
{
  void *pItem =
    Array_RemoveAt((Array*)p, index);
  Token_Delete((Token*)pItem);
}

int TokenMap_SetAt(TokenMap* pMap,
                   const char* Key,
                   Token* newValue)
{
  void *pPrevious;
  int r = Map_SetAt((Map*)pMap, Key, newValue, &pPrevious);
  Token_Delete((Token*)pPrevious);
  return r;
}

bool TokenMap_Lookup(TokenMap* pMap,
                     const char*  Key,
                     Token** rValue)
{
  return Map_Lookup((Map*)pMap,
                    Key,
                    (void**)rValue);
}

bool TokenMap_RemoveKey(TokenMap* pMap, const char*  Key)
{
  Token *pItem;
  bool r = Map_RemoveKey((Map*)pMap, Key, (void**)&pItem);

  if (r)
  {
    Token_Delete(pItem);
  }

  return r;
}

void TokenMap_Init(TokenMap* p)
{
  TokenMap t = TOKEN_INIT;
  *p = t;
}

void TokenMap_Destroy(TokenMap* p)
{
  Map_Destroy((Map*)p);
}

TokenMap* TokenMap_Create()
{
  TokenMap* p = (TokenMap*)malloc(sizeof * p);

  if (p)
  {
    TokenMap_Init(p);
  }

  return p;
}

void TokenMap_Delete(TokenMap * p)
{
  if (p != NULL)
  {
    TokenMap_Destroy(p);
    free(p);
  }
}

void TokenMap_Swap(TokenMap * pA, TokenMap * pB)
{
  TokenMap t = TOKENMAP_INIT;
  *pA = *pB;
  *pB = t;
}

