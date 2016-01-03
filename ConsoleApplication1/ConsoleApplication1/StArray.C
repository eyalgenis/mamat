#include "StArray.H"

StArray::StArray(char * pStudent)
{
	pStudent_ = NULL;
	pStudent = pStudent_;
	count_ = 0;
}

bool StArray::addStudent(int studentID, char studentName)
{
	count_++;
	pStudent_+count_=Student(StudentID, studentName)
	// create Student ???
}
