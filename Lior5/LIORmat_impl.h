#ifndef _MAT_IMPL_H_
#define _MAT_IMPL_H_
#include "mat.h"
#include "vec.h"
#include <list>
using namespace std;

//*********************************************************************************************
// Name:           constructor Mat<T>::Mat(unsigned int w)        
// Description:    constructs a new matrix with width w
// Parameters:     unsigned int w - the characteristic allowed width of vectors in this matrix
// Return value:   Mat<T>
//*********************************************************************************************
template <class T>
Mat<T>::Mat(unsigned int w) : w_(w) {};
//*********************************************************************************************
// Name:           constructor Mat<T>::Mat(Vec<T> vec_1d)        
// Description:    constructs a new matrix with 1 vector(vec_1d) and sets the width to the length of vec_1d
// Parameters:     Vec<T> vec_1d-the matrix is constructed with  vec_1d elements and width
// Return value:   Mat<T>
//*********************************************************************************************
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
//*********************************************************************************************
// Name:           constructor Mat<T>::Mat(Vec< Vec<T> > vec_2d)      
// Description:    constructs a new matrix with vec_2d elements and sets the width to the length of vec_2d
// Parameters:     Vec< Vec<T> > vec_2d vec_2d-the matrix is constructed with  vec_2d elements and width
// Return value:   Mat<T>
//*********************************************************************************************
template <class T>
Mat<T>::Mat(Vec< Vec<T> > vec_2d)
{
	ExceptionEmptyOperand e_empty_op;
	if (vec_2d.size() == 0)
	{
		throw(e_empty_op);
	}
	w_ = vec_2d[0].size();
	for (unsigned int i = 0; i < vec_2d.size(); i++)
	{
		this->vals_.push_back(vec_2d[i]);
	}
}
//*********************************************************************************************
// Name:           Mat<T>::width()
// Description:    returns the characteristic allowed width of vectors in this matrix
// Parameters:     none
// Return value:   unsigned int w_, the width of the matrix
//*********************************************************************************************
template<class T>
unsigned int Mat<T>::width() const
{
	return w_;
}
//*********************************************************************************************
// Name:           Mat<T>::height()
// Description:    returns the characteristic allowed width of vectors in this matrix
// Parameters:     none
// Return value:   unsigned int w_, the width of the matrix
//*********************************************************************************************
template<class T>
unsigned int Mat<T>::height() const
{
	return this->vals_.size();
}
//*********************************************************************************************
// Name:           Mat<T>::operator+(const Mat & rhs) const
// Description:    overloads the + operator for matrices for +rhs operations, 
//				   adds this matrix with rhs and returns the result matrix
// Parameters:     const Mat & rhs
// Return value:   Mat<T> result- the matrix that contains the result of the addition
//*********************************************************************************************
template<class T>
Mat<T> Mat<T>::operator+(const Mat & rhs) const
{
	Mat<T> result(rhs.width());
	ExceptionWrongDimensions e_wrong_dim;
	ExceptionEmptyOperand e_empty_op;
	typename list< Vec<T> >::const_iterator it;
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
//*********************************************************************************************
// Name:           Mat<T>::operator*(const T & rhs) const
// Description:    overloads the * operator for matrix * rhs(scalar) operations, 
//				   multiplies this matrix by rhs scalar and returns the result matrix
// Parameters:     const T & rhs
// Return value:   Mat<T> result- the matrix that contains the result of the multiplication
//*********************************************************************************************
template<class T>
Mat<T> Mat<T>::operator*(const T & rhs) const
{
 	Mat<T> result((*this).width());
	typename list< Vec<T> >::const_iterator it;

	for (it = (*this).begin(); it != (*this).end(); it++)
	{
		result.push_back((*it)*rhs);
	}
	return result;
}
//*********************************************************************************************
// Name:           Mat<T>::operator*(const Mat<T> & rhs) const
// Description:    overloads the * operator for matrices for *rhs(matrix) operations, 
//				   multiplies this matrix by rhs matrix and returns the result matrix
// Parameters:     const Mat<T> & rhs
// Return value:   Mat<T> result- the matrix that contains the result of the multiplication
//*********************************************************************************************
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
				elem = elem + ((*this)[i][k] * rhs[k][j]);
			}
			vec_line.push_back(elem);
		}
		result.push_back(vec_line);
		vec_line = vec_temp;
	}
	return result;
}
//*********************************************************************************************
// Name:         Mat<T>::operator,(const Mat<T>& rhs) const                                
// Description:  concatanates the rhs matrix rows to the bottom of this matrix rows, keeping the same width
// Parameters:   const Mat<T>& rhs
// Return value: Mat<T> result matrix
//*********************************************************************************************
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
//*********************************************************************************************
// Name:         Mat<T>::get_rows(const Vec<unsigned int>& ind) const                              
// Description:  concatanates the rows indicated by ind(vector) and returns the result as matrix
// Parameters:   const Vec<unsigned int>& ind - each element of this vector specifies
//				 a row of the matrix that needs to be included in the result matrix
// Return value: Mat<T> result matrix
//*********************************************************************************************
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
	return result_mat;
}
//*********************************************************************************************
// Name:         Mat<T>::get_cols(const Vec<unsigned int>& ind) const                              
// Description:  concatanates the collumns indicated by ind(vector) and returns the result as matrix
// Parameters:   const Vec<unsigned int>& ind - each element of this vector specifies
//				 a collumn of the matrix that needs to be included in the result matrix
// Return value: Mat<T> result matrix
//*********************************************************************************************
template<class T>
Mat<T> Mat<T>::get_cols(const Vec<unsigned int>& ind) const
{
	Mat<T> temp_mat((*this).height());
	Mat<T> result_mat(ind.size());
	temp_mat = (*this).transpose().get_rows(ind);
	result_mat = temp_mat.transpose();
	return result_mat;
}
//*********************************************************************************************
// Name:         Mat<T>::transpose() const                          
// Description:  transposes the matrix and return the result
// Parameters:   none
// Return value: Mat<T> result matrix(the transpose of this matrix)
//*********************************************************************************************
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
//*********************************************************************************************
// Name:           operator*(const T & lhs, const Mat<T>& rhs)
// Description:    enables the * operator to include multiplications in the form scalar*matrix
// Parameters:     const Mat<T> & rhs -matrix
//			       const T & lhs -scalar
// Return value:   Mat<T> result- the matrix that contains the result of the multiplication
//*********************************************************************************************
template<class T>
Mat<T> operator*(const T & lhs, const Mat<T>& rhs)
{
	return rhs*lhs;
}
//*********************************************************************************************
// Name:           ostream & operator<<(ostream & ro, const Mat<T>& m)          
// Description:    outputs the vector to ostream in this pattern by overloading the << operator
//				   (	
//	first row -    (first_element,	second_element,	.......,	last_element)
//  second row -   (first_element,	second_element,	.......,	last_element)
//	.
//	.
//	last row -     (first_element,	second_element,	.......,	last_element)
//				   )
// Parameters:     ostream & ro, const Vec<T>& v
// Return value:   ro
//*********************************************************************************************
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