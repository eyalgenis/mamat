#ifndef _VEC_IMPL_H_
#define _VEC_IMPL_H_
#include <list>
#include <exception>
#include <iostream>
#include <cmath>
#include "complex.h"
//*********************************************************************************************
// Name:           ExceptionWrongDimensions::what()
// Description:    illegal operation, dimenesions of operands don't match
// Parameters:     none
// Return value:   none
//*********************************************************************************************
const char* ExceptionWrongDimensions::what() const throw()
{
	return "operand dimensions must agree";
}
//*********************************************************************************************
// Name:           ExceptionEmptyOperand::what()
// Description:    an empty operand has been used
// Parameters:     none
// Return value:   none
//*********************************************************************************************
const char* ExceptionEmptyOperand::what() const throw()
{
	return "empty operand";
}
//*********************************************************************************************
// Name:           ExceptionIndexExceed::what()
// Description:    trying to access index outside of boundries
// Parameters:     none
// Return value:   none
//*********************************************************************************************
const char* ExceptionIndexExceed::what() const throw()
{
	return "index exeeds operand dimensions";
}
using namespace std;


//*********************************************************************************************
// Name:           Vec<T>::Vec(const T& el) constructor
// Description:    initilize a vector with this element
// Parameters:     const T& el
// Return value:   none
//*********************************************************************************************
template <class T>
Vec<T>::Vec(const T& el): Vec<T>()
{
	vals_.push_back(el);
}
//*********************************************************************************************
// Name:           Vec<T>::push_back(T el)                               
// Description:    Adding new element el to the vector first position
// Parameters:     T el
// Return value:   none
//*********************************************************************************************
template<class T>
void Vec<T>::push_back(T el)
{
	vals_.push_back(el);
}
//*********************************************************************************************
// Name:           Vec<T>::size() const                              
// Description:    Returns vector size
// Parameters:     none
// Return value:   unsigned int vals_.size()
//*********************************************************************************************
template<class T>
unsigned int Vec<T>::size() const
{
	return vals_.size();
}
//*********************************************************************************************
// Name:           Vec<T>::operator+(const Vec& rhs) const 
// Description:    Adds element by element this vector with rhs vector
// Parameters:     const Vec& rhs
// Return value:   vec<T> result_vector
//*********************************************************************************************

template<class T>
Vec<T> Vec<T>::operator+(const Vec& rhs) const
{
	Vec result_vector;
	ExceptionWrongDimensions e_wrong_dim;
	ExceptionEmptyOperand e_empty_op;
	if (this->vals_.size() != rhs.size())
	{
		throw (e_wrong_dim);
	}
	if (rhs.size() == 0)//includes the check that both are empty, due to previous check
	{
		throw (e_empty_op);// ExceptionEmptyOperand;
	}
	for (unsigned int i = 0; i < rhs.size(); i++)
	{
		result_vector.push_back((*this)[i] + rhs[i]);
	}
	return result_vector;
}


