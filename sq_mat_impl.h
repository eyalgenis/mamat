#ifndef _SQ_MAT_IMPL_H_
#define _SQ_MAT_IMPL_H_

#include <math.h>
#include "sq_mat.h"
#include "mat.h"

template<class T>
SqMat<T>::SqMat(Mat<T> m) : Mat<T>(m)
{
	ExceptionWrongDimensions e_wrong_dim;
	if (m.width() != m.height())
		throw(e_wrong_dim);
}

template<class T>
unsigned int SqMat<T>::size() const
{
	unsigned int w = this->w_;
	return w;
}

template<class T>
T SqMat<T>::determinant() const
{
	T det = 0;
	unsigned int p, h, k, i, j;
	Vec<T> line_vec, empty_vec;
	unsigned int n = this->size();

	Mat<T> mat_temp(this->size() - 1);
	
	for (unsigned int l = 0; l < n - 1; l++)
	{
		for (unsigned int t = 0; t < n - 1; t++)
		{
			line_vec.push_back(0);
		}
		mat_temp.push_back(line_vec);
		line_vec = empty_vec;
	}

	if (n == 1) {
		return (*this)[0][0];
	}
	else if (n == 2) {
		det = ((*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0]);
		return det;
	}
	else {
		for (p = 0; p < n; p++) {
			h = 0;
			k = 0;
			for (i = 1; i < n; i++) {
				for (j = 0; j < n; j++) {
					if (j == p) {
						continue;
					}
					mat_temp[h][k] = (*this)[i][j];
					k++;
					if (k == n - 1) {
						h++;
						k = 0;
					}
				}
			}
			SqMat<T> sq_mat_temp = (SqMat<T>) mat_temp;
			det = det + (*this)[0][p] * pow(-1, p) * sq_mat_temp.determinant();
		
		}
		return det;
	}
}



#endif // _SQ_MAT_IMPL_H_
