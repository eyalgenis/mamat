#include "Course.H"
////
Course :: Course(char * courseNum, char * courseName, int hwAmount, double hwWeigh, int examGrade, int * hwGrade) :
	courseNum_(courseNum), courseName_(courseName), hwAmount_(hwAmount), hwWeigh_(hwWeigh), examGrade_(examGrade), hwGrade_(hwGrade) {
	count_++;
}

int Course::getNum() const
{
	return atoi(courseNum_);
}

char * Course::getName() const
{
	return courseName_;
}

int Course::getExamGrade() const
{
	return examGrade_;
}

int Course::getHwGrade(int num) const
{
	int* grade = hwGrade_;
	return *(grade+num);
}

int Course::getHwAmount() const
{
	return hwAmount_;
}

double Course::getHwWeigh() const
{
	return hwWeigh_;
}

double Course::getHwAverage() const
{
	int* grade = hwGrade_;
	int sum = 0;
	int i;
	for (i = 0; i < hwAmount_; i++) {
		sum += &grade;
		grade++;
	}
	return &grade/hwAmount_;
}

int Course::getCourseGrade() const
{
	return round((1-hwWeigh_)*examGrade_+hwWeigh_*getHwAverage());
}

Course :: ~Course()
{
	count_--;
}

bool Course::setExamGrade(int newExamGrade)
{
	if (newExamGrade > 100 || newExamGrade < 0)
		return 0;
	examGrade_ = newExamGrade;
	return 1;
}

bool Course::setHwGrade(int hwNum, int newHwGrade)
{
	if (newHwGrade > 100 || newHwGrade < 0)
		return 0;
	if (hwNum > hwAmount_)
		return 0;

	int* grade = hwGrade_;
	*(grade + hwNum) = newHwGrade;
	return 1;
}
