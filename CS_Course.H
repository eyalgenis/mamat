#ifndef CS_COURSE_H
#define CS_COURSE_H

#include "Course.H"

class CS_Course : public Course {
public:
	// Constructor: initializes cs_course
	CS_Course();

	// Methods to access data individually
	bool isTakef() const; // Value of factor on course
	char* getBook() const; // Add factor to course
	int getCourseGrade() const;

	// Methods to change data individually
	bool setTakef(bool takef);
	char* setbook(char* book);

protected:
	bool hwTakef_;
	char* bookName_;
};

#endif // CS_COURSE_H