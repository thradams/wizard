#include "stdafx.h"
#include <stdlib.h>
#include "Array.h"
#define ASSERT(X)

int Array_Reserve(Array* p, int nelements)
{
	int result = -1;
	if (nelements > p->capacity)
	{
		void** pnew = p->pItems;
		pnew = (void**)realloc(pnew, nelements * sizeof(void*));
		if (pnew)
		{
			p->pItems = pnew;
			p->capacity = nelements;
			result = nelements;
		}
	}
	return result;
}


int Array_Grow(Array* p, int nelements)
{
	int result = -1;
	if (nelements > p->capacity)
	{
		int new_nelements = p->capacity + p->capacity / 2;
		if (new_nelements < nelements)
		{
			new_nelements = nelements;
		}
		result = Array_Reserve(p, new_nelements);
	}
	return result;
}

void* Array_Pop(Array* p)
{
	ASSERT(p->size > 0);

	void* pItem = p->pItems[p->size - 1];
	p->pItems[p->size - 1] = NULL;
	p->size--;
	return pItem;
}

void* Array_Top(Array* p)
{
	ASSERT(p->size > 0);
	return p->pItems[p->size - 1];
}

int Array_Push(Array* p, void* pItem)
{
	int result = Array_Grow(p, p->size + 1);
	if (result >= 0)
	{
		p->pItems[p->size] = pItem;
		p->size++;
	}
	return result;
}

void Array_Clear(Array* p)
{
	for (int i = 0; i < p->size; i++)
	{
		//Token_Delete(p[i]->pItems[i]);
	}

	free(p->pItems);
	p->pItems = NULL;
	p->size = 0;
	p->capacity = 0;
}


void Array_Init(Array* p)
{
	Array temp = ARRAY_INIT;
	*p = temp;
}

Array* Array_Create()
{
	Array* p = (Array*)malloc(sizeof * p);
	if (p)
	{
		Array_Init(p);
	}
	return p;
}

void Array_Destroy(Array* st)
{
	Array_Clear(st);
}

void Array_Swap(Array* p1, Array* p2)
{
	Array temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void Array_Delete(Array* st)
{
	Array_Destroy(st);
	free(st);
}

void* Array_Begin(Array* p)
{
	return p->pItems[0];
}

void* Array_End(Array* p)
{
	return p->pItems[p->size];
}

void* Array_RemoveAt(Array* p, int index)
{
	if (index != p->size - 1)
	{
		void* t = p->pItems[index];
		p->pItems[index] = p->pItems[p->size - 1];
		p->pItems[p->size - 1] = t;		
	}

	return Array_Pop(p);
}





