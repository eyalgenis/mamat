#ifndef STARRAY_H
#define STARRAY_H
#include <iostream>
#include <stdbool.h>
#include "Student.H"
#include "Proj.H"
#include "EE_Course.H"
#include "CS_Course.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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