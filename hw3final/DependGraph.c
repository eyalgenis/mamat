#include <stdio.h>
#include <stdlib.h>
#include "DependGraph.h"
#include "Stack.h"

struct DEPEND_GRAPH_
{
	NODE* head;
	DELETE_ELEMENT DeleteF;
	COMPARE_ELEMENTS CompareF;
	PRINT_ELEMENT PrintE;
	CLONE_ELEMENT CloneF;
};

struct DG_NODE_
{
	PElement pElem;
	NODE* parentNode;
	NODE* nextNode;
	Bool was_executed;
};

/*
* Private helper functions
*/

/* *****************************************************
Function: FindNode
Abstract:  Searches for the node of a given element in a given graph
Parameters:
	pDG - pointer to the dependency graph
	pElem - pointer to the element for finding its node
Return Value:
	pSearch - pointer to the requested node of element, or NULL if it's not on the dependency graph
***************************************************** */
static NODE* FindNode(DEPEND_GRAPH* pDG, PElement pElem)
{
	NODE* pSearch = pDG->head;

	for (pSearch = pDG->head; pSearch != NULL; pSearch = pSearch->nextNode) // Search if node already exists
	{
		if (pDG->CompareF(pSearch->pElem, pElem) == EQUAL)
			return pSearch;
	}

	return NULL;
}

/*
* Interface implementation
*/

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
DEPEND_GRAPH* CreateGraph(CLONE_ELEMENT CloneF, DELETE_ELEMENT DeleteF, COMPARE_ELEMENTS CompareF, PRINT_ELEMENT PrintE)
{
	DEPEND_GRAPH* pDG;

	pDG = (DEPEND_GRAPH*)malloc(sizeof(DEPEND_GRAPH));

	if (pDG == NULL)
	{
		fprintf(stdout, "DependGraph.c: Failed to allocate memory");
		exit(-1);
	}
	// graph initialization

	pDG->head = NULL;
	pDG->CompareF = CompareF;
	pDG->DeleteF = DeleteF;
	pDG->CloneF = CloneF;
	pDG->PrintE = PrintE;

	return pDG;
}

/* *****************************************************
Function: DeleteGraph
Abstract: Deletes a graph and its contents
Parameters:
	pDG - pointer to the desired dependency graph to delete
Return Value: N/a
***************************************************** */
void DeleteGraph(DEPEND_GRAPH* pDG)
{
	NODE *pNode, *pNext;
	
	if (pDG == NULL) // no graph (parameters check)
		return;

	pNode = pDG->head;

	if (pNode == NULL) // it's an empty graph
	{
		free(pDG);
		return;
	}

	pNext = pNode->nextNode;

	while (pNext != NULL) // delete all contents of graph
	{
		pDG->DeleteF(pNode->pElem);
		free(pNode);
		pNode = pNext;
		pNext = pNext->nextNode;
	}
	
	pDG->DeleteF(pNode->pElem);
	free(pNode);

	free(pDG); // delete graph

	return;
}

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
Result AddElement(DEPEND_GRAPH* pDG, PElement pNewElement, PElement pParentElement)
{
	NODE *pNewNode, *pParentNode;

	if (pDG == NULL || pNewElement == NULL) // no graph or no element to add (parameters check)
		return FAILURE;

	pNewNode = FindNode(pDG, pNewElement); // search if the new element already exists on graph

	if (pNewNode != NULL)
		return FAILURE;
	
	pParentNode = FindNode(pDG, pParentElement); // search parent element's node

	if (pParentElement != NULL && pParentNode == NULL) // parent element isn't NULL + its node doesn't exist on graph
		return FAILURE;

	pNewNode = (NODE*)malloc(sizeof(NODE)); // ADT creates a node and initializes + copies the element
	if (pNewNode == NULL)
	{
		fprintf(stdout, "DependGraph.c: Failed to allocate memory");
		exit(-1);
	}
	// new element's node initialization
	pNewNode->pElem = pDG->CloneF(pNewElement); // copy the element
	pNewNode->parentNode = pParentNode; // link to found parent (or NULL)
	pNewNode->nextNode = pDG->head;
	pDG->head = pNewNode;
	pNewNode->was_executed = FALSE;

	return SUCCESS;
}

/* *****************************************************
Function: ExecuteElement
Abstract: Marks required element as executed 
Parameters:
	pDG - pointer to the dependency graph
	pElementExec - pointer to the element for execution
Return Value:
	FAILURE if basic requirements aren't met (no graph or element, element doesn't exist or already executed), otherwise SUCCESS
***************************************************** */
Result ExecuteElement(DEPEND_GRAPH* pDG, PElement pElementExec)
{
	NODE *pExecNode, *pTmpNode;

	if (pDG == NULL || pElementExec == NULL) // no graph or no element to execute (parameters check)
		return FAILURE;

	pExecNode = FindNode(pDG, pElementExec); // find the node of element for execution

	if (pExecNode == NULL || pExecNode->was_executed == TRUE) // didn't find the element or it's already executed
		return FAILURE;

	pTmpNode = pExecNode->parentNode; // go up on graph, starting from parent

	while (pTmpNode != NULL)
	{
		if (pTmpNode->was_executed == FALSE) // if parent element isn't executed, the required element can't be executed too
		{
			printf("Error - Cannot execute:\n");
			pDG->PrintE(pExecNode->pElem);
			printf("\n");
			printf("The next Prerequisite is not satisfied:\n");
			pDG->PrintE(pTmpNode->pElem);
			printf("\n");

			return FAILURE;
		}
			
		pTmpNode = pTmpNode->parentNode;
	}

	pExecNode->was_executed = TRUE;

	return SUCCESS;
}

