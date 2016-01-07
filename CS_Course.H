#ifndef _CS_COURSE_H_
#define _CS_COURSE_H_
#include "Course.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

class CS_Course : public Course {
public:
	// Constructor: initializes cs_course
	CS_Course(int courseNum, char* courseName, int hwAmount, double hwWeigh, bool hwTakef, char* bookName);

	// Methods to access data individually
	bool isTakef() const; // Value of factor on course
	char* getBook() const; // Add factor to course
	int getCourseGrade() const;
	~CS_Course();

	// Methods to change data individually
	bool setTakef(bool takef);
	char* setBook(char* book);

protected:
	bool hwTakef_;
	char* bookName_;
};

#endif // CS_COURSE_H