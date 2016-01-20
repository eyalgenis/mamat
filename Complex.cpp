#include "complex.h"
#include <iostream>

using namespace std;


//Complex Complex::operator+(const Complex&  rhs)
//{
//	double resRE = re_ + rhs.re_;
//	double resIM = im_ + rhs.im_;
//	return Complex(resRE, resIM);
//}


//Complex Complex::operator-(const Complex & rhs)
//{
//	double resRE = re_ - rhs.re_;
//	double resIM = im_ - rhs.im_;
//	return Complex(resRE, resIM);
//}


//Complex Complex::operator*(const Complex & rhs)
//{
//	double resRE = (re_ * rhs.re_) - (im_ * rhs.im_);
//	double resIM = (im_ * rhs.re_) + (re_ * rhs.im_);
//	return Complex(resRE, resIM);
//}

Complex operator+(const Complex &c1, const Complex &c2) // GLOBAL
{
	double resRE = c1.re_ + c2.re_;
	double resIM = c1.im_ + c2.im_;

	return Complex(resRE, resIM);
}


Complex operator-(const Complex & c1, const Complex & c2) // GLOBAL
{
	double resRE = c1.re_ - c2.re_;
	double resIM = c1.im_ - c2.im_;

	return Complex(resRE, resIM);
}


Complex operator*(const Complex  &c1, const Complex &c2) // GLOBAL
{
	double resRE = (c1.re_ * c2.re_) - (c1.im_ * c2.im_);
	double resIM = (c1.im_ * c2.re_) + (c1.re_ * c2.im_);

	return Complex(resRE, resIM);
}


//*********************************************************************************************
bool operator==(const Complex & c1, const Complex & c2) // GLOBAL
{
	if ((c1.re_ == c2.re_) && (c1.im_ == c2.im_))
		return true;

	return false;
}


double modulu(const Complex num) // GLOBAL
{
	double res = sqrt(num.re_*num.re_ + num.im_*num.im_);

	return res;
}


ostream& operator<<(ostream &ro, const Complex &c) // GLOBAL
{
	ro << c.getRE() << " + ";
	ro << c.getIM() << "i";

	return ro;
}