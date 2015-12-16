#ifndef __STACK__
#define __STACK__
#include "Defines.h"

typedef void* PElement;
typedef struct Stack_* PStack;

/*User Functions*/
typedef PElement (*CLONE_FUNC)(PElement); //User must provide as Stack saves a local copy of the elements
typedef void (*PRINT_FUNC)(PElement); //For the StackPrint function
typedef void (*DEL_FUNC)(PElement); 

/*Interface Functions*/

/*
Function: StackCreate
Arguments: Pointers to user functions
Action: Allocates memory for the Stack and initilize it
Return Value: Pointer to the allocated Stack
*/
PStack  StackCreate(CLONE_FUNC, PRINT_FUNC, DEL_FUNC);
/*
Function: StackPush 
Arguments: Pointer to Stack, Pointer to element to be pushed
Action: Creates a new copy of the element and pushes it to the top of the stack
Return Value: Success or failure
*/
Result  StackPush(PStack,PElement );
/*
Function: StackPrint
Arguments: Pointer to Stack
Action: Prints all of the elements in the stack starting from the top till the bottom
Return Value: None
*/
void  StackPrint(PStack);
/*
Function: StackDestroy
Arguments: Pointer to Stack
Action: Deletes all local elements and free the memory allocated for the stack
Return Value: None
*/
void  StackDestroy(PStack);
/*
Function: StackPop
Arguments: Pointer to Stack
Action: Pop one element from the Stack. It is the user responsibility to free the memorey allocated for the poped element 
Return Value: Pointer to the poped element
*/
PElement StackPop(PStack);

#endif
