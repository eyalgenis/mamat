#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include <stdbool.h>
#include "Person.H"
#include "Proj.H"
#include "EE_Course.H"
#include "CS_Course.H"

class Student : public Person {

public:
	//CONSTRUCTOR
	Student(const int ID, const char* PersonName);

	//DESTRUCTOR
	~Student();

	//get student's sum of courses from EE + CS  
	int getCourseCnt() const;

	//create *COPY* EE course + add to array of pointers to his EE courses
	bool addEE_Course(EE_Course* EECourseToAdd);

	//create *COPY* CS course + add to array of pointers to his CS courses
	bool addCS_Course(CS_Course* CSCourseToAdd);

	//remove course (EE/CS) from memory + from student's array of pointers to courses
	bool remCourse(const int CourseNumToRemove);

	//get pointer to student's EE course
	EE_Course* getEE_Course(const int EECourseNum);

	//get pointer to student's CS course
	CS_Course* getCS_Course(const int CSCourseNum);

	//get student's average from all (EE + CS) courses
	int getAvg();

	//print all details of the student
	void print() const;

protected:
	EE_Course* pEEArray[MAX_COURSE_NUM]; // STATIC array - pointer to student's EE courses
	CS_Course* pCSArray[MAX_COURSE_NUM]; // STATIC array - pointer to student's CS courses
	int EECoursesTaken_;
	int CSCoursesTaken_;
};

#endif
