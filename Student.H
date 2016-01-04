#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "Person.H"
#include "Proj.H"
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

	//////***********************************************************
	//////* Function description: gets out a Student's phone number
	////*************************************************************
	//string get_phone() const;

	////*************************************************************
	//////* Function description: changes a Student's parents phone number.
	////*************************************************************
	//void change_phone(const string phone);

	////*************************************************************
	//////* Function description: raises a flag that indicates a Student is sick.
	//////* Return value: FAILURE/SUCCESS
	////*************************************************************
	//Result set_sick();

	//*************************************************************
	//* Function description: prints out a Student's information.
	//*************************************************************
	void print() const;

protected:
	EE_Course* pEEArray;
	CS_Course* pCSArray;
	int EECoursesTaken_;
	int CSCoursesTaken_;
};

#endif
