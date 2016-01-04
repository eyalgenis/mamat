#include "Student.H"

using std::cout;
using std::endl;
using std::boolalpha;

//CONSTRUCTOR
Student::Student(const int ID, const char* PersonName) :
Person(ID, PersonName), EECoursesTaken_(0), CSCoursesTaken_(0)
{
	EE_Course* pEEArray[MAX_COURSE_NUM] = { 0 }; // STATIC
	CS_Course* pCSArray[MAX_COURSE_NUM] = { 0 }; // STATIC
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