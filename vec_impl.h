#ifndef _VEC_IMPL_H_
#define _VEC_IMPL_H_
#include <list>
#include <exception>
#include <iostream>
#include <cmath>

const char* ExceptionWrongDimensions::what() const throw()
{
	return "operand dimensions must agree";
}

const char* ExceptionEmptyOperand::what() const throw()
{
	return "empty operand";
}

const char* ExceptionIndexExceed::what() const throw()
{
	return "index exeeds operand dimensions";
}

template<class T>
Vec<T>::Vec(const T & el)
{
	this->vals_.push_back(el);
}

template<class T>
void Vec<T>::push_back(T el)
{
	vals_.push_back(el);
}

template<class T>
unsigned int Vec<T>::size() const
{
	return vals_.size();
}

template<class T>
Vec<T> Vec<T>::operator+(const Vec & rhs) const
{
	ExceptionWrongDimensions e_wng_dim;
	ExceptionEmptyOperand e_empty;
	
	Vec new_vec;
	if (this->vals_.size() != rhs.size())
		throw (e_wng_dim);
	if (this->vals_.size() == 0)
		throw (e_empty);
	
	unsigned int i = 0;
	
	while (i < this->vals_.size()) {
		new_vec.push_back((*this)[i] + rhs[i]);
		i++;
	}

	return new_vec;
}

template<class T>
Vec<T> Vec<T>::operator*(const T & rhs) const
{
	ExceptionEmptyOperand e_empty;

	Vec<T> new_vec;

	//if (rhs.size() == 0)
	//	throw (e_empty);

	unsigned int i = 0;
	typename list<T>::const_iterator iter = this->begin();

	while (i < this->size()) {
		new_vec.push_back(rhs * (*iter));
		i++;
		iter++;
	}

	return new_vec;
}

template<class T>
T & Vec<T>::operator[](unsigned int ind)
{
	ExceptionIndexExceed e_idx_exc;
	if (ind >= this->vals_.size())
		throw(e_idx_exc);
	
	unsigned int i = 0;
	list<T>::const_iterator iter = vals_.begin();
	while (i < ind) {
		i++;
		iter++;
	}

	return const_cast<T&>(*iter);
}

template<class T>
const T & Vec<T>::operator[](unsigned int ind) const
{
	ExceptionIndexExceed e_idx_exc;
	if (ind >= this->vals_.size())
		throw(e_idx_exc);

	unsigned int i = 0;
	list<T>::const_iterator iter = vals_.begin();
	while (i < ind) {
		i++;
		iter++;
	}

	return *iter;
}

template<class T>
Vec<T> Vec<T>::operator,(const Vec & rhs) const
{
	ExceptionEmptyOperand e_empty;
	if (rhs.size() == 0)
		throw (e_empty);

	Vec<T> new_vec;

	typename list<T>::const_iterator iter = this->begin();
	
	while (iter != this->end()) {
		new_vec.push_back(*iter);
		iter++;
	}

	iter = rhs.begin();
	while (iter != rhs.end()) {
		new_vec.push_back(*iter);
		iter++;
	}

	return new_vec;
}

template<class T>
Vec<T> Vec<T>::operator[](const Vec<unsigned int>& ind) const
{
	ExceptionIndexExceed e_idx_exc;

	Vec<T> new_vec;

	unsigned int i=0;
	while (i < ind.size()) {
		if (ind[i] >= this->size())
			throw (e_idx_exc);

		new_vec.push_back((*this)[ind[i]]);
		i++;
	}

	return new_vec;
}


template<class T>
Vec<T> operator*(const T & lhs, const Vec<T>& rhs)
{
	ExceptionEmptyOperand e_empty;

	Vec<T> new_vec;

	if (rhs.size() == 0)
		throw (e_empty);

	unsigned int i = 0;
	list<T>::const_iterator iter = rhs.begin();

	while (i < rhs.size()) {
		new_vec.push_back(lhs * (*iter));
		i++;
		iter++;
	}

	return new_vec;

}

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
	++it;
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

	unsigned int i = 0;
	while (i < size) {
		new_vec.push_back(start);
		start++;
		i++;
	}

	return new_vec;
}

template<class T>
class norm_inf_comp {
public:
	bool operator()(Vec<T>& lhs, Vec<T>& rhs) const {

		ExceptionEmptyOperand e_empty_op;
		if (lhs.size() == 0 || rhs.size() == 0)
			throw (e_empty_op);	// ExceptionEmptyOperand;

		typename list<T>::const_iterator iter = lhs.begin();

		double lhs_norm = 0, rhs_norm = 0;

		while (iter != lhs.end()) {
			if (lhs_norm > (double)abs(*iter))
				continue;
			else
				lhs_norm = (double)abs(*iter);
		}

		iter = rhs.begin();

		while (iter != rhs.end()) {
			if (rhs_norm > (double)abs(*iter))
				continue;
			else
				rhs_norm = (double)abs(*iter);
		}

		return lhs_norm < rhs_norm;
	}
};

#endif // _VEC_IMPL_H_