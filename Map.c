#include "stdafx.h"
#include "Map.h"
#include <string.h>
#define ASSERT(X)
#include <stdlib.h>



void KeyValue_Delete(MapItem* p)
{
  if (p)
  {
    String_Destroy(&p->Key);
    free(p);
  }
}

static MapItem* Map_GetAssocAt(
  Map* pMap,
  const char* Key,
  unsigned int* nHashBucket,
  unsigned int* HashValue);


inline unsigned int String_HashKey(const char*  Key)
{
  // hash key to unsigned int value by pseudorandomizing transform
  // (algorithm copied from STL string hash in xfunctional)
  unsigned int uHashVal = 2166136261U;
  unsigned int uFirst = 0;
  unsigned int uLast = (unsigned int)strlen(Key);
  unsigned int uStride = 1 + uLast / 10;

  for (; uFirst < uLast; uFirst += uStride)
  {
    uHashVal = 16777619U * uHashVal ^ (unsigned int)Key[uFirst];
  }

  return (uHashVal);
}


void Map_RemoveAll(Map* pMap)
{
  if (pMap->pHashTable != NULL)
  {
    for (unsigned int nHash = 0;
         nHash < pMap->nHashTableSize;
         nHash++)
    {
      MapItem* pKeyValue =
        pMap->pHashTable[nHash];

      while (pKeyValue != NULL)
      {
        MapItem* pKeyValueCurrent = pKeyValue;
        pKeyValue = pKeyValue->pNext;
        KeyValue_Delete(pKeyValueCurrent);
      }
    }

    free(pMap->pHashTable);
    pMap->pHashTable = NULL;
    pMap->nCount = 0;
  }
}

void Map_Destroy(Map* pMap)
{
  Map_RemoveAll(pMap);
}

static MapItem* Map_GetAssocAt(
  Map* pMap,
  const char* Key,
  unsigned int* nHashBucket,
  unsigned int* HashValue)
{
  if (pMap->pHashTable == NULL)
  {
    *HashValue = 0;
    *nHashBucket = 0;
    return NULL;
  }

  *HashValue = String_HashKey(Key);
  *nHashBucket = *HashValue % pMap->nHashTableSize;

  MapItem* pResult = NULL;

  MapItem* pKeyValue =
    pMap->pHashTable[*nHashBucket];

  for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
  {
    if (pKeyValue->HashValue == *HashValue &&
        strcmp(pKeyValue->Key , Key) == 0)
    {
      pResult = pKeyValue;
      break;
    }
  }

  return pResult;
}

bool Map_Lookup(Map* pMap,
                const char*  Key,
                void** rValue)
{
  bool bResult = false;

  unsigned int nHashBucket, HashValue;
  MapItem* pKeyValue = Map_GetAssocAt(pMap,
                                       Key,
                                       &nHashBucket,
                                       &HashValue);

  if (pKeyValue != NULL)
  {
    *rValue = pKeyValue->pValue;
    bResult = true;
  }

  return bResult;
}

bool Map_LookupKey(Map* pMap,
                   const char*  Key,
                   const char** rKey)
{
  bool bResult = false;

  unsigned int nHashBucket, HashValue;
  MapItem* pKeyValue = Map_GetAssocAt(pMap,
                                       Key,
                                       &nHashBucket,
                                       &HashValue);

  if (pKeyValue != NULL)
  {
    *rKey = pKeyValue->Key;
    bResult = true;
  }

  return bResult;
}

bool Map_RemoveKey(Map* pMap,
                   const char*  Key,
                   void** ppValue)
{
  *ppValue = 0;
  bool bResult = false;

  if (pMap->pHashTable != NULL)
  {
    unsigned int HashValue =
      String_HashKey(Key);

    MapItem** ppKeyValuePrev =
      &pMap->pHashTable[HashValue % pMap->nHashTableSize];

    MapItem* pKeyValue = *ppKeyValuePrev;

    for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
    {
      if ((pKeyValue->HashValue == HashValue) &&
          (strcmp(pKeyValue->Key, Key) == 0))
      {
        // remove from list
        *ppKeyValuePrev = pKeyValue->pNext;
        *ppValue = pKeyValue->pValue;
        KeyValue_Delete(pKeyValue);
        bResult = true;
        break;
      }

      ppKeyValuePrev = &pKeyValue->pNext;
    }
  }

  return bResult;
}

int Map_SetAt(Map* pMap,
              const char* Key,
              void* newValue,
              void** ppPreviousValue)
{
  int result = 0;
  *ppPreviousValue = NULL;

  if (pMap->pHashTable == NULL)
  {
	  if (pMap->nHashTableSize < 1)
	  {
		  pMap->nHashTableSize = 10;
	  }

    MapItem** pHashTable =
      (MapItem**)malloc(sizeof(MapItem*) * pMap->nHashTableSize);

    if (pHashTable != NULL)
    {
      memset(pHashTable, 0, sizeof(MapItem*) * pMap->nHashTableSize);
      pMap->pHashTable = pHashTable;
    }
  }

  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    MapItem* pKeyValue =
      Map_GetAssocAt(pMap,
                     Key,
                     &nHashBucket,
                     &HashValue);

    if (pKeyValue == NULL)
    {
      pKeyValue = (MapItem*)malloc(sizeof(MapItem) * 1);
      pKeyValue->HashValue = HashValue;
      pKeyValue->pValue = newValue;
      String_Init(&pKeyValue->Key, Key);
      pKeyValue->pNext = pMap->pHashTable[nHashBucket];
      pMap->pHashTable[nHashBucket] = pKeyValue;
      pMap->nCount++;
      result = 0;
    }

    else
    {
      result = 1;
      *ppPreviousValue = pKeyValue->pValue;
      pKeyValue->pValue = newValue;
      String_Set(&pKeyValue->Key, Key);
    }
  }

  return result;
}

void Map_Init(Map * p)
{
  Map temp = MAPSTRINGTOPTR_INIT;
  *p = temp;
}

void Map_Swap(Map * pA, Map * pB)
{
  Map temp = *pA;
  *pA = *pB;
  *pB = temp;
}

Map* Map_Create()
{
  Map* p = (Map*)malloc(sizeof(Map));

  if (p != 0)
  {
    Map t = MAPSTRINGTOPTR_INIT;
    *p = t;
  }

  return p;
}

void Map_Delete(Map * p)
{
  if (p != 0)
  {
    Map_Destroy(p);
    free(p);
  }
}
