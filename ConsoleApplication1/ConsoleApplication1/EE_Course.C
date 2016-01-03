#include "EE_Course.H"

EE_Course :: EE_Course() : Course(), factor_(0) {}

int EE_Course::getFactor() const
{
	return factor_;
}

int EE_Course:: getCourseGrade() const
{
	int finalGrade;
	finalGrade = round((1 - hwWeigh_)*examGrade_ + hwWeigh_*getHwAverage()) + factor_;
	if (finalGrade > 100)
		return 100;
	return finalGrade;
}

int EE_Course::setFactor(int factorToSet)
{
	factor_ = factorToSet;
	return 1;
}

