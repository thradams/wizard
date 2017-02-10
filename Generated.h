#pragma once
#include "Map.h"
#include "Array.h"
#include "String.h"


typedef struct Token Token;

#define TOKEN_INIT { STRING_INIT } //TODO

void Token_Init(Token* p);
void Token_Destroy(Token* p);

Token*  Token_Create();
void Token_Delete(Token * p);
void Token_Swap(Token * pA, Token * pB);

typedef struct
{
  Token** pItems;
  int Size;
  int Capacity;
} TokenArray;

#define TOKENARRAY_INIT {0, 0, 0}

int      TokenArray_Reserve(TokenArray* p, int nelements);
int      TokenArray_Grow(TokenArray* p, size_t nelements);
void     TokenArray_Pop(TokenArray* p);
Token*      TokenArray_Top(TokenArray* p);
int      TokenArray_Push(TokenArray* p, Token* pItem);
void     TokenArray_Clear(TokenArray* p);
void     TokenArray_Init(TokenArray* p);
TokenArray* TokenArray_Create();
void     TokenArray_Destroy(TokenArray* st);
void     TokenArray_Delete(TokenArray* st);
void     TokenArray_Swap(TokenArray* p1, TokenArray* p2);

Token*      TokenArray_Begin(TokenArray* p);
Token*      TokenArray_End(TokenArray* p);

//


typedef struct TokenMapItem
{
  struct MapItem* pNext;
  unsigned int HashValue;
  String Key;
  Token* pValue;
} TokenMapItem;


typedef struct
{
  TokenMapItem** pHashTable;
  unsigned int nHashTableSize;
  size_t  nCount;
} TokenMap;


#define TOKENMAP_INIT { NULL, 100, 0 }

int TokenMap_SetAt(TokenMap* pMap,
                   const char* Key,
                   Token* newValue);

bool TokenMap_Lookup(TokenMap* pMap,
                     const char*  Key,
                     Token** rValue);

bool TokenMap_RemoveKey(TokenMap* pMap,
                        const char*  Key);

void TokenMap_Init(TokenMap* p);
void TokenMap_Destroy(TokenMap* p);

TokenMap*  TokenMap_Create();
void TokenMap_Delete(TokenMap * p);

void TokenMap_Swap(TokenMap * pA, TokenMap * pB);

