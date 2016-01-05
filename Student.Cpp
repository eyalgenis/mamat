#include "Student.H"

using std::cout;
using std::endl;

//CONSTRUCTOR
Student::Student(const int ID, const char* PersonName) :
Person(ID, PersonName), EECoursesTaken_(0), CSCoursesTaken_(0)
{
	pEEArray[MAX_COURSE_NUM] = { 0 }; // STATIC (INITIALIZE)
	pCSArray[MAX_COURSE_NUM] = { 0 }; // STATIC (INITIALIZE)
}

//DESTRUCTOR
Student::~Student() {} // THAT'S IT? NO MORE DELETES OF ARRAYS POINT-TO-ELEMENTS?? (lior vector...)

//SUM OF STUDENT'S LEARNED COURSES
int Student::getCouseCnt() const
{
	return EECoursesTaken_ + CSCoursesTaken_;
}

bool Student::addEE_Course(EE_Course* EECourseToAdd)  // pointer to EE_Course
{

	if (EECourseToAdd == NULL)
	{
		return false; // ??????? exit(-1) ????????
	}

	if (EECoursesTaken_ == MAX_COURSE_NUM) // student has full courses
	{
		return false;
	}

	EE_Course* CopyToAdd;
	CopyToAdd = new EE_Course(EECourseToAdd->getNum(), EECourseToAdd->getName(), EECourseToAdd->getHwNum(), EECourseToAdd->getHwWeigh());

	//if (CopyToAdd == NULL) // allocation failed ?? is it necessary ??
	//{
	//	cerr << "meme" << endl; // ?????????? MEME ?????????
	//	return false;
	//}

	CopyToAdd->setFactor(EECourseToAdd->getFactor());

	int i = 0;
	while (i < MAX_COURSE_NUM) // add course to available cell in array
	{
		if (pEEArray[i] != NULL)
		{
			pEEArray[i] = CopyToAdd;
			EECoursesTaken_++;
			return true;
		}
		
		i++;
	}

	return false;  // THE ARRAY IS FULL?
}

bool Student::addCS_Course(CS_Course* CSCourseToAdd)
{

	if (CSCourseToAdd == NULL)
	{
		return false; // ??????? exit(-1) ????????
	}

	if (CSCoursesTaken_ == MAX_COURSE_NUM) // student has full courses
	{
		return false;
	}

	CS_Course* CopyToAdd;
	CopyToAdd = new CS_Course(CSCourseToAdd->getNum(), CSCourseToAdd->getName(), CSCourseToAdd->getHwNum(), CSCourseToAdd->getHwWeigh(), CSCourseToAdd->isTakef(), CSCourseToAdd->getBook());

	//if (CopyToAdd == NULL) // allocation failed ?????? is it necessary ??????
	//{
	//	cerr << "meme" << endl; // ?????????? MEME ?????????
	//	return false;
	//}
	
	int i = 0;
	while (i < MAX_COURSE_NUM)
	{
		if (pCSArray[i] != NULL)
		{
			pCSArray[i] = CopyToAdd;
			CSCoursesTaken_++;
			return true;
		}

		i++;
	}

	return false;
}

bool Student::remCourse(const int CourseNumToRemove)
{
	int i = 0;
	while (i < MAX_COURSE_NUM)
	{
		if (pEEArray[i]->getNum() == CourseNumToRemove)
		{
			pEEArray[i]->~EE_Course();
			pEEArray[i] = NULL;
			CSCoursesTaken_++;
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

EE_Course* Student::getEE_Course(const int EECourseNum)
{
	int i = 0;
	while (i < MAX_COURSE_NUM)
	{
		if (pEEArray[i]->getNum() == EECourseNum)
		{
			return pEEArray[i];
		}

		i++;
	}

	return NULL;
}

CS_Course* Student::getCS_Course(const int CSCourseNum)
{
	int i = 0;
	while (i < MAX_COURSE_NUM)
	{
		if (pCSArray[i]->getNum() == CSCourseNum)
		{
			return pCSArray[i];
		}

		i++;
	}

	return NULL;
}

int Student::getAvg() // when const?
{
	int i = 0;
	int sum = 0;
	int avg;

	while (i < MAX_COURSE_NUM)
	{
		sum += pEEArray[i]->getCourseGrade() + pCSArray[i]->getCourseGrade();
		i++;
	}

	avg = sum / (EECoursesTaken_ + CSCoursesTaken_);
	return avg;
}

void Student::print() const
{
	char* StudName;
	char* EECourseName;
	char* CSCourseName;

	StudName = Student::getName(); // Person??
	cout << "Student Name: " << name << endl;
	delete []StudName; // delete copy

	cout << "Student ID: " << Student::getID() << endl;

	cout << "Average Grade: " << getAvg() << endl; // local method

	cout << "EE Courses:" << endl;

	int i = 0;
	while (i < EECoursesTaken_)
	{
		EECourseName = pEEArray[i]->getName();
		cout << pEEArray[i]->getNum() << " " << EECourseName << " " << pEEArray[i]->getCourseGrade() << endl;
		delete[] EECourseName;
	}

	cout << "CS Courses:" << endl;

	i = 0;
	while (i < CSCoursesTaken_)
	{
		CSCourseName = pCSArray[i]->getName();
		cout << pCSArray[i]->getNum() << " " << CSCourseName << " " << pCSArray[i]->getCourseGrade() << endl;
		delete[] CSCourseName;
	}

	return;
}