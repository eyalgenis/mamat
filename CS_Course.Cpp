#include "CS_Course.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

CS_Course::CS_Course(int courseNum, char* courseName, int hwAmount, double hwWeigh, bool hwTakef, char* bookName) :
	Course(courseNum, courseName, hwAmount, hwWeigh), hwTakef_(hwTakef) {
	bookName_ = new char[strlen(bookName) + 1];
	strcpy(bookName_, bookName);
}

CS_Course::~CS_Course()
{
	if (bookName_ != NULL)
		delete[] bookName_;
}

bool CS_Course::isTakef() const
{
	return hwTakef_;
}

char * CS_Course::getBook() const // do we need to make a copy?!?!?
{
	char* bookcpy = new char[strlen(bookName_) + 1];
	strcpy(bookcpy, bookName_);
	return bookcpy;
}

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
	//	if (bookName_ == NULL) return;
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