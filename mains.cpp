#include "Course.H"
#include "EE_Course.H"
#include "CS_Course.H"
#include "STUDENT.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>
using namespace std;

int main () {
	int a;
	

	CS_Course cs_course(234117, "Madmach2", 4, 0.5, true, "sefer");
	cout << "cs_course number: " << cs_course.getNum() << endl;
	cout << "cs_course name: " << cs_course.getName() << endl;
	cout << "hw average: " << cs_course.getHwAverage() << endl;
	cout << "hm amount: " << cs_course.getHwNum() << endl;
	cout << "hw 2 grade: " << cs_course.getHwGrade(2) << endl;
	cout << "exam grade: " << cs_course.getExamGrade() << endl;
	cout << "hw weigh: " << cs_course.getHwWeigh() << endl;

	if (cs_course.setExamGrade(80))
		cout << "exam grade: " << cs_course.getExamGrade() << endl;

	if (cs_course.setHwGrade(2, 70))
		cout << "hw 2 grade: " << cs_course.getHwGrade(2) << endl;

	cout << "hw average: " << cs_course.getHwAverage() << endl;
	cout << "cs_course grade: " << cs_course.getCourseGrade() << endl;

	cout << "cs_course hw takef? " << cs_course.isTakef() << endl;
	cout << "cs_course book: " << cs_course.getBook() << endl;

	if(cs_course.setTakef(false))
		cout << "cs_course grade: " << cs_course.getCourseGrade() << endl;

	cout << "cs_course hw takef? " << cs_course.isTakef() << endl;

	if (cs_course.setBook("Algebra"))
		cout << "cs_course book: " << cs_course.getBook() << endl;


	//EE_Course pmamat(44101, "mamat", 4, 0.3);
	//cout << "ee_course number: " << ee_course.getNum() << endl;
	//cout << "ee_course name: " << ee_course.getName() << endl;
	//cout << "hw average: " << ee_course.getHwAverage() << endl;
	//cout << "hm amount: " << ee_course.getHwNum() << endl;
	//cout << "hw 2 grade: " << ee_course.getHwGrade(2) << endl;
	//cout << "exam grade: " << ee_course.getExamGrade() << endl;
	//cout << "hw weigh: " << ee_course.getHwWeigh() << endl;

	//if (ee_course.setExamGrade(80))
	//	cout << "exam grade: " << ee_course.getExamGrade() << endl;

	//if (ee_course.setHwGrade(2, 70))
	//	cout << "hw 2 grade: " << ee_course.getHwGrade(2) << endl;

	//cout << "hw average: " << ee_course.getHwAverage() << endl;
	//cout << "ee_course grade: " << ee_course.getCourseGrade() << endl;

	//if (ee_course.setFactor(10))
	//	cout << "ee_course grade: " << ee_course.getCourseGrade() << endl;


	Student eyal(6059615, "eyal");
//	Student saba(5997925, "saba");
	EE_Course* pmamat = new EE_Course(44101, "mamat", 4, 0.3);
	eyal.addEE_Course(pmamat);
	pmamat->setExamGrade(80);
	pmamat->setHwGrade(1, 70);
	//saba.addEE_Course(pmamat);
	
	eyal.print();

	scanf_s("%d", &a);
	return 1;
}