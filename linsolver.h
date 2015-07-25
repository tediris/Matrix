#ifndef LINSOLVER_H
#define LINSOLVER_H

#include "matrix.h"
#include <cmath>

namespace LSolve {
	int choosePivot(Matrix<float>& mat, int col);
	void normalizeRow(Matrix<float>& mat, int row);
	Matrix<float> GaussianElim(Matrix<float> A, Matrix<float> b);
}

#endif
