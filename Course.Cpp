#include "Course.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

/* *****************************************************
* Function: Course
* Abstract:  Creates a new course and initializes it
* Parameters:
** int courseNum - Number of course
** char* courseName - Pointer to name of course
** int hwAmount - Number of hw sheets in course
** double hwWeigh - Weigh of all hw sheets from final grade
***************************************************** */
Course::Course(int courseNum, char* courseName, int hwAmount, double hwWeigh) :
	courseNum_(courseNum), hwAmount_(hwAmount), hwWeigh_(hwWeigh), examGrade_(0) {

	courseName_ = new char[strlen(courseName) + 1];
	strcpy(courseName_, courseName);

	hwGrade_ = new int[hwAmount]();
}

/* *****************************************************
* Function: getNum
* Abstract: Returns course number 
* Parameters:
* Return Value: Number of course
***************************************************** */
int Course::getNum() const
{
	return courseNum_;
}

/* *****************************************************
* Function: getName
* Abstract: Makes a copy of course name and returns it
* Parameters:
* Return Value: Name of course
***************************************************** */
char* Course::getName() const
{
	char* namecpy = new char[strlen(courseName_) + 1];
	strcpy(namecpy, courseName_);
	return namecpy;
}

/* *****************************************************
* Function: getExamGrade
* Abstract: Returns course exam grade
* Parameters:
* Return Value: Exam grade of course
***************************************************** */
int Course::getExamGrade() const
{
	return examGrade_;
}

/* *****************************************************
* Function: getHwGrade
* Abstract: Calculates pointer to given hw number and returns grade
* Parameters: int num - Hw sheet number
* Return Value: Grade of specific hw
***************************************************** */
int Course::getHwGrade(int num) const
{
	int* grade = hwGrade_;
	return *(grade + num);
}

/* *****************************************************
* Function: getHwNum
* Abstract: Returns course amount of hw sheets
* Parameters: 
* Return Value: Amount of hw sheets
***************************************************** */
int Course::getHwNum() const
{
	return hwAmount_;
}

/* *****************************************************
* Function: getHwWeigh
* Abstract: Returns hw weigh from final grade
* Parameters:
* Return Value: Weigh of hw from final grade
***************************************************** */
double Course::getHwWeigh() const
{
	return hwWeigh_;
}

/* *****************************************************
* Function: getHwAverage
* Abstract: Calculates the average of all hw
* Parameters:
* Return Value: hw average grade
***************************************************** */
double Course::getHwAverage() const
{
	if (hwAmount_ == 0) return 0;
	int sum = 0;
	for (int i = 0; i < hwAmount_; i++) {
		sum += *(hwGrade_ + i);
	}
	return (double)sum / (double)hwAmount_;
}

/* *****************************************************
* Function: getCourseGrade
* Abstract: Calculates the final grade of course
* Parameters:
* Return Value: Course grade
***************************************************** */
int Course::getCourseGrade() const
{
	double tmp = (1 - (double)hwWeigh_)*(double)examGrade_ + (double)hwWeigh_*(double)getHwAverage();
	int finalGrade = (int)(tmp + 0.5);
	return finalGrade;
}

/* *****************************************************
* Function: ~Course
* Abstract: Destructor of course
***************************************************** */
Course :: ~Course()
{
	if (courseName_ != NULL)
		delete[] courseName_;

	if (hwGrade_ != NULL)
		delete[] hwGrade_;
}

/* *****************************************************
* Function: setExamGrade
* Abstract: Set the exam grade of course
* Parameters: int newExamGrade - Grade of exam to set
* Return Value: true - Success, false - Failure
***************************************************** */
bool Course::setExamGrade(int newExamGrade)
{
	if (newExamGrade > 100 || newExamGrade < 0)
		return false;
	examGrade_ = newExamGrade;
	return true;
}

/* *****************************************************
* Function: setHwGrade
* Abstract: Set a specific hw sheet grade
* Parameters: int hwNum - Specified hw number to set, int newHwGrade - grade to set
* Return Value: true - Success, false - Failure
***************************************************** */
bool Course::setHwGrade(int hwNum, int newHwGrade)
{
	if ((newHwGrade > 100) || (newHwGrade < 0) || (hwNum >= hwAmount_))
		return false;

	*(hwGrade_ + hwNum) = newHwGrade;
	return true;
}