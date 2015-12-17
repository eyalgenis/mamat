#ifndef __DEPENDGRAPH__
#define __DEPENDGRAPH__
#include "Defines.h"
#include "Stack.h"

/* Some necessary type definitions */
typedef struct _DEPEND_GRAPH* PDEPEND_GRAPH;
typedef void* PKEY; /* Notice we now use a pointer to a key */
typedef void* PElement;typedef struct DependGraphNode_* PNODE;


typedef struct DependGraphNode_ {
	PElement pelem;
	PNODE nextNode;
	PNODE parentNode;
	Bool was_executed;
} NODE;

/* Function types */
typedef PKEY(*GET_KEY)(PElement);
typedef void(*DEL_ELEMENT)(PElement);
typedef Bool(*COMPARE_KEYS)(PKEY, PKEY);
typedef void(*PRINT_ELEMENT)(PElement);
typedef void(*CLONE)(PElement);

/* Interface functions */
PDEPEND_GRAPH CreateGRAPH(GET_KEY, DEL_ELEMENT, COMPARE_KEYS, PRINT_ELEMENT);

Result AddGRAPH(PDEPEND_GRAPH, PElement, PNODE);

Result ExecuteGRAPH(PDEPEND_GRAPH, PNODE);
PElement GetGRAPH(PDEPEND_GRAPH, PKEY);
Bool RemoveGRAPH(PDEPEND_GRAPH, PKEY);
void PrintGRAPH(PDEPEND_GRAPH);
void DeleteGRAPH(PDEPEND_GRAPH);

#endif __DEPENDGRAPH__
