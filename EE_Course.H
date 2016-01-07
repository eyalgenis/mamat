#ifndef _EE_COURSE_H_
#define _EE_COURSE_H_
#include "Course.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

class EE_Course : public Course {
public:
	// Constructor: initializes ee_course
	EE_Course(int courseNum, char* courseName, int hwAmount, double hwWeigh);

	// Methods to access data individually
	int getFactor() const; // Value of factor on course
	int getCourseGrade();
	~EE_Course();

	// Methods to change data individually
	bool setFactor(int factorToSet); // Add factor to course

protected:
	int factor_;
};

#endif // EE_COURSE_H