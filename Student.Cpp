#include "Student.H"

//CONSTRUCTOR
Student::Student(const int ID, const char* PersonName) :
Person(ID, PersonName), EECoursesTaken_(0), CSCoursesTaken_(0)
{
	pEEArray[MAX_COURSE_NUM] = { 0 }; // STATIC (INITIALIZE ONLY)
	pCSArray[MAX_COURSE_NUM] = { 0 }; // STATIC (INITIALIZE ONLY)
}

//DESTRUCTOR
Student::~Student() {} // THAT'S IT? NO MORE DELETES OF ARRAYS POINT-TO-ELEMENTS?? (lior vector...)

//get student's sum of courses from EE + CS  
int Student::getCourseCnt() const
{
	return EECoursesTaken_ + CSCoursesTaken_;
}

//create *COPY* EE course + add to array of pointers to his EE courses
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

//create *COPY* CS course + add to array of pointers to his CS courses
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

//get pointer to student's EE course
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

//get pointer to student's CS course
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

//get student's average from all (EE + CS) courses
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

//print all details of the student
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