#ifndef __DEPENDGRAPH__
#define __DEPENDGRAPH__
#include "Defines.h"
#include "Stack.h"

/* User functions types */

typedef PElement(*CLONE_ELEMENT)(PElement);
typedef void(*DELETE_ELEMENT)(PElement);
typedef Bool(*COMPARE_ELEMENTS)(PElement, PElement);
typedef void(*PRINT_ELEMENT)(PElement);

/* Implementation type definitions */

typedef struct DEPEND_GRAPH_ DEPEND_GRAPH;
typedef struct DG_NODE_ NODE;

/* Interface functions */

/* *****************************************************
Function: CreateGraph
Abstract: Creates a new dependancy graph and initializes it
Parameters:
	CloneF - pointer to cloning element function
	DeleteF - pointer to deleting element function
	CompareF - pointer to comparing elements function
	PrintE - pointer to printing element function
Return Value:
	pDG - pointer to the created dependency graph
***************************************************** */
DEPEND_GRAPH* CreateGraph(CLONE_ELEMENT CloneF, DELETE_ELEMENT DeleteF, COMPARE_ELEMENTS CompareF, PRINT_ELEMENT PrintE);

/* *****************************************************
Function: DeleteGraph
Abstract: Deletes a graph and its contents
Parameters:
	pDG - pointer to the desired dependency graph to delete
Return Value: N/a
***************************************************** */
void DeleteGraph(DEPEND_GRAPH* pDG);

/* *****************************************************
Function: AddElement
Abstract: Adds an element to the dependency graph and links it to desired (existing) elements
Parameters:
	pDG - pointer to the dependency graph
	pNewElement - pointer to the element for addition
	pParentElement - pointer to the element which the new one should depend on
Return Value:
	FAILURE if basic requirements aren't met (no graph or element, element already exists or parent doesn't), otherwise SUCCESS
***************************************************** */
Result AddElement(DEPEND_GRAPH* pDG, PElement pNewElement, PElement pParentElement);

/* *****************************************************
Function: ExecuteElement
Abstract: Marks required element as executed
Parameters:
	pDG - pointer to the dependency graph
	pElementExec - pointer to the element for execution
Return Value:
	FAILURE if basic requirements aren't met (no graph or element, element doesn't exist or already executed), otherwise SUCCESS
***************************************************** */
Result ExecuteElement(DEPEND_GRAPH* pDG, PElement pElementExec);

/* *****************************************************
Function: PrintExecElements
Abstract: Prints all of executed elements, by order of chronological addition
Parameters:
	pDG - pointer to the dependency graph
Return Value: N/a
***************************************************** */
void PrintExecElements(DEPEND_GRAPH* pDG);

/* *****************************************************
Function: CountElements
Abstract: Counts the number of elements on the graph
Parameters:
	pDG - pointer to the dependency graph
Return Value: N/a
***************************************************** */
int CountElements(DEPEND_GRAPH* pDG);

/* *****************************************************
Function: PrintPrerequisities
Abstract: Prints all prerequisities' elements of a given element, including it
Parameters:
	pDG - pointer to the dependency graph
	pElem - pointer to the required element
Return Value: 
	counter - num of elements on graph, or -1 if there's no graph
***************************************************** */
void PrintPrerequisities(DEPEND_GRAPH* pDG, PElement pElem);

/* *****************************************************
Function: ResetGraph
Abstract: Marks all elements as not executed
Parameters:
	pDG - pointer to the dependency graph
Return Value:
	FAILURE if graph's existance requirement isn't met, otherwise SUCCESS
***************************************************** */
Result ResetGraph(DEPEND_GRAPH* pDG);

/* *****************************************************
Function: RemoveElement
Abstract: Removes an element's node from the graph, and links its dependencies to its parent
Parameters:
	pDG - pointer to the dependency graph
	pElem - pointer to the element for removal
Return Value:
	FAILURE if basic requirements aren't met (no graph or element, element doesn't exist), otherwise SUCCESS
***************************************************** */
Result RemoveElement(DEPEND_GRAPH* pDG, PElement pElem);

#endif /* __DEPENDGRAPH__ */