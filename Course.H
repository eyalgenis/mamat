#ifndef COURSE_H
#define COURSE_H

#include <cstdlib>
#include <string.h>
#include <algorithm>
#include <windows.h>

class Course {
public:
	// Constructor: initializes course
	Course(int courseNum, char* courseName, int hwAmount, double hwWeigh);

	// Methods to access data individually
	int getNum() const; // Number of this course
	char* getName() const; // Pointer to string of name of this course
	int getExamGrade() const; // Exam's grade of this course
	int getHwGrade(int num) const; // HW's grade of this course
	int getHwAmount() const; // Number of HW to due on this course
	double getHwWeigh() const; // Weigh of HW on this course
	double getHwAverage() const; // Average grade of HW on this course
	int getCourseGrade() const; // Final grade on this course
	~Course(); // Destructor

	// Methods to change data individually
	bool setExamGrade(int newExamGrade);
	bool setHwGrade(int hwNum, int newHwGrade);

protected:
	// Data
	int courseNum_;
	char* courseName_;
	int hwAmount_;
	double hwWeigh_;
	int examGrade_;
	int* hwGrade_;
};

#endif // COURSE_H