#include "EE_Course.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

/* *****************************************************
* Function: EE_Course
* Abstract:  Creates a new ee_course, inherits from Course and initializes it
* Parameters:
** int courseNum - Number of course
** char* courseName - Pointer to name of course
** int hwAmount - Number of hw sheets in course
** double hwWeigh - Weigh of all hw sheets from final grade
** int factor - Factor given in course, initialized to 0
***************************************************** */
EE_Course::EE_Course(int courseNum, char* courseName, int hwAmount, double hwWeigh) :
	Course(courseNum, courseName, hwAmount, hwWeigh), factor_(0) {}

/* *****************************************************
* Function: ~EE_Course
* Abstract: Destructor of ee_course
***************************************************** */
EE_Course::~EE_Course() {}

/* *****************************************************
* Function: getFactor
* Abstract: Returns the given factor
* Parameters:
* Return Value: Factor in course
***************************************************** */
int EE_Course::getFactor() const
{
	return factor_;
}

/* *****************************************************
* Function: getCourseGrade
* Abstract: Calculates the final grade of course including factor
* Parameters:
* Return Value: Course grade
***************************************************** */
int EE_Course::getCourseGrade()
{
	double tmp = (1 - (double)hwWeigh_)*(double)examGrade_ + (double)hwWeigh_*(double)getHwAverage() + (double)factor_;
	int finalGrade = (int)(tmp + 0.5);
	if (finalGrade > 100)
		return 100;
	if (finalGrade < 0)
		return 0;
	return finalGrade;
}

/* *****************************************************
* Function: setFactor
* Abstract: Set factor of course
* Parameters: int factorToSet
* Return Value: true - Success, false - Failure
***************************************************** */
bool EE_Course::setFactor(int factorToSet)
{
	factor_ = factorToSet;
	return true;
}