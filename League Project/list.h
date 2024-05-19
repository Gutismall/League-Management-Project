
#ifndef _LIST_
#define _LIST_

#include "def.h"
#include "Arena.h"

typedef struct 
{
	NODE head;
}LIST;


BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

BOOL L_delete(NODE* pNode);					// erase node after *pNode

const NODE* L_find(const NODE* pNode,const
                   void* Value,int compare(const void* cmp1,const void* cmp2));// return a pointer to the node 

BOOL L_free(LIST* pList);					// free list memory

int L_print(const LIST* pList);					// print the list content

#endif
