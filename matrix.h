#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

template <class T>
class Matrix {
public:
	Matrix(int rows, int cols);
	Matrix(const Matrix<T>& mat);
	Matrix<T>& operator= (const Matrix<T> &mat);
	~Matrix();
	int getRows();
	int getCols();
	T* getValues() const;
	T get(int row, int col);
	void set(int row, int col, T value);
	Matrix<T> transpose();
	void scaleRow(int row, int scale);
	void scaleRow(int row, float scale);
	void scaleRow(int row, double scale);
	void addRows(int row1, int row2); //stores in row2
	void swapRows(int row1, int row2);
	void scaleAddRows(int row1, int scale, int row2); //stores in row2
	void scaleAddRows(int row1, float scale, int row2); //stores in row2
	void scaleAddRows(int row1, double scale, int row2); //stores in row2
	Matrix<T> extractColumns(int colsToExtract[], size_t size);
	void getColumn(T* buf, int col);
	Matrix<T> operator+(Matrix<T>& mat);
	Matrix<T> operator-(Matrix<T>& mat);
	std::string toString();
	Matrix<T> operator*(int value);
	Matrix<T> operator*(float value);
	Matrix<T> operator*(double value);
	Matrix<T> operator*(Matrix<T>& mat);
	T* operator[](int index); // effectively a get row
	template <class U>
	friend std::ostream& operator<<(std::ostream& os, Matrix<U>& mat);


private:
	int rows;
	int cols;
	T *values;
};

template <class T>
Matrix<T>::Matrix(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	this->values = new T[rows * cols];
}


template <class T>
Matrix<T>::Matrix(const Matrix<T>& mat) {
	this->rows = mat.rows;
	this->cols = mat.cols;
	this->values = new T[rows * cols];
	std::memcpy(this->getValues(), mat.getValues(), sizeof(T) * this->rows * this->cols);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat) {
	this->rows = mat.rows;
	this->cols = mat.cols;
	this->values = new T[rows * cols];
	std::memcpy(this->getValues(), mat.getValues(), sizeof(T) * this->rows * this->cols);

	return *this;
}

template <class T>
Matrix<T>::~Matrix() {
	delete [] values;
}

template <class T>
int Matrix<T>::getRows() {
	return this->rows;
}

template <class T>
int Matrix<T>::getCols() {
	return this->cols;
}

template <class T>
T* Matrix<T>::getValues() const {
	return this->values;
}

template <class T>
T Matrix<T>::get(int row, int col) {
	return values[row * this->cols + col];
}

template <class T>
void Matrix<T>::set(int row, int col, T value) {
	values[row * this->cols + col] = value;
}

template <class T>
Matrix<T> Matrix<T>::transpose() {
	Matrix<T> result(this->getCols(), this->getRows());
	for (int i = 0; i < this->getRows(); i++) {
		for (int j = 0; j < this->getCols(); j++) {
			result.set(j, i, this->get(i ,j));
		}
	}
	return result;
}

template <class T>
void Matrix<T>::addRows(int row1, int row2) {
	for (int col = 0; col < this->cols; col++) {
		values[row2 * this->cols + col] += values[row1 * this->cols + col];
	}
}

template <class T>
void Matrix<T>::scaleAddRows(int row1, int scale, int row2) {
	for (int col = 0; col < this->cols; col++) {
		values[row2 * this->cols + col] += values[row1 * this->cols + col] * scale;
	}
}

template <class T>
void Matrix<T>::scaleAddRows(int row1, float scale, int row2) {
	for (int col = 0; col < this->cols; col++) {
		values[row2 * this->cols + col] += values[row1 * this->cols + col] * scale;
	}
}

template <class T>
void Matrix<T>::scaleAddRows(int row1, double scale, int row2) {
	for (int col = 0; col < this->cols; col++) {
		values[row2 * this->cols + col] += values[row1 * this->cols + col] * scale;
	}
}

template <class T>
Matrix<T> Matrix<T>::extractColumns(int colsToExtract[], size_t size) {
	Matrix<T> result(this->getRows(), size);
	for (size_t i = 0; i < size; i++) {
		for (int row = 0; row < this->getRows(); row++) {
			result.set(row, i, this->get(row, colsToExtract[i]));
		}
	}

	return result;
}

template <class T>
void Matrix<T>::getColumn(T* buf, int col) {
	for (int i = 0; i < this->getRows(); i++) {
		buf[i] = this->get(i, col);
	}
}

template <class T>
void Matrix<T>::swapRows(int row1, int row2) {
	for (int col = 0; col < this->cols; col++) {
		T temp = values[row2 * this->cols + col];
		values[row2 * this->cols + col] = values[row1 * this->cols + col];
		values[row1 * this->cols + col] = temp;
	}
}


template <class T>
void Matrix<T>::scaleRow(int row, int scale) {
	for (int col = 0; col < this->cols; col++) {
		//values[row * this->cols + col] = values[row * this->cols + col] * scale;
		// maybe this is more efficient?
		this->set(row, col, this->get(row, col) * scale);
	}
}

template <class T>
void Matrix<T>::scaleRow(int row, float scale) {
	for (int col = 0; col < this->cols; col++) {
		this->set(row, col, this->get(row, col) * scale);
	}
}

template <class T>
void Matrix<T>::scaleRow(int row, double scale) {
	for (int col = 0; col < this->cols; col++) {
		this->set(row, col, this->get(row, col) * scale);
	}
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& mat) {
	Matrix<T> result(this->rows, this->cols);
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < this->cols; col++) {
			result.set(row, col, this->get(row, col) + mat.get(row, col));
		}
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& mat) {
	Matrix<T> result(this->rows, this->cols);
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < this->cols; col++) {
			result.set(row, col, this->get(row, col) - mat.get(row, col));
		}
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(int value) {
	Matrix<T> result(this->rows, this->cols);
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < this->cols; col++) {
			result.set(row, col, this->get(row, col) * value);
		}
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(float value) {
	Matrix<T> result(this->rows, this->cols);
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < this->cols; col++) {
			result.set(row, col, this->get(row, col) * value);
		}
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(double value) {
	Matrix<T> result(this->rows, this->cols);
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < this->cols; col++) {
			result.set(row, col, this->get(row, col) * value);
		}
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& mat) {
	Matrix<T> result(this->rows, mat.cols);
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < mat.getCols(); col++) {
			T sum = 0;
			//
			for (int i = 0; i < this->rows; i++) {
				sum += this->get(row, i) * mat.get(i, col);
			}
			//
			result.set(row, col, sum);
		}
	}
	return result;
}

template <class T>
std::string Matrix<T>::toString() {
	std::stringstream matString;

	matString << "[" << this->get(0, 0);
	for (int col = 1; col < this->cols; col++) {
		matString << ", " << this->get(0, col);
	}
	matString << "]";

	for (int row = 1; row < this->rows; row++) {
		matString << "\n[" << this->get(row, 0);
		for (int col = 1; col < this->cols; col++) {
			matString << ", " << this->get(row, col);
		}
		matString << "]";
	}
	return matString.str();
}

template <class T>
Matrix<T> operator*(int i, Matrix<T>& mat) {
	return mat * i;
}

template <class T>
Matrix<T> operator*(float i, Matrix<T>& mat) {
	return mat * i;
}

template <class T>
Matrix<T> operator*(double i, Matrix<T>& mat) {
	return mat * i;
}

template <class T>
T* Matrix<T>::operator[](int index) {
	return (this->values + index * this->getCols());
}

template <class U>
std::ostream& operator<<(std::ostream& os, Matrix<U>& mat) {
    return os << mat.toString();
};


#endif
