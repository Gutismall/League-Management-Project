

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

BOOL L_init(LIST* pList)
{
	if (pList == NULL ) 	
		return False;

	pList->head.next = NULL;
	return True;
}


NODE* L_insert(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if ( !pNode ) 
		return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));

	if ( tmp != NULL )  {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}


BOOL L_delete(NODE* pNode)
{
	NODE* tmp;
	if (!pNode)
		return False;
	tmp = pNode->next;
	if(!tmp)
		return False;
	
	pNode->next = tmp->next;
	free(tmp);
	return True;
}


const NODE* L_find(const NODE* pNode,const void* Value,int compare(const void* cmp1,const void* cmp2))
{
	const NODE* tmp = pNode;
	while (tmp != NULL)
	{
		if (compare(Value,tmp->key) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

BOOL L_free(LIST* pList)
{
	NODE *tmp;
	BOOL cont = True;
	if ( !pList ) 
		return False;

	tmp = &(pList->head);
	while (cont)
		cont = L_delete(tmp);
		
	return True;
}

int L_print(const LIST* pList)
{
	NODE	*tmp;
	int		c = 0;

	if ( !pList )
		return False;
    
	tmp = pList->head.next;
	while(tmp != NULL)
	{
        printArena(tmp->key);
		c++;
		tmp = tmp->next;
	}
    return c;
}
