#ifndef _MAT_IMPL_H_
#define _MAT_IMPL_H_

#include "mat.h"
#include "vec.h"
#include <list>

using namespace std;

//********************************************************************************************
// Function Name:  Mat (constructor) 
// Description:    Creates a new matrix and initializes its width to w
// Parameters:
//		w (unsigned int) - width of vectors in the matrix
// Return value:   Newly created matrix
//********************************************************************************************
template <class T>
Mat<T>::Mat(unsigned int w) :
	w_(w)
{}

//********************************************************************************************
// Function Name:  Mat (constructor) 
// Description:    Creates a new matrix with one row (vector) and initializes its width to vector's width
// Parameters:
//		vec_1d (Vec) - row (vector)
// Return value:   Newly created matrix
//********************************************************************************************
template <class T>
Mat<T>::Mat(Vec<T> vec_1d)
{
	ExceptionEmptyOperand EXCEPemptyoperand;

	if (vec_1d.size() == 0)
		throw(EXCEPemptyoperand);

	this->vals_.push_back(vec_1d);

	w_ = vec_1d.size();
}

//********************************************************************************************
// Function Name:  Mat (constructor) 
// Description:    Creates a new 2D matrix with vector of vectors, and initializes its width to first vector's width
// Parameters:
//		vec_2d ((Vec< Vec >) - vector of vectors
// Return value:   Newly created matrix
//********************************************************************************************
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

//********************************************************************************************
// Function Name:  width
// Description:    returns the matrix's (vectors') width
// Parameters:     None
// Return value:   w_ (unsigned int) - matrix's width
//********************************************************************************************
template<class T>
unsigned int Mat<T>::width() const
{
	return w_;
}

//********************************************************************************************
// Function Name:  height
// Description:    returns the matrix's height (width of vertical vector of horizontal vectors)
// Parameters:     None
// Return value:   w_ (unsigned int) - vertical vector's width
//********************************************************************************************
template<class T>
unsigned int Mat<T>::height() const
{
	return this->vals_.size();
}

//********************************************************************************************
// Function Name:  operator+
// Description:    operator+ overload for matrix - adds current matrix to another (rhs)
// Parameters:     
//		rhs (Mat&) - matrix for addition
// Return value:   resultMAT - matrices summary result
//********************************************************************************************
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
		resultMAT.push_back(rhs[i] + (*iter)); // insert summary for every row

		i++;
		iter++;
	}

	return resultMAT;
}

//********************************************************************************************
// Function Name:  operator*
// Description:    operator* overload for scalar - multiply current matrix with a scalar (rhs)
// Parameters:     
//		rhs (T&) - scalar for multiplication
// Return value:   resultMAT - multiplication result
//********************************************************************************************
template<class T>
Mat<T> Mat<T>::operator*(const T& rhs) const
{
	Mat<T> resultMAT(w_);

	typename list< Vec<T> >::const_iterator iter = this->begin();

	while (iter != this->end())
	{
		resultMAT.push_back((*iter) * rhs); // multiply every vector with scalar and insert
		iter++;
	}

	return resultMAT;
}

//********************************************************************************************
// Function Name:  operator*
// Description:    operator* overload for matrix - multiply current matrix with another (rhs)
// Parameters:     
//		rhs (Mat&) - matrix for multiplication
// Return value:   resultMAT - matrices multiplication result
//********************************************************************************************
template<class T>
Mat<T> Mat<T>::operator*(const Mat<T>& rhs) const
{
	ExceptionWrongDimensions EXCEPwrongdimensions;
	ExceptionEmptyOperand EXCEPemptyoperand;

	unsigned int n = this->height();
	unsigned int m = w_;
	unsigned int p = rhs.width();

	if ((n == 0) || (m == 0) || (p == 0))
		throw(EXCEPemptyoperand);

	if (m != rhs.height())
		throw(EXCEPwrongdimensions);

	T el;
	Vec<T> BlankVec;
	Vec<T> LineVec;
	Mat<T> resultMAT(p);

	unsigned int row = 0;
	unsigned int col = 0;
	unsigned int inner = 0;
	
	while (row < n) { // for each lhs row

		col = 0;

		while (col < p) { // for each rhs column

			el = 0;
			inner = 0;

			while (inner < m) { // for each inner
				el = el + ((*this)[row][inner] * rhs[inner][col]); // add to element
				inner++;
			}

			LineVec.push_back(el); // insert element result to line vector

			col++;
		}

		resultMAT.push_back(LineVec); // insert line vector to result matrix
		LineVec = BlankVec; // reset line vector

		row++;
	}

	return resultMAT;
}

