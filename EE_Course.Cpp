#include "EE_Course.H"

EE_Course::EE_Course(int courseNum, char* courseName, int hwAmount, double hwWeigh) :
	Course(courseNum, courseName, hwAmount, hwWeigh), factor_(0) {}

EE_Course::~EE_Course() {}

int EE_Course::getFactor() const
{	return factor_;
}

int EE_Course:: getCourseGrade()
{	int finalGrade;
	finalGrade = ((1 - hwWeigh_)*examGrade_ + hwWeigh_*getHwAverage()) + factor_;
	if (finalGrade > 100)
		return 100;
	return finalGrade;
}

int EE_Course::setFactor(int factorToSet)
{	
	if (factorToSet > 100 || factorToSet < 0)
		return 0;
	factor_ = factorToSet;
	return 1;
}

