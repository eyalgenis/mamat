#include "Complex.h"
#include <iostream>

using namespace std;

//********************************************************************************************
// Function Name:  operator+
// Description:    operator+ overload for complex numbers addition (GLOBAL FRIEND function for the class)
// Parameters:     
//		c1 (Complex&) - lhs complex number
//		c2 (Complex&) - rhs complex number
// Return value:   Complex - summary result
//********************************************************************************************
Complex operator+(const Complex& c1, const Complex& c2)
{
	double resRE = c1.re_+c2.re_;
	double resIM = c1.im_+c2.im_;

	return Complex(resRE, resIM);
}

//********************************************************************************************
// Function Name:  operator-
// Description:    operator- overload for complex numbers subtraction (GLOBAL FRIEND function for the class)
// Parameters:     
//		c1 (Complex&) - lhs complex number
//		c2 (Complex&) - rhs complex number
// Return value:   Complex - subtraction result
//********************************************************************************************
Complex operator-(const Complex& c1, const Complex& c2)
{
	double resRE = c1.re_-c2.re_;
	double resIM = c1.im_-c2.im_;

	return Complex(resRE, resIM);
}

//********************************************************************************************
// Function Name:  operator*
// Description:    operator* overload for complex numbers multiplication (GLOBAL FRIEND function for the class)
// Parameters:     
//		c1 (Complex&) - lhs complex number
//		c2 (Complex&) - rhs complex number
// Return value:   Complex - multiplication result
//********************************************************************************************
Complex operator*(const Complex& c1, const Complex& c2)
{
	double resRE = (c1.re_*c2.re_) - (c1.im_*c2.im_);
	double resIM = (c1.im_*c2.re_) + (c1.re_*c2.im_);

	return Complex(resRE, resIM);
}

//********************************************************************************************
// Function Name:  operator==
// Description:    operator== overload for complex numbers comparison (GLOBAL FRIEND function for the class)
// Parameters:     
//		c1 (Complex&) - lhs complex number
//		c2 (Complex&) - rhs complex number
// Return value:   true if they're equal, otherwise false
//********************************************************************************************
bool operator==(const Complex & c1, const Complex & c2)
{
	if ((c1.re_==c2.re_) && (c1.im_==c2.im_))
		return true;

	return false;
}

//********************************************************************************************
// Function Name:  modulu
// Description:    calculates the modulu of a complex number (GLOBAL FRIEND function for the class)
// Parameters:     
//		c (Complex&) - complex number
// Return value:   modulu of the complex number
//********************************************************************************************
double modulu(const Complex c) // GLOBAL FRIEND
{
	double res = sqrt(c.re_*c.re_ + c.im_*c.im_);

	return res;
}

//********************************************************************************************
// Function Name:  operator<<     
// Description:    operator<< overload for printing to standart output a complex number (GLOBAL FRIEND function for the class)
// Parameters:     
//		ro (ostream&) - output stream
//		c (Complex&) - complex number
// Return value:   ro - updated output stream
//********************************************************************************************
ostream& operator<<(ostream &ro, const Complex &c)
{
	ro << c.getRE() << " + ";
	ro << c.getIM() << "i";

	return ro;
}