//********************************************************************************************
// Function Name: operator,                                
// Description:   concatenates the input matrix's (rhs) rows under the current matrix
// Parameters:   
//		rhs (Mat&) - matrix for conctenation
// Return value:  resultMAT - matrices conctenation result
//********************************************************************************************
template<class T>
Mat<T> Mat<T>::operator,(const Mat<T>& rhs) const
{
	ExceptionWrongDimensions EXCEPwrongdimensions;
	ExceptionEmptyOperand EXCEPemptyoperand;

	if (rhs.size() == 0)
	{
		throw(EXCEPemptyoperand);
	}

	if (w_ != rhs.width())
	{
		throw(EXCEPwrongdimensions);
	}

	typename list< Vec<T> >::const_iterator iter = this->begin();

	Mat<T> resultMAT(rhs.width());

	while (iter != this->end())
	{
		resultMAT.push_back(*iter); // insert current matrix to result
		iter++;
	}

	iter = rhs.begin();

	while (iter != rhs.end())
	{
		resultMAT.push_back(*iter); // insert rhs matrix to result
		iter++;
	}

	return resultMAT;
}

//********************************************************************************************
// Function Name: get_rows                        
// Description:   returns the rows by vector of indices as a matrix
// Parameters:   
//		ind (Vec<unsigned int>&) - vector of row's indices for result matrix
// Return value:  resultMAT - matrix with desirable rows
//********************************************************************************************
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

//********************************************************************************************
// Function Name: get_cols                      
// Description:   returns the columns by vector of indices as a matrix
// Parameters:   
//		ind (Vec<unsigned int>&) - vector of column's indices for result matrix
// Return value:  resultMAT - matrix with desirable columns
//********************************************************************************************
template<class T>
Mat<T> Mat<T>::get_cols(const Vec<unsigned int>& ind) const
{
	Mat<T> TranMAT(this->height());
	TranMAT = this->transpose().get_rows(ind); // use transpose of get_rows to achieve columns

	Mat<T> resultMAT(ind.size());
	resultMAT = TranMAT.transpose(); // transpose back result matrix

	return resultMAT;
}

//********************************************************************************************
// Function Name: transpose                          
// Description:   transposes current matrix
// Parameters:    None
// Return value:  resultMAT - transposed matrix
//********************************************************************************************
template<class T>
Mat<T> Mat<T>::transpose() const
{
	unsigned int n = this->height();
	unsigned int m = w_;

	Vec<T> BlankVec, LineVec;
	Mat<T> resultMAT(this->height());

	unsigned int row = 0;
	unsigned int col = 0;

	while (col < m)
	{
		row = 0;

		while (row < n)
		{
			LineVec.push_back((*this)[row][col]); // insert changed order to line vector
			row++;
		}

		resultMAT.push_back(LineVec); // insert each line vector to result
		LineVec = BlankVec; // reset line vector

		col++;
	}

	return resultMAT;
}

//********************************************************************************************
// Function Name:  operator*
// Description:    operator* overload for scalar - multiply it with a matrix (rhs)
// Parameters:   
//		lhs (T&) - scalar for multiplication(T&) - scalar for multiplication
//		rhs (MAT&) - matrix for multiplication
// Return value:   resultMAT - multiplication result
//********************************************************************************************
template<class T>
Mat<T> operator*(const T& lhs, const Mat<T>& rhs)
{
	return rhs*lhs;
}

//********************************************************************************************
// Function Name:  operator<<     
// Description:    operator<< overload for printing to standart output a matrix row-by-row
// Description:    outputs the vector to ostream in this pattern by overloading the << operator
// Parameters:     
//		ro (ostream&) - output stream
//		m (Mat&) - matrix for printing
// Return value:   ro - updated output stream
//********************************************************************************************
template<class T>
ostream& operator<<(ostream& ro, const Mat<T>& m)
{
	ExceptionEmptyOperand EXCEPemptyoperand;

	if (m.size() == 0)
		throw(EXCEPemptyoperand);

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