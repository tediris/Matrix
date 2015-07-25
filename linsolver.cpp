#include "./linsolver.h"
#include <iostream>

namespace LSolve {

	int choosePivot(Matrix<float>& mat, int col) {

		float biggest = 0;
		float pivotIndex = -1;

		for (int row = col; row < mat.getRows(); row++) {
			float value = mat.get(row, col);
			if (value != 0 && std::abs(value) > biggest) {
				biggest = value;
				pivotIndex = row;
			}
		}

		return pivotIndex;
	}

	void normalizeRow(Matrix<float>& mat, int row) {
		float normalizer = mat.get(row, row);
		for (int col = row; col < mat.getCols(); col++) {
			mat.set(row, col, mat.get(row, col) / normalizer);
		}
	}

	Matrix<float> GaussianElim(Matrix<float> A, Matrix<float> b) {

		// Forward Elimination

		for (int i = 0; i < A.getCols(); i++) {
			int pivotIndex = choosePivot(A, i);\
			if (pivotIndex != i) {
				if (pivotIndex < 0) {
					return A; // need to return null sentinel
				}
				A.swapRows(i, pivotIndex);
				b.swapRows(i, pivotIndex);
			}
			b.set(i, 0, b.get(i, 0) / A.get(i, i));
			normalizeRow(A, i);
			for (int j = i + 1; j < A.getRows(); j++) {
				float scale = -1 * A.get(j, i);
				//std::cout << "scale: " << scale << std::endl;
				A.scaleAddRows(i, scale, j);
				b.scaleAddRows(i, scale, j);
			}
		}

		// Backward Elimination

		for (int i = A.getCols() - 1; i >= 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				float scale = -1 * A.get(j, i);
				A.scaleAddRows(i, scale, j);
				b.scaleAddRows(i, scale, j);
			}
		}

		return b;

	}

}