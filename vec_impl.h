#ifndef _VEC_IMPL_H_
#define _VEC_IMPL_H_
#include <list>
#include <exception>
#include <iostream>
#include <cmath>
#include "complex.h"

//********************************************************************************************
// Name:           ExceptionWrongDimensions::what()
// Description:    dimenesions of operands don't match - illegal operation
// Parameters:     
// Return value:   
//********************************************************************************************
const char* ExceptionWrongDimensions::what() const throw()
{
	return "operand dimensions must agree";
}

//********************************************************************************************
// Name:           ExceptionEmptyOperand::what()
// Description:    this is an empty operand
// Parameters:     
// Return value:   
//********************************************************************************************
const char* ExceptionEmptyOperand::what() const throw()
{
	return "empty operand";
}

//********************************************************************************************
// Name:           ExceptionIndexExceed::what()
// Description:    access to index is illegal, index is out of definition
// Parameters:     
// Return value:   
//********************************************************************************************
const char* ExceptionIndexExceed::what() const throw()
{
	return "index exeeds operand dimensions";
}

//********************************************************************************************
// Name:           Vec<T>::Vec(const T& el) constructor
// Description:    initilize a vector with an element
// Parameters:     const T& el
// Return value:   
//********************************************************************************************
template<class T>
Vec<T>::Vec(const T & el)
{
	this->vals_.push_back(el);
}

//********************************************************************************************
// Name:           Vec<T>::push_back(T el)
// Description:    add element to the end of vector
// Parameters:     T el
// Return value:   
//********************************************************************************************
template<class T>
void Vec<T>::push_back(T el)
{
	vals_.push_back(el);
}

//********************************************************************************************
// Name:           unsigned int Vec<T>::size() const
// Description:    Calculates size of the vector
// Parameters:    
// Return value:   unsigned int vals_.size()
//********************************************************************************************
template<class T>
unsigned int Vec<T>::size() const
{
	return vals_.size();
}

//********************************************************************************************
// Name:           Vec<T>::operator+(const Vec & rhs) const
// Description:    Sum this vector with with rhs vector
// Parameters:     const Vec& rhs
// Return value:   Vec<T> new_vec
//********************************************************************************************
template<class T>
Vec<T> Vec<T>::operator+(const Vec & rhs) const
{
	ExceptionWrongDimensions e_dimensions;
	ExceptionEmptyOperand e_empty;
	
	Vec new_vec;
	if (this->vals_.size() != rhs.size()) // check vectors size equality
		throw (e_dimensions);
	if (this->vals_.size() == 0) // check not empty vector
		throw (e_empty);
	
	unsigned int i = 0;
	
	while (i < this->vals_.size()) { // sum & push till end of vector rechead
		new_vec.push_back((*this)[i] + rhs[i]);
		i++;
	}

	return new_vec;
}

//********************************************************************************************
// Name:           Vec<T>::operator*(const T & rhs) const
// Description:    Multiply this vector with a constant rhs
// Parameters:     const T & rhs
// Return value:   Vec<T> new_vec
//********************************************************************************************
template<class T>
Vec<T> Vec<T>::operator*(const T & rhs) const
{
	ExceptionEmptyOperand e_empty;

	if (this->size() == 0) // check not empty vector
		throw (e_empty); 
	
	Vec<T> new_vec;

	unsigned int i = 0;
	typename list<T>::const_iterator iter = this->begin();

	while (i < this->size()) { // multiply & push till end of vector rechead
		new_vec.push_back(rhs * (*iter));
		i++;
		iter++;
	}

	return new_vec;
}

//********************************************************************************************
// Name:           T & Vec<T>::operator[](unsigned int ind)
// Description:    Reach element in "ind" position in vector
// Parameters:     unsigned int ind
// Return value:   T& Element in ind position
//********************************************************************************************
template<class T>
T & Vec<T>::operator[](unsigned int ind)
{
	ExceptionIndexExceed e_exceed;
	if (ind >= this->vals_.size())
		throw(e_exceed);
	
	typename list<T>::iterator iter = vals_.begin();

	unsigned int i = 0;
	while (i < ind) {
		iter++;
		i++;
	}

	return (*iter);
}

//********************************************************************************************
// Name:           const T & Vec<T>::operator[](unsigned int ind) const
// Description:    Reach element in "ind" position in vector
// Parameters:     unsigned int ind
// Return value:   const T& Element in ind position
//********************************************************************************************
template<class T>
const T & Vec<T>::operator[](unsigned int ind) const
{
	ExceptionIndexExceed e_exceed;
	if (ind >= this->vals_.size())
		throw(e_exceed);

	typename list<T>::const_iterator iter = vals_.begin();

	unsigned int i = 0;
	while (i < ind) {
		iter++;
		i++;
	}

	return (*iter);
}

