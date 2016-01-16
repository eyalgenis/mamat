#include "complex.h"
#include <iostream>
using namespace std;
Complex Complex::operator+(const Complex&  other)
{
	double result_real = real_ + other.real_;
	double result_imag_inary = imag_ + other.imag_;
	return Complex(result_real, result_imag_inary);
}
Complex Complex::operator-(const Complex & other)
{
	double result_real = real_ - other.real_;
	double result_imaginary = imag_ - other.imag_;
	return Complex(result_real, result_imaginary);
}
Complex Complex::operator*(const Complex & other)
{
	double result_real = (real_ * other.real_) - (imag_ * other.imag_);
	double result_imaginary = (imag_ * other.real_) + (real_ * other.imag_);
	return Complex(result_real, result_imaginary);
}
Complex Complex::operator/(const Complex & other)
{
	double result_real = ((real_ * other.real_) + (imag_ * other.imag_)) / ((other.real_ * other.real_) + (other.imag_ * other.imag_));
	double result_imaginary = ((other.real_ * imag_) - (real_ * other.imag_)) / ((other.real_ *other.real_) + (other.imag_ * other.imag_));
	return Complex(result_real, result_imaginary);
}
Complex operator+(const Complex  &num1, const Complex &num2)
{
	double result_real = num1.real_ + num2.real_;
	double result_imaginary = num1.imag_ + num2.imag_;
	return Complex(result_real, result_imaginary);
}
Complex operator*(const Complex  &num1, const Complex &num2)
{
	double result_real = (num1.real_ * num2.real_) - (num1.imag_ * num2.imag_);
	double result_imaginary = (num1.imag_ * num2.real_) + (num1.real_ * num2.imag_);
	return Complex(result_real, result_imaginary);
}

Complex operator/(const Complex & num1, const Complex & num2)
{
	double result_real = ((num1.real_ * num2.real_) + (num1.imag_ * num2.imag_))/((num2.real_ * num2.real_) + (num2.imag_ * num2.imag_));
	double result_imaginary = ((num2.real_ * num1.imag_) - (num1.real_ * num2.imag_)) / ((num2.real_ * num2.real_) + (num2.imag_ * num2.imag_));
	return Complex(result_real, result_imaginary);
}

bool operator==(const Complex & num1, const Complex & num2)
{
	return ((num1.real_ == num2.real_) && (num1.imag_ == num2.imag_));
}

std::ostream& operator<<(ostream& out, const Complex &num)
{
	out << num.get_Real() << " + ";
	out << num.get_Im() << "i";
	return out;
}

double abs(const Complex num)
{
	return sqrt(num.real_*num.real_ + num.imag_*num.imag_);
}

