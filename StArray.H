#ifndef _STARRAY_H_
#define _STARRAY_H_
#include "Student.H"
#include "EE_Course.H"
#include "CS_Course.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

class StArray {
public:
	// Constructor: initializes course
	StArray();

	// Methods to access data individually
	bool printStudent(int studentID);
	void printAll();
	void resetStArray();
	~StArray(); // Destructor

				// Methods to change data individually
	bool addStudent(int studentID, char* studentName);
	bool addEE_Course(int studentID, int courseNum, char* courseName, int hwAmount, double hwWeigh);
	bool addCS_Course(int studentID, int courseNum, char* courseName, int hwAmount, double hwWeigh, bool isTakef, char* bookName);
	bool setHwGrade(int studentID, int courseNum, int hwNum, int newHwGrade);
	bool setExamGrade(int studentID, int courseNum, int newExamGrade);
	bool setFactor(int courseNum, int newFactor);

protected:
	Student* pStudentArray[MAX_STUDENT_NUM];
	int studentCount_;
};

#endif // STARRAY_H