//********************************************************************************************
// Name:           Vec<T>::operator,(const Vec & rhs) const
// Description:    Concatanates this vector with rhs vector    
// Parameters:     const Vec & rhs
// Return value:   Vec<T> new_vec
//********************************************************************************************
template<class T>
Vec<T> Vec<T>::operator,(const Vec & rhs) const
{
//	ExceptionEmptyOperand e_empty;
//	if (rhs.size() == 0) // check not empty vector
//		throw (e_empty);

	Vec<T> new_vec;

	typename list<T>::const_iterator iter = this->begin();
	
	while (iter != this->end()) { // push back this vector to new vector
		new_vec.push_back(*iter);
		iter++;
	}

	iter = rhs.begin();
	while (iter != rhs.end()) { // push back rhs vector to new vector
		new_vec.push_back(*iter);
		iter++;
	}

	return new_vec;
}

//********************************************************************************************
// Name:           Vec<T>::operator,(const Vec & rhs) const
// Description:    Reach elements by "ind"s position given in vector and concatanates them to new vector
// Parameters:     const Vec<unsigned int>& ind
// Return value:   Vec<T> new_vec
//********************************************************************************************
template<class T>
Vec<T> Vec<T>::operator[](const Vec<unsigned int>& ind) const
{
	ExceptionIndexExceed e_exceed;
	ExceptionEmptyOperand e_empty;

	//if (ind.size() == 0) // check not empty vector
	//	throw (e_empty);

	Vec<T> new_vec;

	unsigned int i = 0;
	while (i < ind.size()) { // reach & push back till end of indexes vector rechead
		if (ind[i] >= this->size()) // check given index not exceeded vector size
			throw (e_exceed);

		new_vec.push_back((*this)[ind[i]]);
		i++;
	}

	return new_vec;
}

//********************************************************************************************
// Name:           Vec<T> operator*(const T & lhs, const Vec<T>& rhs)
// Description:    Multiply rhs vector with lhs factor
// Parameters:     const T & lhs, const Vec<T>& rhs
// Return value:   Vec<T> new_vec
//********************************************************************************************
template<class T>
Vec<T> operator*(const T & lhs, const Vec<T>& rhs)
{
	ExceptionEmptyOperand e_empty;

	Vec<T> new_vec;

	if (rhs.size() == 0) // check not empty vector
		throw (e_empty);

	unsigned int i = rhs.size();
	typename list<T>::const_iterator iter = rhs.begin();

	while (0 < i) { // multiply & push back till end of vector
		new_vec.push_back(lhs * (*iter));
		iter++;
		i--;
	}

	return new_vec;

}

//********************************************************************************************
// Name:           ostream & operator<<(ostream & ro, const Vec<T>& v)
// Description:    prints the vector by overloading << operator
// Parameters:     ostream & ro, const Vec<T>& v
// Return value:   ostream & ro
//********************************************************************************************
template<class T>
ostream & operator<<(ostream & ro, const Vec<T>& v)
{
	ExceptionEmptyOperand e_empty;

	if (v.size() == 0) // check not empty vector
		throw (e_empty);
	
	typename list<T>::const_iterator iter = v.begin();;

	ro << "(" << *iter;
	iter++;

	while (iter != v.end()) { // print till end of vector
		ro << ",\t" << *iter;
		iter++;
	}
	ro << ")";
	return ro;
}

//********************************************************************************************
// Name:           Vec<T> range(T start, unsigned int size)
// Description:    Creates new vector with n size (start , start+1, start+2 ... start+size-1)
// Parameters:     T start, unsigned int size
// Return value:   Vec<T> new_vec
//********************************************************************************************
template<class T>
Vec<T> range(T start, unsigned int size)
{
	Vec<T> new_vec;

	while (0 < size) { // push back till vector size reached
		new_vec.push_back(start);
		start = start+1;
		size--;
	}

	return new_vec;
}

//********************************************************************************************
// Name:           bool operator()(Vec<T>& lhs, Vec<T>& rhs) const
// Description:    Compare betweem lhs vector & rhs vector by infinity normal
// Parameters:     Vec<T>& lhs, Vec<T>& rhs
// Return value:   bool (lhs_norm < rhs_norm);
//********************************************************************************************
template<class T>
class norm_inf_comp {
public:
	bool operator()(Vec<T>& lhs, Vec<T>& rhs) const {

		ExceptionEmptyOperand e_empty;
		if (lhs.size() == 0 || rhs.size() == 0) // check not empty vectors
			throw (e_empty);	

		typename list<T>::const_iterator iter = lhs.begin();

		double lhs_norm = 0;
		double rhs_norm = 0;

		while (iter != lhs.end()) { // calculate infinity normal for lhs
			if (lhs_norm < (double)abs(*iter))
				lhs_norm = (double)abs(*iter);
			iter++;
		}

		iter = rhs.begin();

		while (iter != rhs.end()) { // calculate infinity normal for rhs
			if (rhs_norm < (double)abs(*iter))
				rhs_norm = (double)abs(*iter);
			iter++;
		}

		return (lhs_norm < rhs_norm);
	}
};

#endif // _VEC_IMPL_H_