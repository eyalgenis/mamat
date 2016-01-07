#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DependGraph.h"
#include "Defines.h"
#include "Stack.h"

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

#define MAX_LINE_SIZE 255

typedef struct Course_
{
	char* name;
	char* ID;
	int points;
  
} Course;

// User functions (for ADT usage) decleration //

Course* CloneCourseF(Course* CourseCLONE);
void DeleteCourseF(Course* CourseDEL);
CompareResult CompareCoursesF(Course* CourseCMP1, Course* CourseCMP2);
void PrintCourseF(Course* CoursePRINT);

// Internal user function //

Course* CreateCourse(char* ID, char* name, int points);

int main()
{
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* pszCommand = " ";

	char* pID=NULL;
	char* pName = NULL;
	char* pPoints;
	char* pPrerequisiteID = NULL;
	int points;
	int CourseCount = 0;
	Result isOK;

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Memory Leaks Check

	DEPEND_GRAPH* pCourseGraph;
	Course *pCourse, *pParentCourse;

	// dependency graph for coursed is created
	pCourseGraph = CreateGraph((CLONE_ELEMENT)&CloneCourseF, (DELETE_ELEMENT)&DeleteCourseF, (COMPARE_ELEMENTS)&CompareCoursesF, (PRINT_ELEMENT)&PrintCourseF);

	while (fgets(szLine, MAX_LINE_SIZE, stdin)) // parsing until EOF
	{
		pszCommand = strtok(szLine, delimiters);
		
		if (NULL == pszCommand) // no command
		{
			continue;
		}

		if (0 == strcmp(pszCommand, "Add_Course")) // AddElement is called
		{
			pID = strtok(NULL, delimiters);
			pName = strtok(NULL, delimiters);
			pPoints = strtok(NULL, delimiters);
			pPrerequisiteID = strtok(NULL, delimiters);

			// Add course to the the courses graph, depending on prerequisite ID
			if (pID == NULL || pName == NULL || pPoints == NULL || pPrerequisiteID == NULL) // parameters check
			{
				fprintf(stderr, "%s failed: not enough parameters\n", pszCommand);
			}

			else
			{
				points = atoi(pPoints);

				if (strcmp(pPrerequisiteID, "000000") == 0)
				{
					pCourse = CreateCourse(pID, pName, points);
					isOK = AddElement(pCourseGraph, pCourse, NULL);
					// delete user copy
					DeleteCourseF(pCourse);
				}

				else
				{
					pCourse = CreateCourse(pID, pName, points);
					pParentCourse = CreateCourse(pPrerequisiteID, pName, points);
					isOK = AddElement(pCourseGraph, pCourse, pParentCourse);
					// delete user copies
					DeleteCourseF(pCourse);
					DeleteCourseF(pParentCourse);
				}

				if (isOK == FAILURE) // graph returned FAILURE, print to error channel
				{
					fprintf(stderr, "%s failed: internal error\n", pszCommand);
					fprintf(stderr, "%s %s %s %d %s\n", pszCommand, pID, pName, points, pPrerequisiteID);
				}
			}		
		}

		else if (0 == strcmp(pszCommand, "Print_Prerequisites")) // PrintPrerequisites is called
		{
			pID = strtok(NULL, delimiters);

			if (pID == NULL) // parameters check failed
			{
				fprintf(stderr, "%s failed: not enough parameters\n", pszCommand);
			}

			else
			{
				pCourse = CreateCourse(pID, "Virtual1", 1);
				PrintPrerequisities(pCourseGraph, pCourse);
				// delete user copy
				DeleteCourseF(pCourse);
			}
		}

	    else if ( 0 == strcmp(pszCommand, "Print_Executed") ) // PrintExecElements is called
		{
			PrintExecElements(pCourseGraph);
		}

	    else if ( 0 == strcmp(pszCommand, "Take_Course") ) // ExecuteElement is called
		{
			pID = strtok(NULL, delimiters);

			if (pID == NULL) // parameters check failed
			{
				fprintf(stderr, "%s failed: not enough parameters\n", pszCommand);
			}

			else
			{
				pCourse = CreateCourse(pID, "Virtual2", 1);
				isOK = ExecuteElement(pCourseGraph, pCourse);
				// delete user copy
				DeleteCourseF(pCourse);

				if (isOK == FAILURE) // graph returned FAILURE, print to error channel
				{
					fprintf(stderr, "%s failed: internal error\n", pszCommand);
					fprintf(stderr, "%s %s\n", pszCommand, pID);
				}
			}
		}
	    else if ( 0 == strcmp(pszCommand, "Reset_Courses") ) // ResetGraph is called
		{
			
			isOK = ResetGraph(pCourseGraph);

			if (isOK == FAILURE) // graph returned FAILURE, print to error channel
			{
				fprintf(stderr, "%s failed: internal error\n", pszCommand);
				fprintf(stderr, "%s\n", pszCommand);
			}
		}

	    else if ( 0 == strcmp(pszCommand, "Amount_of_Courses") ) // CountElements is called
		{
			CourseCount = CountElements(pCourseGraph);

			if (CourseCount == -1) // graph returned FAILURE, print to error channel
			{
				fprintf(stderr, "%s failed: internal error\n", pszCommand);
				fprintf(stderr, "%s\n", pszCommand);
			}

			else
			{
				printf("There are %d Courses in the database\n", CourseCount);
			}
		}

	    else if ( 0 == strcmp(pszCommand, "Remove_Course") ) // RemoveElement is called
		{
			pID = strtok(NULL, delimiters);

			if (pID == NULL) // parameters check failed
			{
				fprintf(stderr, "%s failed: not enough parameters\n", pszCommand);
			}
			
			else
			{
				pCourse = CreateCourse(pID, "Virtual3", 1);
				isOK = RemoveElement(pCourseGraph, pCourse);
				// delete user copy
				DeleteCourseF(pCourse);

				if (isOK == FAILURE) // graph returned FAILURE, print to error channel
				{
					fprintf(stderr, "%s failed: internal error\n", pszCommand);
					fprintf(stderr, "%s %s\n", pszCommand, pID);
				}
			}
		}

	    else if ( 0 == strcmp(pszCommand, "Print_Line") )
		{
			fgets(szLine, MAX_LINE_SIZE, stdin);
			printf("%s", szLine);
		}

		//else if (0 == strcmp(pszCommand, "End"))
		//{
		//	break;
		//}
	}

	DeleteGraph(pCourseGraph);

	return 0;
}