//*********************************************************************************************
// Name:           Vec<T>::operator*(const T& rhs) const                                   
// Description:    multiply every element of the vector by rhs(a scalar)
// Parameters:     const T& rhs
// Return value:   Vec<T> result_vector
//*********************************************************************************************
template<class T>
Vec<T> Vec<T>::operator*(const T& rhs) const
{
	Vec result_vector;
	typename list<T>::const_iterator it;
	for (it = vals_.begin(); it != vals_.end(); it++)
	{
		result_vector.push_back((*it)*rhs);
	}
	return result_vector;
}
//*********************************************************************************************
// Name:           T& Vec<T>::operator[](unsigned int ind)                             
// Description:    returns the element in the ind'th position of the vector
// Parameters:     unsigned int ind
// Return value:   T& element in ind'th position
//*********************************************************************************************
template<class T>
T& Vec<T>::operator[](unsigned int ind)                             
{
	ExceptionIndexExceed e_index_exceed;
	ExceptionEmptyOperand e_empty_operand;
	if (ind > vals_.size())
	{
		throw (e_index_exceed);
	}
	if (this->size() == 0)
	{
		throw (e_empty_operand);
	}
	typename list<T>::const_iterator it = vals_.begin();
	for (unsigned int i = 0; i < ind; i++) 
	{
		it++;
	}
	return const_cast<T&>(*it);
}
//*********************************************************************************************
// Name:           T& Vec<T>::operator[](unsigned int ind)                             
// Description:    returns the element in the ind'th position of the vector
// Parameters:     unsigned int ind
// Return value:   T& element in ind'th position
//*********************************************************************************************
template<class T>
const T& Vec<T>::operator[](unsigned int ind) const
{
	ExceptionIndexExceed e_index_exceed;
	if (ind >= vals_.size())
	{
		throw (e_index_exceed);
	}
	typename list<T>::const_iterator it = vals_.begin();
	for (unsigned int i = 0; i < ind; i++)
	{
		it++;
	}
	return *it;
}
template<class T>
//*********************************************************************************************
// Name:         Vec<T>::operator,(const Vec& rhs) const                                   
// Description:  concatanates two input vectors and return them as result vector    
// Parameters:   const Vec& rhs  
// Return value: Vec<T> result vector
//*********************************************************************************************
Vec<T> Vec<T>::operator,(const Vec& rhs) const
{
	ExceptionEmptyOperand e_empty_op;
	Vec<T> result_vec;
	typename list<T>::const_iterator it;
	if (rhs.size() == 0)
	{
		throw (e_empty_op);
	}
	it = this->vals_.begin();
	for (it = vals_.begin(); it != vals_.end(); it++)
	{
		result_vec.push_back(*it);
	}
	for (it = rhs.begin(); it != rhs.end(); it++)
	{
		result_vec.push_back(*it);
	}
	return result_vec;
}
template<class T>
//*********************************************************************************************
// Name:           T& Vec<T>::operator[](const Vec<unsigned int>& ind) const                             
// Description:    returns a vector of the elements in the positions stated by the ind vector
// Parameters:     const Vec<unsigned int>& ind
// Return value:   Vec<T> result_vector
//*********************************************************************************************
Vec<T> Vec<T>::operator[](const Vec<unsigned int>& ind) const
{
	ExceptionIndexExceed e_index_exceed;
	Vec result_vector;
	typename list<T>::const_iterator it;
	typename list<T>::const_iterator it_per_element;
	unsigned int size_of_vector = this->vals_.size();
	for (unsigned int i = 0; i < ind.size(); i++)
	{
		if (ind[i] >= size_of_vector)
		{
			throw (e_index_exceed);// ExceptionIndexExceed
		}
		result_vector.push_back((*this)[ind[i]]);
	}
	return result_vector;
}
//*********************************************************************************************
// Name:		  operator*(const T & lhs, const Vec<T>& rhs)                                     
// Description:   multiply every element of the vector by lhs(a scalar)
// Parameters:    const T & lhs -scalar , const Vec<T>& rhs - vector
// Return value:  result_vector
//*********************************************************************************************
template<class T>
Vec<T> operator*(const T & lhs, const Vec<T>& rhs)
{
	ExceptionEmptyOperand e_empty_op;
	Vec<T> result_vector;
	typename list<T>::const_iterator it;
	if (rhs.size() == 0)
	{
		throw (e_empty_op);
	}
	for (unsigned int i = 0; i < rhs.size(); i++)
	{
		result_vector.push_back(lhs*rhs[i]);
	}
	return result_vector;
}
//*********************************************************************************************
// Name:           ostream & operator<<(ostream & ro, const Vec<T>& v)            
// Description:    outputs the vector to ostream in this pattern by overloading the << operator
//				   (first_element,	second_element,	.......,	last_element)
// Parameters:     ostream & ro, const Vec<T>& v
// Return value:   ro
//*********************************************************************************************
template<class T>
ostream & operator<<(ostream & ro, const Vec<T>& v)
{
	ExceptionEmptyOperand e_empty_op;
	if (v.size() == 0)
	{
		throw (e_empty_op);// ExceptionEmptyOperand;
	}
	typename list<T>::const_iterator it;
	ro << "(" << *v.begin();
	it = v.begin();
	it++;
	for (it = it; it != v.end(); it++)
	{
		ro << ",\t" << *it;
	}
	ro << ")";
	return ro;
}
//*********************************************************************************************
// Name:           range(T start, unsigned int size)            
// Description:    returns a vector with size size in which the first element is start
//				   and each element is larger than it's former by 1
// Parameters:     T start, unsigned int size
// Return value:   new_vec
//*********************************************************************************************
template<class T>
Vec<T> range(T start, unsigned int size)
{
	Vec<T> new_vec;
	for (unsigned int i = 0; i < size; i++)
	{
		new_vec.push_back(start + i);
	}
	return new_vec;
}

	
template<class T>
class norm_inf_comp {
public:
	bool operator()(Vec<T>& lhs, Vec<T>& rhs) const
	{
		typename list<T>::const_iterator it;
		ExceptionEmptyOperand e_empty_op;
		if (lhs.size() == 0 || rhs.size() == 0)
		{
			throw (e_empty_op);// ExceptionEmptyOperand;
		}

		double inf_norm_lhs = 0, inf_norm_rhs = 0;
		it = lhs.begin();
		while (it != lhs.end())
		{
			inf_norm_lhs = inf_norm_lhs > (double)abs(*it) ? inf_norm_lhs : (double)abs(*it);
			it++;
		}
		it = rhs.begin();
		while (it != rhs.end())
		{
			inf_norm_rhs = inf_norm_rhs > (double)abs(*it) ? inf_norm_rhs : (double)abs(*it);
			it++;
		}
		return (inf_norm_lhs < inf_norm_rhs);
	}
};










#endif // _VEC_IMPL_H_