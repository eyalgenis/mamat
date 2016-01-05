#include <iostream>
#include "StArray.H"
using namespace std;

//CONSTRUCTOR
StArray :: StArray() :
studentCount_(0)
{
	pStudentArray[MAX_STUDENT_NUM] = { 0 }; // STATIC (INITIALIZE ONLY)
}

//DESTRUCTOR
StArray::~StArray()
{
	resetStArray();
}

bool StArray::addStudent(int studentID, char* studentName)
{
	if (studentName == NULL || studentCount_ == MAX_STUDENT_NUM)
		return false;
	Student* studentToAdd = new Student(studentID, studentName);
	pStudentArray[studentCount_] = studentToAdd;
	studentCount_++;
	return true;
}

bool StArray::addEE_Course(int studentID, int courseNum, char* courseName, int hwAmount, double hwWeigh)
{
	for (int i = 0; i < studentCount_; i++) {
		if (pStudentArray[i]->getID() == studentID) {
			EE_Course* ee_courseToAdd = new EE_Course(courseNum, courseName, hwAmount, hwWeigh);
			if (pStudentArray[i]->addEE_Course(ee_courseToAdd) == NULL)
				return false;
			delete ee_courseToAdd;
			return true;
		}
	}
	return false;
}

bool StArray::addCS_Course(int studentID, int courseNum, char* courseName, int hwAmount, double hwWeigh, bool isTakef, char* bookName)
{
	for (int i = 0; i < studentCount_; i++)
		if (pStudentArray[i]->getID() == studentID) {
			CS_Course* cs_courseToAdd = new CS_Course(courseNum, courseName, hwAmount, hwWeigh, isTakef, bookName);
			if (pStudentArray[i]->addCS_Course(cs_courseToAdd) == NULL)
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

	while (i < studentCount_)
	{
		FoundEECourse = pStudentArray[i]->getEE_Course(courseNum);
		if (FoundEECourse == NULL) // course not found
		{
			return false;
		}

		FoundEECourse->setFactor(newFactor); // set factor and return

		i++;
	}

	return true;
}

bool StArray::printStudent(int studentID)
{
	int i = 0;

	while (i < studentCount_)
	{
		if (pStudentArray[i]->getID() == studentID)
		{
			cout << "Printing student" << endl;
			cout << "================" << endl;
			pStudentArray[i]->print();
			return true;
		}
	}

	return false;
}

void StArray::printAll()
{
	cout << "Prining all students" << endl;
	cout << "####################" << endl;

	int i = 0;

	while (i < studentCount_)
	{
		pStudentArray[i]->print();
	}

	return;
}

void StArray::resetStArray()
{
	int i = 0;
	while (i < studentCount_)
	{
		pStudentArray[i]->~Student();
		pStudentArray[i] = NULL;
	}

	studentCount_ = 0;
	return;
}