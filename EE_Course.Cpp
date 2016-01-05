#include "EE_Course.H"

EE_Course::EE_Course(int courseNum, char* courseName, int hwAmount, double hwWeigh) :
	Course(courseNum, courseName, hwAmount, hwWeigh), factor_(0) {}

EE_Course::~EE_Course() {}

int EE_Course::getFactor() const
{	return factor_;
}

int EE_Course:: getCourseGrade()
{	double tmp = (1 - (double)hwWeigh_)*(double)examGrade_ + (double)hwWeigh_*(double)getHwAverage() + (double)factor_;
	int finalGrade = (int)(tmp + 0.5);
	if (finalGrade > 100)
		return 100;
	return finalGrade;
}

bool EE_Course::setFactor(int factorToSet)
{	factor_ = factorToSet;
	return true;
}

