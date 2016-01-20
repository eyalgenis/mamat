#ifndef _SQ_MAT_IMPL_H_
#define _SQ_MAT_IMPL_H_

#include <cmath>
#include "sq_mat.h"
#include "mat.h"

//*******************************************************************************************
// Name:           SqMat<T>::SqMat(Mat<T> m)
// Description:    Constructs a new square matrix with Mat<T> m elements and properties
// Parameters:     Mat<T> m
// Return value:   
//*******************************************************************************************
template<class T>
SqMat<T>::SqMat(Mat<T> m) : Mat<T>(m)
{
	ExceptionWrongDimensions e_wrong_dim;
	if (m.width() != m.height()) // check matrix width & height equality
		throw(e_wrong_dim);
}

//*******************************************************************************************
// Name:           SqMat<T>::size() const
// Description:    Calculates the square matrix size
// Parameters:     
// Return value:   unsigned int w_
//*******************************************************************************************
template<class T>
unsigned int SqMat<T>::size() const
{
	return this->w_; // using just width because width=height
}

//*******************************************************************************************
// Name:           SqMat<T>::determinant() const
// Description:    Calculates the square matrix determinant with recursion
// Parameters:     
// Return value:   T det
//*******************************************************************************************
template<class T>
T SqMat<T>::determinant() const
{
	T det = 0;
	unsigned int p, h, k, i, j;
	unsigned int n = this->size();
	Vec<T> line_vec, empty_vec;

	Mat<T> mat_temp(this->size() - 1); // create temp new smaller matrix to calculate its determinant (recursion)
	
	unsigned int l = 0;
	while (l < n - 1) { // copy this square matrix to the temp matrix

		unsigned int t = 0;
		while (t < n - 1) {
			line_vec.push_back(0);
			t++;
		}

		mat_temp.push_back(line_vec);
		line_vec = empty_vec;
		l++;
	}

	if (n == 1) { // stoppage condition 1 - no calculation for 1x1 matrix
		return (*this)[0][0];
	}
	else if (n == 2) { // stoppage condition 2 - short calculation of 2x2 matrix)
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
			SqMat<T> sq_mat_temp = (SqMat<T>) mat_temp; // casting for temp matrix to square matrix - needed to calculate determinant
			det = det + (*this)[0][p] * pow(-1, p) * sq_mat_temp.determinant(); // recursion
		
		}
		return det;
	}
}

#endif // _SQ_MAT_IMPL_H_
