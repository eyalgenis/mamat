#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "DependGraph.h"

typedef struct _DEPEND_GRAPH
{
	PNODE head;

	/* Function Pointers */
//	GET_KEY GetKeyFunc;
	DEL_ELEMENT DelElementFunc;
	COMPARE_KEYS CompareKeysFunc;
	PRINT_ELEMENT PrintElementFunc;
	CLONE CloneFunc;

} DEPEND_GRAPH;


/*
* Private helper functions
*/

static Bool FindNode(PDEPEND_GRAPH pDG, PNODE pNode) /// ????
{
	int i;
	PKEY pElemKey;
		for (i = 0; i < MAX_ELEMENTS; i++)
		{
			pElemKey = pDG->GetKeyFunc(pDG->ArrElements[i]);
			if (pDG->CompareKeysFunc(pKey, pElemKey))
				return i;
		}
	return -1;
}

PNODE FindNode(char* pRecipeName)
{
	Recipe* pSearcher;

	for (pSearcher = pRecipesList; pSearcher != NULL; pSearcher = pSearcher->pNext) // Search if INGREDIENT already exists
	{
		if (strcmp(pSearcher->pRecipeName, pRecipeName) == 0)
			return pSearcher;
	}

	return NULL;
}

/*
* Interface implementation
*/

PDEPEND_GRAPH CreateGRAPH(
	DEL_ELEMENT DelElementFunc,
	COMPARE_KEYS CompareKeysFunc,
	CLONE CloneFunc,
	PRINT_ELEMENT PrintElementFunc)
{
	PDEPEND_GRAPH pDG;

	pDG = (PDEPEND_GRAPH)malloc(sizeof(PDEPEND_GRAPH));

	if (pDG = NULL)
	{
		fprintf(stdout, "DependGraph.c: Failed to allocate memory");
		exit(-1);
	}

	pDG->head = NULL;
	pDG->CompareKeysFunc = CompareKeysFunc;
	pDG->DelElementFunc = DelElementFunc;
	pDG->CloneFunc = CloneFunc;
	pDG->PrintElementFunc = PrintElementFunc;

	return pDG;
}

void DeleteGRAPH(PDEPEND_GRAPH pDG)
{
	if (pDG == NULL)
		return;

	PNODE p = pDG->head;

	if (p == NULL) {
		free(pDG);
		return;
	}

	PNODE pNext = p->nextNode;

	while (pNext != NULL) {
		pDG->DelElementFunc(p->pelem);
		free(p);
		p = pNext;
	}
	
	pDG->DelElementFunc(p->pelem);
	free(p);
	free(pDG);
}

Result AddGRAPH(PDEPEND_GRAPH pDG, PNODE pNode, PNODE pParent)
{
	PNODE pSearch;

	if (pNode == NULL || pDG == NULL)
		return FAILURE;
	
	pSearch = FindNode(pNode);

	if (pSearch != NULL) // node already exist
		return FAILURE;
	
	pSearch = FindNode(pParent);

	if (pSearch == NULL) // parent doesn't exist
		return FAILURE;

	if (pDG->head == NULL && pParent == NULL) { // Create first NODE
		pDG->head = pNode;
		pNode->nextNode = NULL;
		pNode->parentNode = NULL;
		return SUCCESS;
	}

	else {
		PNODE p = pDG->head;
		while (p->nextNode != NULL) {
			p = p->nextNode;
		}
		p->nextNode = pNode;
		pNode->nextNode = NULL;
		pNode->parentNode = pParent;
		return SUCCESS;
	}
}

Result ExecuteGRAPH(PDEPEND_GRAPH pDG, PNODE pNode) {

	if (pNode == NULL || pDG == NULL)
		return FAILURE;

	PNODE p = pNode; // temp get pnode pointer

	while (p->parentNode != NULL) {
		if (p->was_executed == FALSE) {
			printf("Error - Cannot execute:\n");
			printf("%v\n", &(pNode->pelem)); // what type of element?
			printf("The next Prerequisite is not satisfied\n");
			printf("%v\n", &(p->pelem)); // what type of element?

			return FAILURE;
		}
			
		p = p->parentNode;
	}

	pNode->was_executed = TRUE;
	return SUCCESS;

}

void PrintGRAPH(PDEPEND_GRAPH pDG)
{
	PNODE p = pDG->head;

	PStack pStack = StackCreate(pDG->CloneFunc, pDG->PrintElementFunc, pDG->DelElementFunc);

	while (p->nextNode != NULL) {
		// push
		if (StackPush(pStack, p->pelem) == FAILURE)
			return;
		p = p->nextNode;
	}

	void StackPrint(pStack);

}

int NumGRAPH(PDEPEND_GRAPH pDG) {

	if (pDG == NULL)
		return (-1);

	int i=1;
	PNODE p = pDG->head;

	while (p->nextNode != NULL) {
		p = p->nextNode;
		i++;
	}

	return i;

}

void PrintPARENTS(PDEPEND_GRAPH pDG, PNODE pNode) {
	PNODE p = pDG->head;

	PStack pStack = StackCreate(pDG->CloneFunc, pDG->PrintElementFunc, pDG->DelElementFunc);

	while (p->parentNode != NULL) {
		// push
		if (StackPush(pStack, p->pelem) == FAILURE)
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