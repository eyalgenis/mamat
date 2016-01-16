#ifndef _SQ_MAT_IMPL_H_
#define _SQ_MAT_IMPL_H_
#include "mat.h"
#include "vec.h"
#include <list>
#include <cmath>
#include <iostream>
#include "sq_mat.h"
using namespace std;

template<class T>
SqMat<T>::SqMat(Mat<T> m) : Mat<T>(m) {};

template<class T>
unsigned int SqMat<T>::size() const
{
	return (*this).width();
}

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
	SqMat<T> temp(n - 1);//for it to be the same size
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
		det = det + (*this)[0][p] * pow(-1, p) * temp.determinant();
	}
	return det;
}
//template<class T>
//T SqMat<T>::determinant() const//using lu decomposition such as M=LU
//{
//	SqMat lower((*this));//to initialize two matrices with the same size
//	SqMat upper((*this));//to initialize two matrices with the same size
//	T det=1;
//	unsigned int n = (*this).size();
//	for (unsigned int i = 0; i < n; i++)
//	{
//		for (unsigned int j = 0; j < n; j++)
//		{
//			if (j < i)
//				lower[j][i] = 0;
//			else
//			{
//				lower[j][i] = (*this)[j][i];
//				for (unsigned int k = 0; k < i; k++)
//				{
//					lower[j][i] = lower[j][i] - lower[j][k] * upper[k][i];
//				}
//			}
//		}
//		for (unsigned int j = 0; j < n; j++)
//		{
//			if (j < i)
//				upper[i][j] = 0;
//			else if (j == i)
//				upper[i][j] = 1;
//			else
//			{
//				upper[i][j] = (*this)[i][j] / lower[i][i];
//				for (unsigned int k = 0; k < i; k++)
//				{
//					upper[i][j] = upper[i][j] - ((lower[i][k] * upper[k][j]) / lower[i][i]);
//				}
//			}
//		}
//	}
//	for (unsigned int i = 0; i < n; i++)
//	{
//		det = upper[i][i] * lower[i][i] * det;
//	}
//
//	return det;
//}












#endif // _SQ_MAT_IMPL_H_
