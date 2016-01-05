#include "Course.H"

Course :: Course(int courseNum, char* courseName, int hwAmount, double hwWeigh) :
	courseNum_(courseNum), hwAmount_(hwAmount), hwWeigh_(hwWeigh), examGrade_(0) {

	courseName_ = new char[strlen(courseName) + 1];
	strcpy(courseName_, courseName);

	hwGrade_ = new int[hwAmount]();
}

int Course::getNum() const
{	return courseNum_;
}

char* Course::getName() const
{	char* namecpy = new char[strlen(courseName_) + 1];
	strcpy(namecpy, courseName_);
	return namecpy;
}

int Course::getExamGrade() const
{	return examGrade_;
}

int Course::getHwGrade(int num) const
{	int* grade = hwGrade_;
	return *(grade+num);
}

int Course::getHwAmount() const
{	return hwAmount_;
}

double Course::getHwWeigh() const
{	return hwWeigh_;
}

double Course::getHwAverage() const
{	int sum = 0;
	for (int i = 0; i < hwAmount_; i++) {
		sum += *(hwGrade_+i);
	}
	return (double)sum/(double)hwAmount_;
}

int Course::getCourseGrade() const
{	return round((1-hwWeigh_)*examGrade_+hwWeigh_*getHwAverage());
}

Course :: ~Course()
{	delete[] courseName_;
	delete[] hwGrade_;
}

bool Course::setExamGrade(int newExamGrade)
{	if (newExamGrade > 100 || newExamGrade < 0)
		return 0;
	examGrade_ = newExamGrade;
	return 1;
}

bool Course::setHwGrade(int hwNum, int newHwGrade)
{	if (newHwGrade > 100 || newHwGrade < 0)
		return 0;
	if (hwNum > hwAmount_)
		return 0;

	*(hwGrade_ + hwNum) = newHwGrade;
	return 1;
}
