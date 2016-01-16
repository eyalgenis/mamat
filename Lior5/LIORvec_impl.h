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
// Name:           Vec<T>::Vec(const T& el)
// Description:    trying to access index outside of boundries
// Parameters:     none
// Return value:   none
//*********************************************************************************************
template <class T>
Vec<T>::Vec(const T& el)
{
	vals_.push_back(el);
}
//*********************************************************************************************
// Name:           Vec<T>::push_back(T el)                               
// Description:    Adding new el to the vec first bit
// Parameters:     none
// Return value:   none
//*********************************************************************************************
template<class T>
void Vec<T>::push_back(T el)
{
	vals_.push_back(el);
}
//*********************************************************************************************
// Name:           Vec<T>::size() const                              
// Description:    Returns vec size
// Parameters:     none
// Return value:   vals_.size()
//*********************************************************************************************

template<class T>
unsigned int Vec<T>::size() const
{
	return vals_.size();
}
//*********************************************************************************************
// Name:          Vec<T>::operator+(const Vec& rhs) const 
// Description:    Adds rhs (scalar) to evert elm in vector
// Parameters:     rhs
// Return value:   result_vector
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
// Description:    multiplay rhs (scalar) to evert elm in vector
// Parameters:     rhs
// Return value:   result_vector
//*********************************************************************************************

template<class T>
Vec<T> Vec<T>::operator*(const T& rhs) const
{
	Vec result_vector;
	list<T>::const_iterator it;
	for (it = vals_.begin(); it != vals_.end(); it++)
	{
		result_vector.push_back((*it)*rhs);
	}
	return result_vector;
}


//*********************************************************************************************
// Name:           T& Vec<T>::operator[](unsigned int ind)                             
// Description:    multiplay rhs (scalar) to every element in this vector
// Parameters:     rhs
// Return value:   result_vector
//*********************************************************************************************

template<class T>
T& Vec<T>::operator[](unsigned int ind)                             
{
	ExceptionIndexExceed e_index_exceed;
	if (ind > vals_.size())
	{
		throw (e_index_exceed);
	}
	list<T>::const_iterator it = vals_.begin();
	for (unsigned int i = 0; i < ind; i++, it++) {}
	return const_cast<T&>(*it);
}

//*********************************************************************************************
// Name:           T& Vec<T>::operator[](unsigned int ind                                 -matan
// Description:    multiplay rhs (scalar) to every element in this vector
// Parameters:     rhs
// Return value:   result_vector
//*********************************************************************************************

template<class T>
const T& Vec<T>::operator[](unsigned int ind) const
{
	ExceptionIndexExceed e_index_exceed;
	if (ind > vals_.size())
	{
		throw (e_index_exceed);
	}
	list<T>::const_iterator it = vals_.begin();
	for (unsigned int i = 0; i < ind; i++, it++) {}
	return *it;
}
template<class T>
Vec<T> Vec<T>::operator,(const Vec& rhs) const
{
	ExceptionEmptyOperand e_empty_op;
	Vec<T> new_vec;
	list<T>::const_iterator it;
	if (rhs.size() == 0)
	{
		throw (e_empty_op);
	}
	it = this->vals_.begin();
	for (it = vals_.begin(); it != vals_.end(); it++)
	{
		new_vec.push_back(*it);
	}
	for (it = rhs.begin(); it != rhs.end(); it++)
	{
		new_vec.push_back(*it);
	}
	return new_vec;

}
template<class T>
Vec<T> Vec<T>::operator[](const Vec<unsigned int>& ind) const
{
	ExceptionIndexExceed e_index_exceed;
	Vec result_vector;
	list<T>::const_iterator it;
	list<T>::const_iterator it_per_element;
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

template<class T>
Vec<T> operator*(const T & lhs, const Vec<T>& rhs)
{
	ExceptionEmptyOperand e_empty_op;
	Vec<T> result_vector;
	list<T>::const_iterator it;
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

template<class T>
ostream & operator<<(ostream & ro, const Vec<T>& v)
{
	ExceptionEmptyOperand e_empty_op;
	if (v.size() == 0)
	{
		throw (e_empty_op);// ExceptionEmptyOperand;
	}
	list<T>::const_iterator it;
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

template<class T>
Vec<T> range(T start, unsigned int size)
{
	Vec<T> new_vec;
	T element_to_insert = start;
	for (unsigned int i = 0; i < size; i++)
	{
		new_vec.push_back(element_to_insert);
		element_to_insert = element_to_insert + 1;
	}
	return new_vec;
}


template<class T>
class norm_inf_comp {

public:

	bool operator()(Vec<T>& lhs, Vec<T>& rhs) const
	{
		ExceptionEmptyOperand e_empty_op;
		if (lhs.size() == 0 || rhs.size() == 0)
		{
			throw (e_empty_op);// ExceptionEmptyOperand;
		}
		double inf_norm_lhs = 0, inf_norm_rhs = 0;
		list<T>::const_iterator it;
		for (it = lhs.begin(); it != lhs.end(); it++)
		{
			inf_norm_lhs = inf_norm_lhs > (double)abs(*it) ? inf_norm_lhs : (double)abs(*it);
		}
		for (it = rhs.begin(); it != rhs.end(); it++)
		{
			inf_norm_rhs = inf_norm_rhs > (double)abs(*it) ? inf_norm_rhs : (double)abs(*it);
		}
		return (inf_norm_lhs < inf_norm_rhs);
	}

};










#endif // _VEC_IMPL_H_