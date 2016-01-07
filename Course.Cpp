#include "Course.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

Course::Course(int courseNum, char* courseName, int hwAmount, double hwWeigh) :
	courseNum_(courseNum), hwAmount_(hwAmount), hwWeigh_(hwWeigh), examGrade_(0) {

	courseName_ = new char[strlen(courseName) + 1];
	strcpy(courseName_, courseName);

	hwGrade_ = new int[hwAmount]();
}

int Course::getNum() const
{
	return courseNum_;
}

char* Course::getName() const
{
	char* namecpy = new char[strlen(courseName_) + 1];
	strcpy(namecpy, courseName_);
	return namecpy;
}

int Course::getExamGrade() const
{
	return examGrade_;
}

int Course::getHwGrade(int num) const
{
	int* grade = hwGrade_;
	return *(grade + num);
}

int Course::getHwNum() const
{
	return hwAmount_;
}

double Course::getHwWeigh() const
{
	return hwWeigh_;
}

double Course::getHwAverage() const
{
	if (hwAmount_ == 0) return 0;
	int sum = 0;
	for (int i = 0; i < hwAmount_; i++) {
		sum += *(hwGrade_ + i);
	}
	return (double)sum / (double)hwAmount_;
}

int Course::getCourseGrade() const
{
	double tmp = (1 - (double)hwWeigh_)*(double)examGrade_ + (double)hwWeigh_*(double)getHwAverage();
	int finalGrade = (int)(tmp + 0.5);
	return finalGrade;
}

Course :: ~Course()
{
	if (courseName_ != NULL)
		delete[] courseName_;

	if (hwGrade_ != NULL)
		delete[] hwGrade_;
}

bool Course::setExamGrade(int newExamGrade)
{
	if (newExamGrade > 100 || newExamGrade < 0)
		return false;
	examGrade_ = newExamGrade;
	return true;
}

bool Course::setHwGrade(int hwNum, int newHwGrade)
{
	if ((newHwGrade > 100) || (newHwGrade < 0) || (hwNum >= hwAmount_))
		return false;

	*(hwGrade_ + hwNum) = newHwGrade;
	return true;
}