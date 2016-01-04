#ifndef CS_COURSE_H
#define CS_COURSE_H

#include "Course.H"

class CS_Course : public Course {
public:
	// Constructor: initializes cs_course
	CS_Course(int courseNum, char* courseName, int hwAmount, double hwWeigh, bool hwTakef, char* bookName);

	// Methods to access data individually
	bool isTakef() const; // Value of factor on course
	char* getBook() const; // Add factor to course
	int getCourseGrade() const;
	~CS_Course();

	// Methods to change data individually
	bool setTakef(bool takef);
	char* setBook(char* book);

protected:
	bool hwTakef_;
	char* bookName_;
};

#endif // CS_COURSE_H