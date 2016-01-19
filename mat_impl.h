#ifndef _MAT_IMPL_H_
#define _MAT_IMPL_H_

#include "mat.h"
#include "vec.h"
#include <list>

using namespace std;

template <class T>
Mat<T>::Mat(unsigned int w) : // constructor for matrix WIDTH INITIALIZATION (=> WIDTH for all vectors)
	w_(w)
{}

template <class T>
Mat<T>::Mat(Vec<T> vec_1d) // constructor for ONE ROW (vector), and also: mat_width <= vec_width
{
	ExceptionEmptyOperand EXCEPemptyoperand;

	if (vec_1d.size() == 0)
		throw(EXCEPemptyoperand);

	this->vals_.push_back(vec_1d);

	w_ = vec_1d.size();
}

template <class T>
Mat<T>::Mat(Vec< Vec<T> > vec_2d) // constructor for 2D (vector of vectors), and also: mat_width <= 2D[0].size() = first vector's size
{
	ExceptionEmptyOperand EXCEPemptyoperand;

	if (vec_2d.size() == 0)
		throw(EXCEPemptyoperand);

	w_ = vec_2d[0].size();

	unsigned int i = 0;

	while (i < w_)
	{
		this->vals_.push_back(vec_2d[i]);
		i++;
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
	return this->vals_.size(); // size of this<->vertical vector (of hotizontal vectors)
}

template<class T>
Mat<T> Mat<T>::operator+(const Mat& rhs) const
{
	ExceptionWrongDimensions EXCEPwrongdimensions;
	ExceptionEmptyOperand EXCEPemptyoperand;

	if (w_ != rhs.width() || this->height() != rhs.height())
		throw(EXCEPwrongdimensions);

	if (w_ == 0 || this->height() == 0 || rhs.width() == 0 || rhs.height() == 0)
		throw(EXCEPemptyoperand);
	
	Mat<T> resultMAT(w_);

	typename list< Vec<T> >::const_iterator iter = this->begin();

	unsigned int i = 0;

	while(i < rhs.height())
	{
		resultMAT.push_back(rhs[i] + (*iter));

		i++;
		iter++;
	}

	return resultMAT;
}

template<class T>
Mat<T> Mat<T>::operator*(const T & rhs) const
{
	Mat<T> resultMAT(w_);

	typename list< Vec<T> >::const_iterator iter = this->begin();

	while (iter != this->end())
	{
		resultMAT.push_back((*iter) * rhs);
		iter++;
	}

	return resultMAT;
}

template<class T>
Mat<T> Mat<T>::operator*(const Mat<T>& rhs) const
{
	unsigned int n = this->height();
	unsigned int m = this->width();
	unsigned int p = rhs.width();
	Mat<T> new_mat(p);
	Vec<T> vec_line, vec_temp;
	T elem;
	ExceptionWrongDimensions e_wrong_dim;
	ExceptionEmptyOperand e_empty_op;

	if (this->width() != rhs.height())
		throw(e_wrong_dim);

	if ((rhs.width() == 0) || (rhs.height() == 0) || (this->width() == 0) || (this->height() == 0))
		throw(e_empty_op);

	unsigned int i = 0;
	while (i < n) {

		unsigned int j = 0;
		while (j < p) {
			elem = 0;
			unsigned int k = 0;
			while (k < m) {
				elem = elem + ((*this)[i][k] * rhs[k][j]);
				k++;
			}
			vec_line.push_back(elem);

			j++;
		}
		new_mat.push_back(vec_line);
		vec_line = vec_temp;

		i++;
	}

	return new_mat;
}

template<class T>
Mat<T> Mat<T>::operator,(const Mat<T>& rhs) const
{
	ExceptionEmptyOperand e_empty_op;
	ExceptionWrongDimensions e_wrong_dim;
	typename list< Vec<T> >::const_iterator it;
	Mat<T> result(rhs.width());
	if (rhs.size() == 0)
	{
		throw(e_empty_op);
	}
	if (rhs.width() != this->width())
	{
		throw(e_wrong_dim);
	}
	it = (*this).begin();
	while (it != (*this).end())
	{
		result.push_back(*it);
		it++;
	}
	it = rhs.begin();
	while (it != rhs.end())
	{
		result.push_back(*it);
		it++;
	}
	return result;
}

template<class T>
Mat<T> Mat<T>::get_rows(const Vec<unsigned int>& ind) const
{
	ExceptionIndexExceed EXCEPindexexceed;

	Mat<T> resultMAT(w_);

	unsigned int i = 0;

	while (i < ind.size())
	{
		if (this->height < ind[i])
			throw (EXCEPindexexceed);

		resultMAT.push_back((*this)[(ind[i])]);

		i++;
	}

	return resultMAT;
}

template<class T>
Mat<T> Mat<T>::get_cols(const Vec<unsigned int>& ind) const
{
	Mat<T> TranMAT(this->height());
	TranMAT = (*this).transpose().get_rows(ind);

	Mat<T> resultMAT(ind.size());
	resultMAT = TranMAT.transpose();

	return resultMAT;
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
	
	ExceptionEmptyOperand e_empty_op;
	if (m.size() == 0)
		throw(e_empty_op);

	ro << "(" << endl;

	unsigned int i = 0;
	while (i < m.height()) {
		ro << "(";

		unsigned int j = 0;
		while (j < m.width()) {
			if (j == 0)
				ro << m[i][j];
			else
				ro << ",\t" << m[i][j];

			j++;
		}

		if (i == m.height() - 1)
			ro << ")\n";
	
		else
			ro << "),\n";
		
		i++;
	}

	ro << ")";
	return ro;
	
}

#endif // _MAT_IMPL_H_