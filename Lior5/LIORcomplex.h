#ifndef _COMPLEX_H_
#define _COMPLEX_H_
#include <cmath>
#include <iostream>

using namespace std;
class Complex
{

	
public:
	Complex(double r, double i) : real_(r), imag_(i) {};
	Complex(double r) : real_(r), imag_(0.0) {};
	Complex() : real_(0.0), imag_(0.0) {};
	Complex operator+(const Complex& other);
	Complex operator-(const Complex& other);
	Complex operator*(const Complex& other);
	Complex operator/(const Complex& other);


	double get_Im() const { return imag_; }
	double get_Real() const { return real_; }

	friend Complex operator+(const Complex  &num1, const Complex &num2);
	friend Complex operator*(const Complex  &num1, const Complex &num2);
	friend Complex operator/(const Complex  &num1, const Complex &num2);
	friend bool operator==(const Complex  &num1, const Complex &num2);

	friend std::ostream &operator<<(std::ostream &output, const Complex &num);
	friend double abs(const Complex num);
	private:
	double real_;
	double imag_;
};










#endif // _COMPLEX_H_
