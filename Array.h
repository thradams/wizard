#pragma once


typedef struct
{
	void** pItems;
	int size;
	int capacity;
} Array;

#define ARRAY_INIT {0, 0, 0}

int Array_Reserve(Array* p, int nelements);
int Array_Grow(Array* p, int nelements);
void* Array_Pop(Array* p);
void* Array_Top(Array* p);
int   Array_Push(Array* p, void* pItem);
void  Array_Clear(Array* p);
void  Array_Init(Array* p);
Array* Array_Create();
void Array_Destroy(Array* st);
void Array_Delete(Array* st);
void Array_Swap(Array* p1, Array* p2);
void* Array_RemoveAt(Array* p, int index);
