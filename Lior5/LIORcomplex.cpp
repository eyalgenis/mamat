#include "complex.h"
#include <iostream>
using namespace std;
//*********************************************************************************************
// Name:           Complex Complex::operator+(const Complex& rhs);
// Description:    adds rhs  to this complex number
// Parameters:     const Complex& rhs - the complex number to add to this from the right
// Return value:   Complex result
//*********************************************************************************************
Complex Complex::operator+(const Complex&  rhs)
{
	double result_real = real_ + rhs.real_;
	double result_imaginary = imag_ + rhs.imag_;
	return Complex(result_real, result_imaginary);
}
//*********************************************************************************************
// Name:           Complex Complex::operator-(const Complex& rhs);
// Description:    subtracts rhs from this complex number
// Parameters:     const Complex& rhs - the complex number to subtract from this
// Return value:   Complex result
//*********************************************************************************************
Complex Complex::operator-(const Complex & rhs)
{
	double result_real = real_ - rhs.real_;
	double result_imaginary = imag_ - rhs.imag_;
	return Complex(result_real, result_imaginary);
}
//*********************************************************************************************
// Name:           Complex Complex::operator*(const Complex& rhs);
// Description:    multuplies this complex by rhs
// Parameters:     const Complex& rhs - the complex number multiply with this from the right
// Return value:   Complex result
//*********************************************************************************************
Complex Complex::operator*(const Complex & rhs)
{
	double result_real = (real_ * rhs.real_) - (imag_ * rhs.imag_);
	double result_imaginary = (imag_ * rhs.real_) + (real_ * rhs.imag_);
	return Complex(result_real, result_imaginary);
}
//*********************************************************************************************
// Name:           Complex Complex::operator/(const Complex& rhs);
// Description:    divides this complex number by rhs
// Parameters:     const Complex& rhs - the complex number by which to divide
// Return value:   Complex result
//*********************************************************************************************
Complex Complex::operator/(const Complex & rhs)
{
	double result_real = ((real_ * rhs.real_) + (imag_ * rhs.imag_)) / ((rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_));
	double result_imaginary = ((rhs.real_ * imag_) - (real_ * rhs.imag_)) / ((rhs.real_ *rhs.real_) + (rhs.imag_ * rhs.imag_));
	return Complex(result_real, result_imaginary);
}



//*********************************************************************************************
// Name:           Complex operator+(const Complex  &num1, const Complex &num2);
// Description:    adds num1 and num2 and returns result
// Parameters:     const Complex& num1 - the lhs complex number
//				   const Complex& num2 - the rhs complex number
// Return value:   Complex result of addition of num1 and num2
//*********************************************************************************************
Complex operator+(const Complex  &num1, const Complex &num2)
{
	double result_real = num1.real_ + num2.real_;
	double result_imaginary = num1.imag_ + num2.imag_;
	return Complex(result_real, result_imaginary);
}
//*********************************************************************************************
// Name:           Complex operator-(const Complex  &num1, const Complex &num2);
// Description:    subtracts num2 from num 1 and returns result
// Parameters:     const Complex& num1 - the lhs complex number
//				   const Complex& num2 - the rhs complex number
// Return value:   Complex result of subtraction of num2 from num1
//*********************************************************************************************
Complex operator-(const Complex & num1, const Complex & num2)
{
	return Complex(num1.real_-num2.real_,num2.imag_-num2.imag_);
}
//*********************************************************************************************
// Name:           Complex operator*(const Complex  &num1, const Complex &num2);
// Description:    multiplies num1 by num2 and returns result
// Parameters:     const Complex& num1 - the lhs complex number
//				   const Complex& num2 - the rhs complex number
// Return value:   Complex result of product of num1 and num2
//*********************************************************************************************
Complex operator*(const Complex  &num1, const Complex &num2)
{
	double result_real = (num1.real_ * num2.real_) - (num1.imag_ * num2.imag_);
	double result_imaginary = (num1.imag_ * num2.real_) + (num1.real_ * num2.imag_);
	return Complex(result_real, result_imaginary);
}
//*********************************************************************************************
// Name:           Complex operator/(const Complex  &num1, const Complex &num2);
// Description:    divides num1 by num2
// Parameters:     const Complex& num1 - the lhs complex number
//				   const Complex& num2 - the rhs complex number
// Return value:   Complex result of divition of num2 by num1
//*********************************************************************************************
Complex operator/(const Complex & num1, const Complex & num2)
{
	double result_real = ((num1.real_ * num2.real_) + (num1.imag_ * num2.imag_))/((num2.real_ * num2.real_) + (num2.imag_ * num2.imag_));
	double result_imaginary = ((num2.real_ * num1.imag_) - (num1.real_ * num2.imag_)) / ((num2.real_ * num2.real_) + (num2.imag_ * num2.imag_));
	return Complex(result_real, result_imaginary);
}
//*********************************************************************************************
// Name:           bool operator==(const Complex  &num1, const Complex &num2);
// Description:    returns a boolean answer wheter num1 and num2 are identical
// Parameters:     const Complex& num1 - the lhs complex number
//				   const Complex& num2 - the rhs complex number
// Return value:   boolean answer - true - if the two number are identical
//								  - false- they are not
//*********************************************************************************************
bool operator==(const Complex & num1, const Complex & num2)
{
	return ((num1.real_ == num2.real_) && (num1.imag_ == num2.imag_));
}
//*********************************************************************************************
// Name:           ostream &operator<<(ostream &output, const Complex &num);
// Description:    overloads the << operator such that <<complex will print:
//				   <real_part> + <imaginary_part>i
// Parameters:     ostream &output - the channel for output
//				   const Complex& num - the complex number to be printed
// Return value:   ostream &output
//*********************************************************************************************
ostream& operator<<(ostream& out, const Complex &num)
{
	out << num.get_Real() << " + ";
	out << num.get_Im() << "i";
	return out;
}
//*********************************************************************************************
// Name:           double abs(const Complex num);
// Description:    computes the absolut value of complex number (sqrt(real^2 + imaginary^2))
// Parameters:     const Complex& num - the complex number to be printed
// Return value:   double abs - the absolut value of complex number num
//*********************************************************************************************
double abs(const Complex num)
{
	return sqrt(num.real_*num.real_ + num.imag_*num.imag_);
}

