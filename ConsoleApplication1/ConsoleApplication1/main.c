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

void Print_Course(Course*);
Course* Clone_Course(Course*);
void Delete_Course(Course*);
CompareResult Compare_courses(Course*, Course*);


int main()
{
  
  char szLine[MAX_LINE_SIZE];
  char* delimiters = " \t\n";
  char* pszCommand;
   

  while (fgets(szLine, MAX_LINE_SIZE, stdin))
    {
      
      pszCommand = strtok(szLine, delimiters);
      
      if (NULL == pszCommand )
        {
	  continue;
        }
      if ( 0 == strcmp(pszCommand, "Add_Course") )
        {
	  
	  /*
	    Add your code here
	   */
	}
      
      else if ( 0 == strcmp(pszCommand, "Print_Prerequisites") )
	{
	  /*
	    Add your code here
	  */
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

void Print_Course(Course* course) {
	printf("Course - <%c>\n", &course->ID);
	printf("====================\n");
	printf("Name - <%c>\n", &course->name);
	printf("Name - <%d>\n", &course->points);

}


Course* Clone_Course(Course* course1) {

	Course* course2 malloc(sizeof)

		return course2;

}










