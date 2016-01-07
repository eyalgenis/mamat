#include "CS_Course.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

/* *****************************************************
* Function: CS_Course
* Abstract:  Creates a new cs_course, inherits from Course and initializes it
* Parameters:
** int courseNum - Number of course
** char* courseName - Pointer to name of course
** int hwAmount - Number of hw sheets in course
** double hwWeigh - Weigh of all hw sheets from final grade
** char* bookName - Pointer to book name of course
** bool hwTakef - Sais if the hw is takef or magen
***************************************************** */
CS_Course::CS_Course(int courseNum, char* courseName, int hwAmount, double hwWeigh, bool hwTakef, char* bookName) :
	Course(courseNum, courseName, hwAmount, hwWeigh), hwTakef_(hwTakef) {
	bookName_ = new char[strlen(bookName) + 1];
	strcpy(bookName_, bookName);
}

/* *****************************************************
* Function: ~CS_Course
* Abstract: Destructor of cs_course
***************************************************** */
CS_Course::~CS_Course()
{
	if (bookName_ != NULL)
		delete[] bookName_;
}

/* *****************************************************
* Function: isTakef
* Abstract: Returns if hw is takef or magen
* Parameters:
* Return Value: true - Takef, false - Magen
***************************************************** */
bool CS_Course::isTakef() const
{
	return hwTakef_;
}

/* *****************************************************
* Function: getBook
* Abstract: Makes a copy of bookName and returns a pointer to it
* Parameters:
* Return Value: Pointer to book name of course
***************************************************** */
char * CS_Course::getBook() const
{
	char* bookcpy = new char[strlen(bookName_) + 1];
	strcpy(bookcpy, bookName_);
	return bookcpy;
}

/* *****************************************************
* Function: setTakef
* Abstract: Set hw is takef or magen
* Parameters: bool takef - 1 if takef, 0 if magen
* Return Value: true - Success, false - Failure
***************************************************** */
bool CS_Course::setTakef(bool takef)
{
	hwTakef_ = takef;
	return 1;
}

char* CS_Course::setBook(char* new_book)
{
	// destroy exiting book
	delete[] bookName_;
	// create new data
	bookName_ = new char[strlen(new_book) + 1];
	return strcpy(bookName_, new_book);

}

int CS_Course::getCourseGrade() const
{
	double tmp = (1 - (double)hwWeigh_)*(double)examGrade_ + (double)hwWeigh_*(double)getHwAverage();
	int finalGrade = (int)(tmp + 0.5);
	if (hwTakef_)
		return finalGrade;
	if (finalGrade>examGrade_)
		return finalGrade;
	return examGrade_;
}