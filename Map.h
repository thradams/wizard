
#pragma once
#include "String.h"
#include <stdbool.h>

typedef struct MapItem
{
	struct MapItem* pNext;
	unsigned int HashValue;
	String Key;
	void* pValue;
} MapItem;

typedef struct 
{
	MapItem** pHashTable;
	unsigned int nHashTableSize;
	size_t  nCount;
} Map;


#define MAPSTRINGTOPTR_INIT { NULL, 100, 0 }

int Map_SetAt(Map* pMap,
	const char* Key,
	void* newValue,
	void** ppPreviousValue);


bool Map_Lookup(Map* pMap,
	const char*  Key,
	void** rValue);

bool Map_RemoveKey(Map* pMap,
	const char*  Key,
	void** ppValue);

void Map_Init(Map* p);
void Map_Destroy(Map* p);

Map*  Map_Create();
void Map_Delete(Map * p);

void Map_Swap(Map * pA, Map * pB);
