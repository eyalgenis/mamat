#ifndef __DEPENDGRAPH__
#define __DEPENDGRAPH__
#include "Defines.h"
#include "Stack.h"

/* Some necessary type definitions */
typedef struct _DEPEND_GRAPH* PDEPEND_GRAPH;
typedef struct DependGraphNode_* PNODE;
typedef void* PElement;

typedef struct DependGraphNode_ {
	PElement pelem; // element of user
	PNODE nextNode; // mekusheret
	PNODE parentNode; // graphic
	Bool was_executed;
} NODE;

/* Function types */
typedef void(*DELETE_ELEMENT)(PElement);
typedef Bool(*COMPARE_ELEMENT)(PElement, PElement);
typedef void(*PRINT_ELEMENT)(PElement);
typedef void(*CLONE_ELEMENT)(PElement);

/* Interface functions */
PDEPEND_GRAPH CreateGRAPH(CLONE_ELEMENT, DELETE_ELEMENT, COMPARE_ELEMENT, PRINT_ELEMENT);

Result AddGRAPH(PDEPEND_GRAPH, PElement, PNODE);

Result ExecuteGRAPH(PDEPEND_GRAPH, PNODE);
PElement GetGRAPH(PDEPEND_GRAPH, PKEY);
Bool RemoveGRAPH(PDEPEND_GRAPH, PKEY);
void PrintGRAPH(PDEPEND_GRAPH);
void DeleteGRAPH(PDEPEND_GRAPH);

#endif __DEPENDGRAPH__
