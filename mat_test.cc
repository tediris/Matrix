#include "./matrix.h"
#include <iostream>
#include "./linsolver.h"
#include <vector>
using namespace std;

int main() {
	Matrix<float> A(3, 3);
	A.set(0, 0, 0.0);
	A.set(0, 1, 2.0);
	A.set(0, 2, 1.0);
	A.set(1, 0, 1.0);
	A.set(1, 1, -2.0);
	A.set(1, 2, -3.0);
	A.set(2, 0, -1.0);
	A.set(2, 1, 1.0);
	A.set(2, 2, 2.0);

	//cout << "A[0][2]: " << A[0][2] << endl;

	int colsToExtract[] = {0, 1};
	Matrix<float> shrunk = A.extractColumns(colsToExtract, sizeof(colsToExtract) / sizeof(colsToExtract[0]));
	//cout << shrunk << endl;

	float firstCol[A.getRows()] = {};
	A.getColumn(firstCol, 0);

	Matrix<float> b(3, 1);
	b.set(0, 0, -8.0);
	b.set(1, 0, 0.0);
	b.set(2, 0, 3.0);

	//cout << b << endl;
	//Matrix<float> X = A;
	//cout << X << endl;
	//std::cout << "Matrix size: " << (sizeof(float) * A.getRows() * A.getCols())  << std::endl;

	Matrix<float> result = LSolve::GaussianElim(A, b);
	cout << result << endl;

}
