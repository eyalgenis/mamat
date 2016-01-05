#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "Person.H"
#include "Proj.H"
#include "EE_Course.H"
#include "CS_Course.H"
//#include <string>
#include <iostream>
#include <stdbool.h>

//using std::string;

class Student : public Person {
public:

	//CONSTRUCTOR
	Student(const int ID, const char* PersonName);


	//DESTRUCTOR
	~Student();


	int getCouseCnt() const;

	bool addEE_Course(EE_Course* EECourseToAdd);

	bool addCS_Course(CS_Course* CSCourseToAdd);

	bool remCourse(const int CourseNumToRemove);

	EE_Course* getEE_Course(const int EECourseNum);

	CS_Course* getCS_Course(const int CSCourseNum);

	int getAvg();

	void print() const;

protected:
	EE_Course* pEEArray[MAX_COURSE_NUM; // STATIC
	CS_Course* pCSArray[MAX_COURSE_NUM]; // STATIC
	int EECoursesTaken_;
	int CSCoursesTaken_;
};

#endif
