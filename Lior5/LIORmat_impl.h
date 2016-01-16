#ifndef _MAT_IMPL_H_
#define _MAT_IMPL_H_
#include "mat.h"
#include "vec.h"
#include <list>
using namespace std;

template <class T>
Mat<T>::Mat(unsigned int w) : w_(w) {};

template <class T>
Mat<T>::Mat(Vec<T> vec_1d)
{
	ExceptionEmptyOperand e_empty_op;
	if (vec_1d.size()==0)
	{
		throw(e_empty_op);
	}
	w_ = vec_1d.size();
	this->vals_.push_back(vec_1d);
}


template <class T>
Mat<T>::Mat(Vec< Vec<T> > vec_2d)
{
	ExceptionEmptyOperand e_empty_op;
	if (vec_2d.size() == 0)
	{
		throw(e_empty_op);
	}
	w_ = vec_2d.width();
	for (unsigned int i = 0; i < vec_2d.size(); i++)
	{
		this->vals_.push_back(vec_2d[i]);
	}
}

template<class T>
unsigned int Mat<T>::width() const
{
	return w_;
}

template<class T>
unsigned int Mat<T>::height() const
{
	return vals_.size();
}

template<class T>
Mat<T> Mat<T>::operator+(const Mat & rhs) const
{
	Mat<T> result(rhs.width());
	ExceptionWrongDimensions e_wrong_dim;
	ExceptionEmptyOperand e_empty_op;
	list<Vec<T>>::const_iterator it;
	if ((w_ != rhs.width()) || ((*this).height() != rhs.height()))
	{
		throw(e_wrong_dim);
	}
	if ((rhs.width() == 0) || (rhs.height() == 0) || ((*this).width() == 0) || ((*this).height() == 0))
	{
		throw(e_empty_op);
	}
	it = (*this).begin();
	for (unsigned int i = 0; i < rhs.height(); i++)
	{
		result.push_back(rhs[i]+ (*it));
		it++;
	}
	return result;
}

template<class T>
Mat<T> Mat<T>::operator*(const T & rhs) const
{
 	Mat<T> result((*this).width());
	list<Vec<T>>::const_iterator it;

	for (it = (*this).begin(); it != (*this).end(); it++)
	{
		result.push_back((*it)*rhs);
	}
	return result;
}

template<class T>
Mat<T> Mat<T>::operator*(const Mat<T>& rhs) const
{
	unsigned int n, m, p;
	n = (*this).height();
	m = (*this).width();
	p = rhs.width();
	Mat<T> result(p);
	Vec<T> vec_line,vec_temp;
	T elem;
	ExceptionWrongDimensions e_wrong_dim;
	ExceptionEmptyOperand e_empty_op;
	
	if ((*this).height() != rhs.width())
	{
		throw(e_wrong_dim);
	}
	if ((rhs.width() == 0) || (rhs.height() == 0) || ((*this).width() == 0) || ((*this).height() == 0))
	{
		throw(e_empty_op);
	}
	for (unsigned int i = 0; i < n; i++)
	{	
		for (unsigned int j = 0; j < p; j++)
		{
			elem = 0;
			for (unsigned int k = 0; k < m; k++)
			{
				elem = elem + (*this)[i][k] * rhs[k][j];
			}
			vec_line.push_back(elem);
		}
		result.push_back(vec_line);
		vec_line = vec_temp;
	}
	return result;
}

template<class T>
Mat<T> Mat<T>::operator,(const Mat<T>& rhs) const
{
	ExceptionEmptyOperand e_empty_op;
	ExceptionWrongDimensions e_wrong_dim;
	list<Vec<T>>::const_iterator it;
	Mat<T> result(rhs.width());
	if (rhs.size() == 0)
	{
		throw(e_empty_op);
	}
	if (rhs.width() != this->width())
	{
		throw(e_wrong_dim);
	}
	for (it = (*this).begin(); it != (*this).end(); it++)
	{
		result.push_back(*it);
	}
	for (it = rhs.begin(); it != rhs.end(); it++)
	{
		result.push_back(*it);
	}
	return result;
}

template<class T>
Mat<T> Mat<T>::get_rows(const Vec<unsigned int>& ind) const
{
	ExceptionIndexExceed e_index_exceed;
	Mat<T> result_mat((*this).width());
	for (unsigned int i = 0; i < ind.size(); i++)
	{
		if (ind[i] > (*this).height())
		{
			throw (e_index_exceed);
		}
		result_mat.push_back((*this)[(ind[i])]);
	}
	result_mat.push_back((*this)[ind]);
	return result;
}
template<class T>
Mat<T> Mat<T>::get_cols(const Vec<unsigned int>& ind) const
{
	Mat<T> temp_mat((*this).height());
	Mat<T> result_mat(ind.size());
	temp_mat = (*this).transpose().get_rows(ind);
	result_mat = temp_mat.transpose();
}

template<class T>
Mat<T> Mat<T>::transpose() const
{
	Mat<T> result((*this).height());
	unsigned int n, m;
	Vec<T> vec_line_of_trans, vec_empty;
	n = (*this).height();
	m = (*this).width();
	for (unsigned int j = 0; j < m; j++)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			vec_line_of_trans.push_back((*this)[i][j]);
		}
		result.push_back(vec_line_of_trans);
		vec_line_of_trans = vec_empty;
	}
	return result;
}








template<class T>
Mat<T> operator*(const T & lhs, const Mat<T>& rhs)
{
	return rhs*lhs;
}

template<class T>
ostream & operator<<(ostream & ro, const Mat<T>& m)
{
	{
		ro << "(" << endl;
		ExceptionEmptyOperand e_empty_op;
		if (m.size() == 0)
		{
			throw(e_empty_op);
		}
		for (unsigned int i = 0; i < m.height(); i++)
		{

			ro << "(";
			for (unsigned int j = 0; j < m.width(); j++)
			{
				if (j == 0)
				{
					ro << m[i][j];
				}
				else
				{
					ro << ",\t" << m[i][j];
				}
			}
			if (i == m.height() - 1)
			{
				ro << ")\n";
			}
			else
			{
				ro << "),\n";
			}
		}
		ro << ")";
		return ro;
	}
}

#endif // _MAT_IMPL_H_