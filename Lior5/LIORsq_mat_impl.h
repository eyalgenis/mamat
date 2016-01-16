#ifndef _SQ_MAT_IMPL_H_
#define _SQ_MAT_IMPL_H_
#include "mat.h"
#include "vec.h"
#include <list>
#include <cmath>
#include <iostream>
#include "sq_mat.h"
using namespace std;
//*********************************************************************************************
// Name:           SqMat<T>::SqMat(Mat<T> m) : Mat<T>(m) {};
// Description:    constructs a new square matrix with Mat<T> m elements and properties
// Parameters:     Vec< Vec<T> > vec_2d vec_2d-the matrix is constructed with  vec_2d elements and width
// Return value:   Mat<T>
//*********************************************************************************************
template<class T>
SqMat<T>::SqMat(Mat<T> m):Mat<T>(m)
{
	ExceptionWrongDimensions e_wrong_dim;
	if (m.width() != m.height())
	{
		throw(e_wrong_dim);
	}
}
//*********************************************************************************************
// Name:           unsigned int SqMat<T>::size() const
// Description:    returns the characteristic size(length and height) of this matrix
// Parameters:     none
// Return value:   unsigned (*this).width() - the size of the matrix
//*********************************************************************************************
template<class T>
unsigned int SqMat<T>::size() const
{
	return (*this).width();
}
//*********************************************************************************************
// Name:           T SqMat<T>::determinant() const
// Description:    calculates the determinant of this SqMat
// Parameters:     none
// Return value:   T det- the determinant of this SqMat
//*********************************************************************************************
template<class T>
T SqMat<T>::determinant() const
{
	T det=0;
	Vec<T> line_vec, empty_vec;
	unsigned int n = (*this).size();
	unsigned int i, j, k, h, p,l,t;
	if (n == 1)
	{
		return (*this)[0][0];
	}
	if (n == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
	}
	Mat<T> temp(n - 1);//for it to be the same size
	
	for (l = 0; l < n - 1; l++)
	{
		for (t = 0; t < n - 1; t++)
		{
			line_vec.push_back(0);
		}
		temp.push_back(line_vec);
		line_vec = empty_vec;
	}
	for (p = 0; p < n; p++)
	{
		h = 0;
		k = 0;
		for (i = 1; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (j == p)
				{
					if (k == n - 1)
					{
						h++;
						k = 0;
					}
					continue;
				}
				temp[h][k] = (*this)[i][j];
				k++;
				if (k == n - 1)
				{
					h++;
					k = 0;
				}
			}
		}
		SqMat<T> sq_temp = (SqMat<T>)temp;
		det = det + (*this)[0][p] * pow(-1, p) *sq_temp.determinant();
	}
	return det;
}













#endif // _SQ_MAT_IMPL_H_
