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
Mat<T> Mat<T>::operator*(const Mat<T>& rhs) const // MATRIX MULTIPLICATION
{
	unsigned int n = this->height();
	unsigned int m1 = w_();
	unsigned int m2 = rhs.height();
	unsigned int k = rhs.width();

	ExceptionWrongDimensions EXCEPwrongdimensions;
	ExceptionEmptyOperand EXCEPemptyoperand;

	if (m1 != m2)
		throw(EXCEPwrongdimensions);

	if (n == 0 || m1 == 0 || m2 == 0 || k == 0)
		throw(EXCEPemptyoperand);

	Mat<T> resultMAT(k);

	T el;
	Vec<T> BlankVec;
	Vec<T> LineVec;

	unsigned int left_row = 0;
	unsigned int right_col = 0;
	unsigned int inner = 0;

	while (left_row < n)
	{
		while (right_col < k)
		{
			el = 0;

			while (inner < m1)
			{
				el += ((*this)[left_row][inner] * rhs[inner][right_col]); // compute multiplication
				inner++;
			}

			LineVec.push_back(el); // insert element to line_vector

			right_col++;
		}

		resultMAT.push_back(LineVec); // insert line_vector to resultmat current row
		LineVec = BlankVec; // reset line_vector

		left_row++;
	}

	return resultMAT;
}

template<class T>
Mat<T> Mat<T>::operator,(const Mat<T>& rhs) const
{
	ExceptionWrongDimensions e_wrong_dim;
	ExceptionEmptyOperand EXCEPemptyoperand;

	if (w_ != rhs.width())
		throw(EXCEPwrongdimensions);

	if (rhs.size() == 0)
		throw(EXCEPemptyoperand);

	Mat<T> resultMAT(w_);

	typename list< Vec<T> >::const_iterator iter = this->begin();

	while (iter != this->end())
	{
		resultMAT.push_back(*iter);
		iter++;
	}

	iter = rhs.begin();

	while (iter != rhs.end())
	{
		resultMAT.push_back(*iter);
		iter++;
	}

	return resultMAT;
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
	unsigned int n = this->height();
	unsigned int m = this->width();

	Mat<T> resultMAT(this->height());

	Vec<T> BlankVec;
	Vec<T> LineVec;

	unsigned int row = 0;
	unsigned int col = 0;

	while (col < m)
	{
		while (row < n)
		{
			LineVec.push_back((*this)[row][col]);
			row++;
		}

		resultMAT.push_back(LineVec);
		LineVec = BlankVec;

		col++;
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
	ExceptionEmptyOperand EXCEPemptyoperand;
	if (m.size() == 0)
		throw(EXCEPemptyoperand);

	ro << "(" << endl;

	unsigned int i = 0;
	unsigned int j = 0;

	while (i < m.height())
	{
		ro << "(";

		while (j < m.width())
		{
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