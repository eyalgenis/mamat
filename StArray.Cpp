#include "StArray.H"
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

//CONSTRUCTOR
StArray::StArray() :
	studentCount_(0)
{
	int i = 0;
	while (i < MAX_STUDENT_NUM)
	{
		pStudentArray[i] = NULL; // STATIC (INITIALIZE ONLY)
		i++;
	}
}

//DESTRUCTOR
StArray::~StArray()
{
	resetStArray();
}

bool StArray::addStudent(int studentID, char* studentName)
{
	if ((studentName == NULL) || (studentCount_ == MAX_STUDENT_NUM) || (studentID < 0))
		return false;

	int i = 0;

	while (i < studentCount_)
	{
		if (pStudentArray[i]->getID() == studentID)
		{
			return false; //student is already in array
		}
		i++;
	}

	Student* studentToAdd = new Student(studentID, studentName);
	pStudentArray[studentCount_] = studentToAdd;
	studentCount_++;
	return true;
}

bool StArray::addEE_Course(int studentID, int courseNum, char* courseName, int hwAmount, double hwWeigh)
{
	if (hwWeigh < 0 || hwWeigh > 1)
		return false;
	for (int i = 0; i < studentCount_; i++) {
		if (pStudentArray[i]->getID() == studentID) {
			EE_Course* ee_courseToAdd = new EE_Course(courseNum, courseName, hwAmount, hwWeigh);
			if (pStudentArray[i]->addEE_Course(ee_courseToAdd) == false)
				return false;
			delete ee_courseToAdd;
			return true;
		}
	}
	return false;
}

bool StArray::addCS_Course(int studentID, int courseNum, char* courseName, int hwAmount, double hwWeigh, bool isTakef, char* bookName)
{
	if (hwWeigh < 0 || hwWeigh > 1)
		return false;
	for (int i = 0; i < studentCount_; i++)
		if (pStudentArray[i]->getID() == studentID) {
			CS_Course* cs_courseToAdd = new CS_Course(courseNum, courseName, hwAmount, hwWeigh, isTakef, bookName);
			if (pStudentArray[i]->addCS_Course(cs_courseToAdd) == false)
				return false;
			delete cs_courseToAdd;
			return 1;
		}
	return 0;
}

bool StArray::setHwGrade(int studentID, int courseNum, int hwNum, int newHwGrade)
{
	EE_Course* FoundEECourse;
	CS_Course* FoundCSCourse;
	int i = 0;

	while (i < studentCount_)
	{
		if (pStudentArray[i]->getID() == studentID) // Student found
		{
			FoundCSCourse = pStudentArray[i]->getCS_Course(courseNum);
			if (FoundCSCourse == NULL) // Not CS
			{
				FoundEECourse = pStudentArray[i]->getEE_Course(courseNum);
				if (FoundEECourse == NULL) // Not EE
				{
					return false;
				}

				if (FoundEECourse->setHwGrade(hwNum, newHwGrade) == false)
					return false;
				return true;
			}

			if (FoundCSCourse->setHwGrade(hwNum, newHwGrade) == false)
				return false;
			return true;
		}

		i++;
	}

	return false;
}

bool StArray::setExamGrade(int studentID, int courseNum, int newExamGrade)
{
	EE_Course* FoundEECourse;
	CS_Course* FoundCSCourse;
	int i = 0;

	while (i < studentCount_)
	{
		if (pStudentArray[i]->getID() == studentID) // Student found
		{
			FoundCSCourse = pStudentArray[i]->getCS_Course(courseNum);
			if (FoundCSCourse == NULL) // Not CS
			{
				FoundEECourse = pStudentArray[i]->getEE_Course(courseNum);
				if (FoundEECourse == NULL) // Not EE
				{
					return false;
				}

				if (FoundEECourse->setExamGrade(newExamGrade) == false)
					return false;
				return true;
			}

			if (FoundCSCourse->setExamGrade(newExamGrade) == false)
				return false;
			return true;
		}

		i++;
	}

	return false;
}

bool StArray::setFactor(int courseNum, int newFactor)
{
	EE_Course* FoundEECourse;
	int i = 0;
	bool foundOne = false;

	while (i < studentCount_)
	{
		FoundEECourse = pStudentArray[i]->getEE_Course(courseNum);
		if (FoundEECourse != NULL) // course not found for this student
		{
			FoundEECourse->setFactor(newFactor); // set factor
			foundOne = true;
		}

		i++;
	}

	return foundOne;
}

bool StArray::printStudent(int studentID)
{
	int i = 0;

	while (i < studentCount_)
	{
		if (pStudentArray[i]->getID() == studentID)
		{
			pStudentArray[i]->print();
			return true;
		}
	i++;
	}

	return false;
}

void StArray::printAll()
{
	int i = 0;

	while (i < studentCount_)
	{
		pStudentArray[i]->print();
		i++;
	}

	return;
}

void StArray::resetStArray()
{
	int i = 0;
	while (i < studentCount_)
	{
		delete pStudentArray[i];
		pStudentArray[i] = NULL;
	}

	studentCount_ = 0;
	return;
}