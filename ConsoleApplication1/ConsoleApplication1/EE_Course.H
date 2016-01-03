#ifndef EE_COURSE_H
#define EE_COURSE_H

#include "Course.H"

class EE_Course : public Course {
public:
	// Constructor: initializes ee_course
	EE_Course();

	// Methods to access data individually
	int getFactor() const; // Value of factor on course
	int getCourseGrade() const;

	// Methods to change data individually
	int setFactor(int factorToSet); // Add factor to course
	
protected:
	int factor_;
};

#endif // EE_COURSE_H