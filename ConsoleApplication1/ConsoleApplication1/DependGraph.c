#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "DependGraph.h"

typedef struct _DEPEND_GRAPH
{
	PNODE head;
	DELETE_ELEMENT DeleteF;
	COMPARE_ELEMENT CompareF;
	PRINT_ELEMENT PrintF;
	CLONE_ELEMENT CloneF;

} DEPEND_GRAPH;

/*
* Private helper functions
*/

/*
* Interface implementation
*/

PDEPEND_GRAPH CreateGRAPH(CLONE_ELEMENT CloneF, DELETE_ELEMENT DeleteF, COMPARE_ELEMENT CompareF, PRINT_ELEMENT PrintF)
{
	PDEPEND_GRAPH pDG;

	pDG = (PDEPEND_GRAPH)malloc(sizeof(DEPEND_GRAPH));

	if (pDG = NULL)
	{
		fprintf(stdout, "DependGraph.c: Failed to allocate memory");
		exit(-1);
	}

	pDG->head = NULL;
	pDG->CompareF = CompareF;
	pDG->DeleteF = DeleteF;
	pDG->CloneF = CloneF;
	pDG->PrintF = PrintF;

	return pDG;
}

void DeleteGRAPH(PDEPEND_GRAPH pDG)
{
	PNODE pNode, pNext;
	
	if (pDG == NULL)
		return;

	pNode = pDG->head;

	if (pNode == NULL) {
		free(pDG);
		return;
	}

	pNext = pNode->nextNode;

	while (pNext != NULL) {
		pDG->DeleteF(pNode->pElem);
		free(pNode);
		pNode = pNext;
	}
	
	pDG->DeleteF(pNode->pElem);
	free(pNode);
	free(pDG);
}

Result AddElement(PDEPEND_GRAPH pDG, PElement pNewElement, PElement pParentElement)
{
	PNODE pNewNode, pParentNode;

	if (pDG == NULL || pNewElement == NULL) // no GRAPH or no ELEMENT to add (parameters check)
		return FAILURE;

	pNewNode = FindNode(pDG, pNewElement);

	if (pNewNode != NULL) // node already exists
		return FAILURE;
	
	pParentNode = FindNode(pDG, pParentElement); // search Parent (lior saved it + flag.. for what ??)

	if (pParentElement != NULL && pParentNode == NULL) // parent element isn't NULL + its node doesn't exist on graph
		return FAILURE;

	pNewNode = (PNODE)malloc(sizeof(NODE)); // ADT creates a node and initialize + copies the element
	if (pNewNode == NULL)
	{
		fprintf(stdout, "DependGraph.c: Failed to allocate memory");
		exit(-1);
	}

	pNewNode->pElem = pDG->CloneF(pNewElement); // copy the element
	pNewNode->parentNode = pParentNode; // link to found (or NULL) 
	pNewNode->nextNode = pDG->head; // add to start of list
	pDG->head = pNewNode;
	pNewNode->was_executed = FALSE;

	return SUCCESS;
}

PNODE FindNode(PDEPEND_GRAPH pDG, PElement pElem)
{
	PNODE pSearch = pDG->head;

	for (pSearch = pDG->head; pSearch != NULL; pSearch = pSearch->nextNode) // Search if NODE (key, elem) already exists
	{
		if (pDG->CompareF(pSearch->pElem, pElem) == EQUAL)
			return pSearch;
	}

	return NULL;
}


Result ExecuteElement(PDEPEND_GRAPH pDG, PElement pElementExec)
{
	PNODE pExecNode;

	if (pDG == NULL || pElementExec == NULL) // parameters check
		return FAILURE;

	pExecNode = FindNode(pDG, pElementExec); // find the node of input element

	if (pExecNode == NULL || pExecNode->was_executed == TRUE)
		return FAILURE;

	while (pExecNode->parentNode != NULL) // look up on graph
	{
		if (pExecNode->parentNode->was_executed == FALSE) // if up node isn't executed...
		{
			printf("Error - Cannot execute :\n");
			pDG->PrintF(pElementExec);
			printf("The next Prerequisite is not satisfied :\n");
			pDG->PrintF(pExecNode->parentNode->pElem);

			return FAILURE;
		}
			
		pExecNode = pExecNode->parentNode;
	}

	if (pExecNode->was_executed == FALSE) // last iteration
	{
		printf("Error - Cannot execute :\n");
		pDG->PrintF(pElementExec);
		printf("The next Prerequisite is not satisfied :\n");
		pDG->PrintF(pExecNode->parentNode->pElem);

		return FAILURE;
	}

	pExecNode->was_executed = TRUE;

	return SUCCESS;
}

void PrintExecElements(PDEPEND_GRAPH pDG)
{
	PNODE pNode;
	PStack pStack;
	Result pushresult;

	if (pDG == NULL)
		return;

	pNode = pDG->head;

	pStack = StackCreate(pDG->CloneF, pDG->PrintF, pDG->DeleteF);

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

int CountElements(PDEPEND_GRAPH pDG)
{
	PNODE pNode;
	int counter = 0;

	if (pDG == NULL)
		return -1;

	pNode = pDG->head;

	while (pNode != NULL)
	{
		counter++;
		pNode = pNode->nextNode;
	}

	return counter;
}

void PrintPrerequisities(PDEPEND_GRAPH pDG, PElement pElem)
{
	PNODE pNode;
	PStack pStack;
	Result pushresult;

	if (pDG == NULL || pElem == NULL)
		return;

	pNode = pDG->head;

	pStack = StackCreate(pDG->CloneF, pDG->PrintF, pDG->DeleteF);

	if (pStack == NULL)
	{
		fprintf(stdout, "DependGraph.c: Failed to allocate memory");
		exit(-1);
	}

	while (p->parentNode != NULL)
	{
		// push
		if (StackPush(pStack, p->pElem) == FAILURE)
			return;
		p = p->parentNode;
	}

	void StackPrint(pStack);

}

Result ResetGRAPH(PDEPEND_GRAPH pDG) {

	PNODE p = pDG->head;

	if (pDG == NULL)
		return FAILURE;

	while (p->nextNode != NULL) {
		p->was_executed = 0;
		p = p->nextNode;
	}

	p->was_executed = 0;

	return SUCCESS;
}

Result RemoveGRAPH(PDEPEND_GRAPH pDG, PNODE pNode) {
	
	if (pNode == NULL || pDG == NULL)
		return FAILURE;

	PNODE p = pDG->head;
	PNODE pSon = NULL;
	PNODE pPrev = NULL;

	while (p->nextNode != NULL && (pSon == NULL || pPrev == NULL)) {

		if (p->parentNode == pNode) // compare keys?
			pSon = p;
		if (p->nextNode == pNode)
			pPrev = p;

		p = p->nextNode;
	}

	pSon->parentNode = pNode->parentNode;
	pPrev->nextNode = pNode->nextNode;

	return SUCCESS;
}