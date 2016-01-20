#ifndef _COMPLEX_H_
#define _COMPLEX_H_
#include <cmath>
#include <iostream>

using namespace std;
class Complex
{

	
public:
	//*********************************************************************************************
	// Name:           constructor Complex::Complex(double r, double i)          
	// Description:    receives real and imaginary parts and constructs a complex
	// Parameters:     double r - real part
	//			       double i -  imaginary part
	// Return value:   Complex
	//*********************************************************************************************
	Complex(double r, double i) : real_(r), imag_(i) {};
	//*********************************************************************************************
	// Name:           constructor Complex::Complex(double r)
	// Description:    receives real part and assumes imaginary is 0
	// Parameters:     double r - real part
	// Return value:   Complex
	//*********************************************************************************************
	Complex(double r) : real_(r), imag_(0.0) {};
	//*********************************************************************************************
	// Name:           constructor Complex::Complex()
	// Description:    initializes a Complex as zero
	// Parameters:     none
	// Return value:   Complex
	//*********************************************************************************************
	Complex() : real_(0.0), imag_(0.0) {};
	
	
	//*********************************************************************************************
	// Name:           Complex Complex::operator+(const Complex& rhs);
	// Description:    adds rhs  to this complex number
	// Parameters:     const Complex& rhs - the complex number to add to this from the right
	// Return value:   Complex result
	//*********************************************************************************************
	Complex operator+(const Complex& rhs);
	//*********************************************************************************************
	// Name:           Complex Complex::operator-(const Complex& rhs);
	// Description:    subtracts rhs from this complex number
	// Parameters:     const Complex& rhs - the complex number to subtract from this
	// Return value:   Complex result
	//*********************************************************************************************
	Complex operator-(const Complex& rhs);
	//*********************************************************************************************
	// Name:           Complex Complex::operator*(const Complex& rhs);
	// Description:    multuplies this complex by rhs
	// Parameters:     const Complex& rhs - the complex number multiply with this from the right
	// Return value:   Complex result
	//*********************************************************************************************
	Complex operator*(const Complex& rhs);
	//*********************************************************************************************
	// Name:           Complex Complex::operator/(const Complex& rhs);
	// Description:    divides this complex number by rhs
	// Parameters:     const Complex& rhs - the complex number by which to divide
	// Return value:   Complex result
	//*********************************************************************************************
	Complex operator/(const Complex& rhs);





	//*********************************************************************************************
	// Name:           double Complex::get_Im() const
	// Description:    returns imaginary part of this complex number
	// Parameters:     none
	// Return value:   double imag_ - the imaginary part of this complex number
	//*********************************************************************************************
	double get_Im() const { return imag_; }
	//*********************************************************************************************
	// Name:           double Complex::get_Real() const
	// Description:    returns Real part of this complex number
	// Parameters:     none
	// Return value:   double real_ - the Real part of this complex number
	//*********************************************************************************************
	double get_Real() const { return real_; }



	//*********************************************************************************************
	// Name:           Complex operator+(const Complex  &num1, const Complex &num2);
	// Description:    adds num1 and num2 and returns result
	// Parameters:     const Complex& num1 - the lhs complex number
	//				   const Complex& num2 - the rhs complex number
	// Return value:   Complex result of addition of num1 and num2
	//*********************************************************************************************
	friend Complex operator+(const Complex  &num1, const Complex &num2);
	//*********************************************************************************************
	// Name:           Complex operator-(const Complex  &num1, const Complex &num2);
	// Description:    subtracts num2 from num 1 and returns result
	// Parameters:     const Complex& num1 - the lhs complex number
	//				   const Complex& num2 - the rhs complex number
	// Return value:   Complex result of subtraction of num2 from num1
	//*********************************************************************************************
	friend Complex operator-(const Complex  &num1, const Complex &num2);
	//*********************************************************************************************
	// Name:           Complex operator*(const Complex  &num1, const Complex &num2);
	// Description:    multiplies num1 by num2 and returns result
	// Parameters:     const Complex& num1 - the lhs complex number
	//				   const Complex& num2 - the rhs complex number
	// Return value:   Complex result of product of num1 and num2
	//*********************************************************************************************
	friend Complex operator*(const Complex  &num1, const Complex &num2);
	//*********************************************************************************************
	// Name:           Complex operator/(const Complex  &num1, const Complex &num2);
	// Description:    divides num1 by num2
	// Parameters:     const Complex& num1 - the lhs complex number
	//				   const Complex& num2 - the rhs complex number
	// Return value:   Complex result of divition of num2 by num1
	//*********************************************************************************************
	friend Complex operator/(const Complex  &num1, const Complex &num2);
	//*********************************************************************************************
	// Name:           bool operator==(const Complex  &num1, const Complex &num2);
	// Description:    returns a boolean answer wheter num1 and num2 are identical
	// Parameters:     const Complex& num1 - the lhs complex number
	//				   const Complex& num2 - the rhs complex number
	// Return value:   boolean answer - true - if the two number are identical
	//								  - false- they are not
	//*********************************************************************************************
	friend bool operator==(const Complex  &num1, const Complex &num2);
	//*********************************************************************************************
	// Name:           ostream &operator<<(ostream &output, const Complex &num);
	// Description:    overloads the << operator such that <<complex will print:
	//				   <real_part> + <imaginary_part>i
	// Parameters:     ostream &output - the channel for output
	//				   const Complex& num - the complex number to be printed
	// Return value:   ostream &output
	//*********************************************************************************************
	friend ostream &operator<<(ostream &output, const Complex &num);
	//*********************************************************************************************
	// Name:           double abs(const Complex num);
	// Description:    computes the absolut value of complex number (sqrt(real^2 + imaginary^2))
	// Parameters:     const Complex& num - the complex number to be printed
	// Return value:   double abs - the absolut value of complex number num
	//*********************************************************************************************
	friend double abs(const Complex num);
	private:
	double real_;
	double imag_;
};










#endif // _COMPLEX_H_