/* *****************************************************
Function: CloneCourseF
Abstract: User function for ADT, which copies a given course and its contents
Parameters:
	CourseCLONE - pointer to the required course to copy
Return Value:
	pCourse - pointer to the copied course
***************************************************** */
Course* CloneCourseF(Course* CourseCLONE)
{
	Course* pCourse;

	pCourse = (Course*)malloc(sizeof(Course));

	if (pCourse == NULL)
	{
		fprintf(stdout, "main.c: Failed to allocate memory");
		exit(-1);
	}

	pCourse->ID= (char*)malloc((strlen(CourseCLONE->ID) + 1));
	pCourse->name = (char*)malloc((strlen(CourseCLONE->name) + 1));

	if (pCourse->name == NULL || pCourse->ID == NULL)
	{
		fprintf(stdout, "main.c: Failed to allocate memory");
		exit(-1);
	}

	strcpy(pCourse->ID, CourseCLONE->ID);
	strcpy(pCourse->name, CourseCLONE->name);
	pCourse->points = CourseCLONE->points;

	return pCourse;
}

/* *****************************************************
Function: DeleteCourseF
Abstract: User function for ADT, which deletes a given course and its contents
Parameters:
	CourseDEL - pointer to the required course for deletion
Return Value: N/a
***************************************************** */
void DeleteCourseF(Course* CourseDEL)
{
	free(CourseDEL->ID);
	free(CourseDEL->name);
	free(CourseDEL);
}

/* *****************************************************
Function: ComapreCourseF
Abstract: User function for ADT, which comapres to course's IDs
Parameters:
	CourseCMP1 - pointer to course #1 for comparison
	CourseCMP2 - pointer to course #2 for comparison
Return Value:
	EQUAL if course's IDs are equal or blank, otherwise NOT_EQUAL
***************************************************** */
CompareResult CompareCoursesF(Course* CourseCMP1, Course* CourseCMP2)
{
	if (CourseCMP1 == NULL && CourseCMP2 == NULL)
	{
		return EQUAL;
	}

	if (CourseCMP1 == NULL || CourseCMP1->ID == NULL || CourseCMP2 == NULL || CourseCMP2->ID == NULL)
	{
		return NOT_EQUAL;
	}

	if (strcmp(CourseCMP1->ID, CourseCMP2->ID) == 0)
	{
		return EQUAL;
	}

	return NOT_EQUAL;
}

/* *****************************************************
Function: PrintCourseF
Abstract: User function for ADT, which prints the details of a given course
Parameters:
	CoursePRINT - pointer to the required course to print
Return Value: N/a
***************************************************** */
void PrintCourseF(Course* CoursePRINT)
{
	printf("Course - %s\n", CoursePRINT->ID);
	printf("====================\n");
	printf("Name - %s\n", CoursePRINT->name);
	printf("Points - %d", CoursePRINT->points);
}

/* *****************************************************
Function: CreateCourse
Abstract: Creates a new course from user input
Parameters:
	ID - pointer to a string, which is the course's identifier (element)
	name - pointer to a string, which is the course's name
	points - number of course's point
Return Value:
	pNewCourse - pointer to the created course
***************************************************** */
Course* CreateCourse(char* ID, char* name ,int points)
{
	Course* pNewCourse;

	pNewCourse = (Course*)malloc(sizeof(Course));

	if (pNewCourse == NULL)
	{
		fprintf(stdout, "main.c: Failed to allocate memory");
		exit(-1);
	}

	pNewCourse->ID = (char*)malloc((strlen(ID) + 1));
	pNewCourse->name = (char*)malloc((strlen(name) + 1));

	if (pNewCourse->name == NULL || pNewCourse->ID == NULL)
	{
		fprintf(stdout, "main.c: Failed to allocate memory");
		exit(-1);
	}

	strcpy(pNewCourse->ID, ID);
	strcpy(pNewCourse->name, name);
	pNewCourse->points = points;

	return pNewCourse;
}