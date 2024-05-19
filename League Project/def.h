
#ifndef _DEF_
#define _DEF_

#define		EMPTY	0x7FFFFFFF
#include "Arena.h"

typedef Arena* DATA;
typedef enum {False, True} BOOL;


typedef struct node 
{
	DATA			key;
	struct node*	next;
}NODE;

#endif
