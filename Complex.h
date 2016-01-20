#ifndef _COMPLEX_H_
#define _COMPLEX_H_
#include <cmath>
#include <iostream>

using namespace std;

class Complex
{
public:

	//********************************************************************************************
	// Function Name:  Complex (constructor) 
	// Description:    Creates a new complex number and initializes both its real and imaginery parts to 0
	// Parameters:	   None
	// Return value:   Newly created complex number
	//********************************************************************************************
	Complex() :
		re_(0.0), im_(0.0)
	{}

	//********************************************************************************************
	// Function Name:  Complex (constructor) 
	// Description:    Creates a new complex number and initializes its real part from input and imaginery part to 0
	// Parameters:	   None
	// Return value:   Newly created complex number
	//********************************************************************************************
	Complex(double re) :
		re_(re), im_(0.0)
	{}

	//********************************************************************************************
	// Function Name:  Complex (constructor) 
	// Description:    Creates a new complex number and initializes both its real and imaginery parts from input
	// Parameters:	   None
	// Return value:   Newly created complex number
	//********************************************************************************************
	Complex(double re, double im) :
		re_(re), im_(im)
	{}

	//********************************************************************************************
	// Function Name:  getRE 
	// Description:    returns the real part of the class' complex number (MEMBER function)
	// Parameters:	   None
	// Return value:   re_ (double) - real part of the class' complex number
	//********************************************************************************************
	double getRE() const { return re_; }
	double getIM() const { return im_; }

	//********************************************************************************************
	// Function Name:  getIM 
	// Description:    returns the imaginary part of the class' complex number (MEMBER function)
	// Parameters:	   None
	// Return value:   im_ (double) - imaginary part of the class' complex number
	//********************************************************************************************
	friend Complex operator+(const Complex &c1, const Complex &c2);

	//********************************************************************************************
	// Function Name:  operator-
	// Description:    operator- overload for complex numbers subtraction (GLOBAL FRIEND function for the class)
	// Parameters:     
	//		c1 (Complex&) - lhs complex number
	//		c2 (Complex&) - rhs complex number
	// Return value:   Complex - subtraction result
	//********************************************************************************************
	friend Complex operator-(const Complex &c1, const Complex &c2);

	//********************************************************************************************
	// Function Name:  operator*
	// Description:    operator* overload for complex numbers multiplication (GLOBAL FRIEND function for the class)
	// Parameters:     
	//		c1 (Complex&) - lhs complex number
	//		c2 (Complex&) - rhs complex number
	// Return value:   Complex - multiplication result
	//********************************************************************************************
	friend Complex operator*(const Complex &c1, const Complex &c2);

	//********************************************************************************************
	// Function Name:  operator==
	// Description:    operator== overload for complex numbers comparison (GLOBAL FRIEND function for the class)
	// Parameters:     
	//		c1 (Complex&) - lhs complex number
	//		c2 (Complex&) - rhs complex number
	// Return value:   true if they're equal, otherwise false
	//********************************************************************************************
	friend bool operator==(const Complex &c1, const Complex &c2);

	//********************************************************************************************
	// Function Name:  modulu
	// Description:    calculates the modulu of a complex number (GLOBAL FRIEND function for the class)
	// Parameters:     
	//		c (Complex&) - complex number
	// Return value:   modulu of the complex number
	//********************************************************************************************
	friend double modulu(const Complex c);

	//********************************************************************************************
	// Function Name:  operator<<     
	// Description:    operator<< overload for printing to standart output a complex number (GLOBAL function for the class)
	// Parameters:     
	//		ro (ostream&) - output stream
	//		c (Complex&) - complex number
	// Return value:   ro - updated output stream
	//********************************************************************************************
	friend ostream& operator<<(ostream &ro, const Complex &c);

private:
	double re_;
	double im_;
};

#endif // _COMPLEX_H_