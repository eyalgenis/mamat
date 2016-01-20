#ifndef _COMPLEX_H_
#define _COMPLEX_H_
#include <cmath>
#include <iostream>

using namespace std;

class Complex
{
public:

	Complex() :
		re_(0.0), im_(0.0)
	{}

	Complex(double re) :
		re_(re), im_(0.0)
	{}

	Complex(double re, double im) :
		re_(re), im_(im)
	{}

	////*********************************************************************************************
	//// Name:           Complex Complex::operator+(const Complex& rhs);
	//// Description:    adds rhs  to this complex number
	//// Parameters:     const Complex& rhs - the complex number to add to this from the right
	//// Return value:   Complex result
	////*********************************************************************************************
	//Complex operator+(const Complex& rhs);

	////*********************************************************************************************
	//// Name:           Complex Complex::operator-(const Complex& rhs);
	//// Description:    subtracts rhs from this complex number
	//// Parameters:     const Complex& rhs - the complex number to subtract from this
	//// Return value:   Complex result
	////*********************************************************************************************
	//
	//Complex operator-(const Complex& rhs);

	////*********************************************************************************************
	//// Name:           Complex Complex::operator*(const Complex& rhs);
	//// Description:    multuplies this complex by rhs
	//// Parameters:     const Complex& rhs - the complex number multiply with this from the right
	//// Return value:   Complex result
	////*********************************************************************************************
	//
	//Complex operator*(const Complex& rhs);

	////*********************************************************************************************
	//// Name:           double Complex::get_Im() const
	//// Description:    returns imaginary part of this complex number
	//// Parameters:     none
	//// Return value:   double imag_ - the imaginary part of this complex number
	////*********************************************************************************************

	double getRE() const { return re_; } // INTERNAL
	double getIM() const { return im_; } // INTERNAL

	friend Complex operator+(const Complex &c1, const Complex &c2); // GLOBAL
	friend Complex operator-(const Complex &c1, const Complex &c2); // GLOBAL
	friend Complex operator*(const Complex &c1, const Complex &c2); // GLOBAL
	friend bool operator==(const Complex &c1, const Complex &c2); // GLOBAL
	friend double modulu(const Complex c); // GLOBAL
	friend ostream& operator<<(ostream &ro, const Complex &c); // GLOBAL

private:
	double re_;
	double im_;
};

#endif // _COMPLEX_H_