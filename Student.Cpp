#include "Student.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

//CONSTRUCTOR
Student::Student(const int ID, const char* PersonName) :
	Person(ID, PersonName), EECoursesTaken_(0), CSCoursesTaken_(0)
{
	int i = 0;
	while (i < MAX_COURSE_NUM)
	{
		pEEArray[i] = NULL; // STATIC (INITIALIZE ONLY)
		pCSArray[i] = NULL; // STATIC (INITIALIZE ONLY)
		i++;
	}
}

////DESTRUCTOR
//Student::~Student() {} // THAT'S IT? NO MORE DELETES OF ARRAYS POINT-TO-ELEMENTS?? (lior vector...)

//get student's sum of courses from EE + CS  
int Student::getCourseCnt() const
{
	return EECoursesTaken_ + CSCoursesTaken_;
}

//create *COPY* EE course + add to array of pointers to his EE courses
bool Student::addEE_Course(EE_Course* EECourseToAdd)  // pointer to EE_Course
{
	if ((EECourseToAdd == NULL) || (EECoursesTaken_ >= MAX_COURSE_NUM))
		return false;

	int i = 0;
	while (i < EECoursesTaken_)
	{
		if (pEEArray[i]->getNum() == EECourseToAdd->getNum())
		{
			return false;
		}

		i++;
	}

	i = 0;
	while (i < CSCoursesTaken_)
	{
		if (pCSArray[i]->getNum() == EECourseToAdd->getNum())
		{
			return false;
		}

		i++;
	}

	EE_Course* CopyToAdd;
	CopyToAdd = new EE_Course(EECourseToAdd->getNum(), EECourseToAdd->getName(), EECourseToAdd->getHwNum(), EECourseToAdd->getHwWeigh());

	CopyToAdd->setFactor(EECourseToAdd->getFactor());

	i = 0;
	while (i < MAX_COURSE_NUM) // add course to available cell in array
	{
		if (pEEArray[i] == NULL)
		{
			pEEArray[i] = CopyToAdd;
			EECoursesTaken_++;
			return true;
		}

		i++;
	}

	return false;  // THE ARRAY IS FULL?
}

//create *COPY* CS course + add to array of pointers to his CS courses
bool Student::addCS_Course(CS_Course* CSCourseToAdd)
{
	if ((CSCourseToAdd == NULL) || (CSCoursesTaken_ >= MAX_COURSE_NUM))
		return false;

	int i = 0;
	while (i < CSCoursesTaken_)
	{
		if (pCSArray[i]->getNum() == CSCourseToAdd->getNum())
		{
			return false;
		}

		i++;
	}

	i = 0;
	while (i < EECoursesTaken_)
	{
		if (pEEArray[i]->getNum() == CSCourseToAdd->getNum())
		{
			return false;
		}

		i++;
	}

	CS_Course* CopyToAdd;
	CopyToAdd = new CS_Course(CSCourseToAdd->getNum(), CSCourseToAdd->getName(), CSCourseToAdd->getHwNum(), CSCourseToAdd->getHwWeigh(), CSCourseToAdd->isTakef(), CSCourseToAdd->getBook());

	i = 0;
	while (i < MAX_COURSE_NUM)
	{
		if (pCSArray[i] == NULL)
		{
			pCSArray[i] = CopyToAdd;
			CSCoursesTaken_++;
			return true;
		}

		i++;
	}

	return false;
}

//remove course (EE/CS) from memory + from student's array of pointers to courses
bool Student::remCourse(const int CourseNumToRemove)
{
	int i = 0;
	while (i < MAX_COURSE_NUM)
	{
		if (pEEArray[i]->getNum() == CourseNumToRemove)
		{
			pEEArray[i]->~EE_Course();
			pEEArray[i] = NULL;
			EECoursesTaken_--;
			return true;
		}

		i++;
	}

	i = 0;
	while (i < MAX_COURSE_NUM)
	{
		if (pCSArray[i]->getNum() == CourseNumToRemove)
		{
			pCSArray[i]->~CS_Course();
			pCSArray[i] = NULL;
			CSCoursesTaken_--;
			return true;
		}

		i++;
	}

	return false;
}

//get pointer to student's EE course
EE_Course* Student::getEE_Course(const int EECourseNum)
{
	int i = 0;
	while (i < EECoursesTaken_)
	{
		if (pEEArray[i]->getNum() == EECourseNum)
		{
			return pEEArray[i];
		}

		i++;
	}

	return NULL;
}

//get pointer to student's CS course
CS_Course* Student::getCS_Course(const int CSCourseNum)
{
	int i = 0;
	while (i < CSCoursesTaken_)
	{
		if (pCSArray[i]->getNum() == CSCourseNum)
		{
			return pCSArray[i];
		}

		i++;
	}

	return NULL;
}

//get student's average from all (EE + CS) courses
int Student::getAvg() // when const?
{
	if ((EECoursesTaken_ + CSCoursesTaken_) == 0)
		return 0;

	int i = 0;
	int sum = 0;
	double avg;

	while (i < EECoursesTaken_)
	{
		sum += pEEArray[i]->getCourseGrade();
		i++;
	}

	i = 0;
	while (i < CSCoursesTaken_)
	{
		sum += pCSArray[i]->getCourseGrade();
		i++;
	}

	avg = (double)sum / (double)(EECoursesTaken_ + CSCoursesTaken_);
	return (int)(avg+0.5);
}

//print all details of the student
void Student::print()
{
	char* StudName;
	char* EECourseName;
	char* CSCourseName;

	StudName = getName(); // Person??
	cout << "Student Name: " << StudName << endl;
	delete[]StudName; // delete copy

	cout << "Student ID: " << ID_ << endl;

	cout << "Average Grade: " << getAvg() << endl; // local method
	cout << "" << endl;
	cout << "EE Courses:" << endl;

	int i = 0;
	while (i < EECoursesTaken_)
	{
		EECourseName = pEEArray[i]->getName();
		cout << pEEArray[i]->getNum() << " " << EECourseName << ": " << pEEArray[i]->getCourseGrade() << endl;
		delete[] EECourseName;
		i++;
	}

	cout << "" << endl;
	cout << "CS Courses:" << endl;

	i = 0;
	while (i < CSCoursesTaken_)
	{
		CSCourseName = pCSArray[i]->getName();
		cout << pCSArray[i]->getNum() << " " << CSCourseName << ": " << pCSArray[i]->getCourseGrade() << endl;
		delete[] CSCourseName;
		i++;
	}

	cout << "" << endl;
	return;
}