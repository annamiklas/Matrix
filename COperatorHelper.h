#pragma once
#include "CError.h"
template <typename T>
class COperatorHelper {
public:
	COperatorHelper(int iColSize) { i_col_size = iColSize; }
	T operator[](int iColIndex);
	T tValGetter(int iColIndex, CError* pcErrorCode);
	void vSetMatrix(T* pcMatrix) { pc_matrix = pcMatrix; }

private:
	T* pc_matrix;
	int i_col_size;
};

template <typename T>
T COperatorHelper<T>::operator[](int iColIndex) {
	CError c_error;
	T t_val = tValGetter(iColIndex, &c_error);
	if (c_error.iGetErrorCode() != NO_ERROR) throw MatrixException("ERROR CODE: " + c_error.iGetErrorCode());
	return t_val;
}

template <typename T>
T COperatorHelper<T>::tValGetter(int iColIndex, CError* pcErrorCode) {
	if (iColIndex <= 0 || iColIndex > i_col_size) pcErrorCode->vSetErrorCode(INCORRECT_INDEX_Y);
	else
		return pc_matrix[iColIndex];
}
