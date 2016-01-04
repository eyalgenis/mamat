#ifndef STARRAY_H
#define STARRAY_H

#include "Student.H"

class StArray {
public:	// Constructor: initializes course	StArray(Student* pStudent);	// Methods to access data individually	bool printStudent(int studentID);	bool printAll();	void resetStArray();	~StArray(); // Destructor	// Methods to change data individually	bool addStudent(int studentID, char studentName);	bool addEE_Course(int studentID, int courseNum, char courseName, int hwAmount, double hwWeigh);	bool addCS_Course(int studentID, int courseNum, char courseName, int hwAmount, double hwWeigh, bool isTakef, char bookName);	bool setHwGrade(int studentID, int courseNum, int hwNum, int newHwGrade);	bool setExamGrade(int studentID, int courseNum, int newExamGrade);	bool setFactor(int courseNum);protected:	// Data	Student* student_;	int count_;
};

#endif // STARRAY_H