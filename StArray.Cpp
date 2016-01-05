#include <iostream>
#include "StArray.H"
using namespace std;

//CONSTRUCTOR
StArray::StArray(Student* pStudent) :
studentCount_(0)
{
	pStudentArray[MAX_STUDENT_NUM] = { 0 }; // STATIC (INITIALIZE ONLY)
}

//DESTRUCTOR
StArray::~StArray()
{
	resetStArray();
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

				FoundEECourse->setHwGrade(hwNum, newHwGrade); // yes EE
				return true;
			}

			FoundCSCourse->setHwGrade(hwNum, newHwGrade); // yes CS
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

				FoundEECourse->setExamGrade(newExamGrade); // found EE
				return true;
			}

			FoundCSCourse->setExamGrade(newExamGrade); // found CS
			return true;
		}

		i++;
	}
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