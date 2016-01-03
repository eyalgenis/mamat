#include "Student.H"
#include <stdbool.h>

using std::cout;
using std::endl;
using std::boolalpha;

//* Function description: constructor of the object Student.
//* Return value: an object of the class Student
Student::Student(const int ID, const string Name, NumOfEECourses, NumOfCSCourses) :
Person(ID, Name), NumOfEECourses(NumOfEECourses), NumOfCSCourses(NumOfCSCourses)
{
	EE_Course* pEEArray[MAX_COURSE_NUM] = { 0 };
	CS_Course* pCSArray[MAX_COURSE_NUM] = { 0 };
}


int Student::getCouseCnt() const { return NumOfEECourses + NumOfCSCourses };

bool Student::addEE_Course(EE_Course* EECourseToAdd)  // EE_COURSE* ???????????
{
	int i=0;
	while (i < MAX_COURSE_NUM)
	{
		if (pEEArray[i] != NULL)
		{
			pEEArray[i] = EECourseToAdd;
			return true;
		}
		
		i++;
	}

	return false;
}

bool Student::addCS_Course(CS_Course* CSCourseToAdd)
{
	int i = 0;
	while (i < MAX_COURSE_NUM)
	{
		if (pEEArray[i] != NULL)
		{
			pEEArray[i] = CSCourseToAdd;
			return true;
		}

		i++;
	}

	return false;
}


//*************************************************************
////* Function description: raises a flag that indicates a Student is sick.
////* Return value: FAILURE/SUCCESS
//*************************************************************
//Result Student::set_sick()
//{
//	sick = true;
//	return SUCCESS;
//}

//*************************************************************
////* Function description: changes a Student's parents phone number.
//*************************************************************
//void Student::change_phone(const string new_phone)
//{
//	phone = new_phone;
//}

////***********************************************************
////* Function description: gets out a Student's phone number
//*************************************************************
//string Student::get_phone() const { return phone; }


//*************************************************************
//* Function description: prints out a Student's information.
//*************************************************************
void Student::print() const
{
	Person::print();
	cout << "Parant's Phone : " << phone << endl;
	string is_sick =((sick==true) ? "true" : "false");
	cout << "Is sick : " << is_sick << endl;
}



