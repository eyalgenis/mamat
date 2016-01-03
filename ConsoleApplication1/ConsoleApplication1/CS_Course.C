#include "CS_Course.H"

CS_Course :: CS_Course(int hwTakef) : 
	Course(), hwTakef_(hwTakef) {}

bool CS_Course::isTakef() const
{
	return hwTakef_;
}

char * CS_Course::getBook() const
{
	return bookName_;
}

bool CS_Course::setTakef(bool takef)
{
	hwTakef_ = takef;
	return 1;
}

char * CS_Course::setbook(char * book)
{ 
	// destroy exiting data
	delete[] bookName_;
	// create new data
	bookName_ = new char[strlen(book) + 1];
	return strcpy(bookName_, book);
}

int CS_Course::getCourseGrade() const
{
	int finalGrade;
	if (hwTakef_)
		finalGrade = round((1 - hwWeigh_)*examGrade_ + hwWeigh_*getHwAverage());
	if (!hwTakef_)
		finalGrade = max(round((1 - hwWeigh_)*examGrade_ + hwWeigh_*getHwAverage()), examGrade_);

	return finalGrade;
}