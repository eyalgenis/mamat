#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defines.h"
#include "DependGraph.h"


#define MAX_LINE_SIZE 255

typedef struct Course_ {
  char* name;
  char* ID;
  int points;
} Course, *PCourse;

void PrintCourse(Course*);
Course* CloneCourse(Course*);
void DeleteCourse(Course*);
CompareResult CompareCourses(Course*, Course*);
Course* CreateCourse(char*, char*, int);

int main()
{
  
  char szLine[MAX_LINE_SIZE];
  char* delimiters = " \t\n";
  char* pszCommand;

  char* pID = NULL;
  char* pName = NULL;
  char* pPrerequisiteID = NULL;
  char* pPoints;
  int points;
   

  while (fgets(szLine, MAX_LINE_SIZE, stdin))
    {
      
      pszCommand = strtok(szLine, delimiters);
      
      if (NULL == pszCommand )
        {
	  continue;
        }
      if ( 0 == strcmp(pszCommand, "Add_Course") )
        {
			

			pID = strtok(NULL, delimiters);
			pName = strtok(NULL, delimiters);
			pPoints = strtok(NULL, delimiters);
			pPrerequisiteID = strtok(NULL, delimiters);

			if (pID == NULL || pName == NULL || pPoints == NULL || pPrerequisiteID == NULL) {
				fprintf(stderr, "%s failed: not enough parameters\n", pszCommand);
			}

			
			points = (atoi)(pPoints);

			Course* CreateCourse(char* ID, char* name, int points)

	}
      
      else if ( 0 == strcmp(pszCommand, "Print_Prerequisites") )
	{
		
	}
      else if ( 0 == strcmp(pszCommand, "Print_Executed") )
	{
	  /*
	    Add your code here
	  */
	}
      else if  ( 0 == strcmp(pszCommand, "Take_Course") )
	{
	  /*
	    Add your code here
	  */
	}
      else if  ( 0 == strcmp(pszCommand, "Reset_Courses") )
	{
	  /*
	    Add your code here
	  */
	}
      else if  ( 0 == strcmp(pszCommand, "Amount_of_Courses") )
	{
	  /*
	    Add your code here
	  */
	}
      else if ( 0 == strcmp(pszCommand, "Remove_Course") )
	{
	  /*
	    Add your code here
	  */
	}
      else if ( 0 == strcmp(pszCommand, "Print_Line") )
	{
	  /*
	    Add your code here
	   */
	}
      
    }

  return 0;
}

Course* CloneCourse(Course* course) {

	Course* pCourse;
	
	pCourse = (Course*)malloc(sizeof(Course));

	if (pCourse == NULL) {
		fprintf(stdout, "main.c: Failed to allocate memory");
		exit(-1);
	}

	pCourse->name = (char*)malloc(strlen(course->name) + 1);
	pCourse->ID = (char*)malloc(strlen(course->ID) + 1);

	if (pCourse->name == NULL || pCourse->ID == NULL)
	{
		fprintf(stdout, "main.c: Failed to allocate memory");
		exit(-1);
	}

	strcpy(pCourse->name, course->name);
	strcpy(pCourse->ID, course->ID);
	pCourse->points = course->points;

	return pCourse;

}
void PrintCourse(Course* course) {

	printf("Course - %s\n", course->ID);
	printf("====================\n");
	printf("Name - %s\n", course->name);
	printf("Name - %d", course->points);
}
void DeleteCourse(Course* course) {
	free(course->ID);
	free(course->name);
	free(course);
}
Course* CreateCourse(char* ID, char* name, int points) {

	Course* pCourse;
	pCourse = (Course*)malloc(sizeof(Course));
	
	if (pCourse == NULL) {
		fprintf(stdout, "main.c: Failed to allocate memory");
		exit(-1);
	}

	pCourse->name = (char*)malloc(strlen(name) + 1);
	pCourse->ID = (char*)malloc(strlen(ID) + 1);
	
	if (pCourse->name == NULL || pCourse->ID == NULL) {
			fprintf(stdout, "main.c: Failed to allocate memory");
			exit(-1);
		}

	strcpy(pCourse->name, name);
	strcpy(pCourse->ID, ID);
	pCourse->points = points;

	return pCourse;
}
CompareResult CompareCourses(Course* course1, Course* course2) {
	
	if (strcmp(course1->ID, course2->ID) == 0) return EQUAL;
	if (course1 == NULL && course2 == NULL) return EQUAL;

	return NOT_EQUAL;
}