/* *****************************************************
Function: PrintExecElements
Abstract: Prints all of executed elements, by order of chronological addition
Parameters: 
	pDG - pointer to the dependency graph
Return Value: N/a
***************************************************** */
void PrintExecElements(DEPEND_GRAPH* pDG)
{
	NODE* pNode;
	PStack pStack;
	Result pushresult;

	if (pDG == NULL) // no graph
		return;

	pNode = pDG->head;

	pStack = StackCreate(pDG->CloneF, pDG->PrintE, pDG->DeleteF);

	if (pStack == NULL)
	{
		fprintf(stdout, "DependGraph.c: Failed to allocate memory");
		exit(-1);
	}

	while (pNode != NULL) // go over mekusheret
	{
		if (pNode->was_executed == TRUE)
		{
			pushresult = StackPush(pStack, pNode->pElem);

			if (pushresult == FAILURE)
			{
				fprintf(stdout, "DependGraph.c: Failed to allocate memory");
				exit(-1);
			}
		}
		pNode = pNode->nextNode;
	}

	StackPrint(pStack);
	StackDestroy(pStack);

	return;
}

/* *****************************************************
Function: CountElements
Abstract: Counts the number of elements on the graph
Parameters:
	pDG - pointer to the dependency graph
Return Value: 
	counter - num of elements on graph, or -1 if there's no graph
***************************************************** */
int CountElements(DEPEND_GRAPH* pDG)
{
	NODE* pNode;
	int counter = 0;

	if (pDG == NULL) // no graph
		return -1;

	pNode = pDG->head;

	while (pNode != NULL)
	{
		counter++;
		pNode = pNode->nextNode;
	}

	return counter;
}

/* *****************************************************
Function: PrintPrerequisities
Abstract: Prints all prerequisities' elements of a given element, including it
Parameters:
	pDG - pointer to the dependency graph
	pElem - pointer to the required element
Return Value: N/a
***************************************************** */
void PrintPrerequisities(DEPEND_GRAPH* pDG, PElement pElem)
{
	NODE* pNode;
	PStack pStack;
	Result pushresult;
	int counter, i;
	PElement popElem;

	if (pDG == NULL || pElem == NULL) // no graph or element
		return;

	pNode = FindNode(pDG, pElem); // find required element's node

	if (pNode == NULL) // didn't find it
		return;

	pStack = StackCreate(pDG->CloneF, pDG->PrintE, pDG->DeleteF);

	if (pStack == NULL)
	{
		fprintf(stdout, "DependGraph.c: Failed to allocate memory");
		exit(-1);
	}

	counter = 0;

	while (pNode != NULL)
	{
		pushresult = StackPush(pStack, pNode->pElem);

		if (pushresult == FAILURE)
		{
			fprintf(stdout, "DependGraph.c: Failed to allocate memory");
			exit(-1);
		}

		counter++;
		pNode = pNode->parentNode;
	}

	for (i = 0; i < counter; i++)
	{
		popElem = StackPop(pStack);
		pDG->PrintE(popElem);
		pDG->DeleteF(popElem);
		printf("\n\n");
	}

	StackDestroy(pStack);

	return;
}

/* *****************************************************
Function: ResetGraph
Abstract: Marks all elements as not executed
Parameters:
	pDG - pointer to the dependency graph
Return Value:
	FAILURE if graph's existance requirement isn't met, otherwise SUCCESS
***************************************************** */
Result ResetGraph(DEPEND_GRAPH* pDG)
{
	NODE* pNode;

	if (pDG == NULL) // no graph
		return FAILURE;

	pNode = pDG->head;

	while (pNode != NULL)
	{
		pNode->was_executed = FALSE;
		pNode = pNode->nextNode;
	}

	return SUCCESS;
}

/* *****************************************************
Function: RemoveElement
Abstract: Removes an element's node from the graph, and links its dependencies to its parent
Parameters:
	pDG - pointer to the dependency graph
	pElem - pointer to the element for removal
Return Value:
	FAILURE if basic requirements aren't met (no graph or element, element doesn't exist), otherwise SUCCESS
***************************************************** */
Result RemoveElement(DEPEND_GRAPH* pDG, PElement pElem)
{
	NODE *pCurr, *pPrev, *pSon;

	if (pDG == NULL || pElem == NULL) // no graph or element to remove (parameters check)
		return FAILURE;

	pCurr = FindNode(pDG, pElem); // find element's node and save it

	if (pCurr == NULL) // didn't find it (or empty graph)
		return FAILURE;

	if (CountElements(pDG) == 1) // found it and there's only one node => it's the only one on graph
	{
		pDG->DeleteF(pCurr->pElem); // remove Element
		free(pCurr); //free Node

		pDG->head = NULL; // now an empty list

		return SUCCESS;
	}

	pPrev = pDG->head;
	pSon = pDG->head;

	while (pPrev->nextNode != pCurr) // save previous node
		pPrev = pPrev->nextNode;

	while (pSon != pCurr) // find all dependencies
	{
		if (pSon->parentNode == pCurr)
		{
			pSon->parentNode = pCurr->parentNode; // link every dependent node to current's parent
		}

		pSon = pSon->nextNode;
	}

	pPrev->nextNode = pCurr->nextNode;

	pDG->DeleteF(pCurr->pElem); // remove element
	free(pCurr); // remove node

	return SUCCESS;
}