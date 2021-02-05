#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "const.h"
#include "CError.h"
#include "MatrixExeption.h"
#include "COperatorHelper.h"

using namespace std;

class CError;

template <typename T>
class CMatrix
{
public:

	CMatrix();
	CMatrix(int iRowSize, int iColSize, CError* pcErrorCode);
	CMatrix(const CMatrix& cOther, CError* pcErrorCode);
	CMatrix(CMatrix&& cOther);
	~CMatrix();

	void vChangeDimentionOfMatrix(int iRow, int iCol,CError* pcErrorCode, int iValToFill = DEF_VALUE);
	void vCreateEmptyMatrix(int iRow, int iCol, CError* pcErrorCode);
	T tGetValFromPosition(int iRow, int iCol, CError* pcErrorCode);
	void vSetValOnPosition(int iRow, int iCol, T tVal, CError* pcErrorCode);
	CMatrix<T> cVectorRow(int iRow, CError* pcErrorCode);
	CMatrix<T> cVectorCol(int iCol, CError* pcErrorCode);
	CMatrix<T> cAddMatrix(const CMatrix<T>& cOther, CError* pcErrorCode);
	CMatrix<T> cSubMatrix(const CMatrix<T>& cOther, CError* pcErrorCode);
	CMatrix<T> cMultMatrix(const CMatrix<T>& cOther, CError* pcErrorCode);
	CMatrix<T> cMultMatrixByNumber(T tMult, CError* pcErrorCode);
	void vTransponate(CError* pcErrorCode);
	T tCountScalarProduct(CMatrix<T>& cOther, CError* pcErrorCode);
	void vSetIdentity(CError* pcErrorCode);
	void vCreateMatrixFromFile(string sFile, CError* pcErrorCode);
	void vAppendFromFromFile(string sFile, int iValToFill,  CError* pcErrorCode);

	void operator=(const CMatrix<T>& cOther);
	void operator=(CMatrix<T>&& cOther);
	CMatrix operator+(const CMatrix& cOther);
	CMatrix operator-(const CMatrix& cOther);
	CMatrix operator*(const CMatrix& cOther);
	CMatrix operator*(T tMult);
	void operator~();
	COperatorHelper<T> operator[](int iIndex);

	void testFill();
	void testFillAndPrint();
	void testPrint();

private:

	int i_row_size;
	int i_col_size;
	T** t_matrix;

	void vCreateMatrixOfSize(int iRow, int iCol, CError* pcErrorCode = NULL);
	void vMoveMatrix(CMatrix<T>& cOther);
	void vFillMatrix(T tVal);
	void vCopyMatrix(const CMatrix<T>& cOther);
	void vDeleteMatrix();
	T** pcInitialMatrix(int iRow, int iCol);

	COperatorHelper<T> cRowGetter(int iRowIndex, CError* pcErrorCode);

	int* pcCountColAndRowNumber(string sFile, CError* pcErrorCode);
	void vCreateMatrixOfSizeFromFile(int iRow, int iCol, string sFile, CError* pcErrorCode);
	int iParseCharToInt(char ch_sing, CError* pcErrorCode);
	T tParseStringToNumber(string sNumber, CError* pcErrorCode);
	int iNumberMultByPowOfTen(int iNumb, int iPow);
	double dNumberMultByNegativePowOfTen(int iNumb, int iPow);
};

template <typename T>
CMatrix<T>::CMatrix() {
	vCreateMatrixOfSize(DEF_ROW_SIZE, DEF_COL_SIZE);
}

template <typename T>
CMatrix<T>::CMatrix(int iRowSize, int iColSize, CError* pcErrorCode) {
	vCreateMatrixOfSize(iRowSize, iColSize, pcErrorCode);
}

template <typename T>
CMatrix<T>::CMatrix(const CMatrix& cOther, CError* pcErrorCode) {
	vDeleteMatrix();
	vCreateMatrixOfSize(cOther.i_row_size, cOther.i_col_size, pcErrorCode);
	vCopyMatrix(cOther);
}

template <typename T>
CMatrix<T>::CMatrix(CMatrix&& cOther) {
	vMoveMatrix(cOther);
}

template <typename T>
CMatrix<T>::~CMatrix() {
	vDeleteMatrix();
}

template <typename T>
void CMatrix<T>::operator=(const CMatrix<T>& cOther) {
	CError c_error;
	vCreateEmptyMatrix(cOther.i_row_size, cOther.i_col_size, &c_error);
	vCopyMatrix(cOther);
	if (!c_error.bIsNoError()) throw MatrixException(c_error.sGetMessage());

}

template <typename T>
void CMatrix<T>::operator=(CMatrix<T>&& cOther) {
	vMoveMatrix(cOther);
}

template <typename T>
void CMatrix<T>::vChangeDimentionOfMatrix(int iRow, int iCol, CError* pcErrorCode, int iValToFill) {
	if (iRow <= 0) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_X_SIZE_OF_NEW_MATRIX);
	else if (iCol <= 0) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_Y_SIZE_OF_NEW_MATRIX);
	else {
		T** t_temp_matrix = pcInitialMatrix(iRow, iCol);
		for (int i = 0; i < iRow; i++)
			for (int j = 0; j < iCol; j++) {
				if (i < i_row_size && j < i_col_size)
					t_temp_matrix[i][j] = t_matrix[i][j];
				else
					t_temp_matrix[i][j] = iValToFill;
			}
		vDeleteMatrix();
		i_col_size = iCol;
		i_row_size = iRow;
		t_matrix = t_temp_matrix;
	}
}

template <typename T>
void CMatrix<T>::vCreateEmptyMatrix(int iRow, int iCol, CError* pcErrorCode) {
	if (iRow <= 0) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_X_SIZE_OF_NEW_MATRIX);
	else if (iCol <= 0) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_Y_SIZE_OF_NEW_MATRIX);
	else {
		T** t_temp_matrix = new T * [iRow];
		for (int i = 0; i < iRow; i++)
			t_temp_matrix[i] = new T[iCol];
		vDeleteMatrix();
		i_col_size = iCol;
		i_row_size = iRow;
		t_matrix = t_temp_matrix;
	}
}

template <typename T>
void CMatrix<T>::vSetValOnPosition(int iRow, int iCol, T tVal, CError* pcErrorCode) {
	if (iRow <= 0 || iRow > i_row_size) pcErrorCode->vSetErrorCodeIfEmpty(INCORRECT_INDEX_X);
	else if (iCol <= 0 || iCol > i_col_size) pcErrorCode->vSetErrorCodeIfEmpty(INCORRECT_INDEX_Y);
	else
		t_matrix[iCol][iRow] = tVal;
}

template <typename T>
T CMatrix<T>::tGetValFromPosition(int iRow, int iCol, CError* pcErrorCode) {
	if (iRow <= 0 || iRow > i_row_size) pcErrorCode->vSetErrorCodeIfEmpty(INCORRECT_INDEX_X);
	else if (iCol <= 0 || iCol > i_col_size) pcErrorCode->vSetErrorCodeIfEmpty(INCORRECT_INDEX_Y);
	else
		return t_matrix[iRow][iCol];
	return std::numeric_limits<double>::quiet_NaN();
}

template <typename T>
CMatrix<T> CMatrix<T>::operator+(const CMatrix<T>& cOther) {
	CError c_error;
	CMatrix<T> c_result = move(cAddMatrix(cOther, &c_error));
	if (!c_error.bIsNoError()) throw MatrixException(c_error.sGetMessage());

	return move(c_result);
}

template <typename T>
CMatrix<T> CMatrix<T>::cAddMatrix(const CMatrix<T>& cOther, CError* pcErrorCode) {
	CMatrix<T> c_matrix_new(i_row_size, i_col_size, pcErrorCode);
	if (t_matrix == NULL || cOther.t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else if (i_row_size != cOther.i_row_size || i_col_size != cOther.i_col_size) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_DIMENTIONS_OF_MATRIXES);
	else
		for (int i = 0; i < cOther.i_row_size; i++)
			for (int j = 0; j < cOther.i_col_size; j++)
				c_matrix_new.t_matrix[i][j] = t_matrix[i][j] + cOther.t_matrix[i][j];
	return move(c_matrix_new);
}

template <typename T>
CMatrix<T> CMatrix<T>::operator-(const CMatrix<T>& cOther) {
	CError c_error;
	CMatrix<T> c_result = move(cSubMatrix(cOther, &c_error));
	if (!c_error.bIsNoError()) throw MatrixException(c_error.sGetMessage());
	return move(c_result);
}

template <typename T>
CMatrix<T> CMatrix<T>::cSubMatrix(const CMatrix<T>& cOther, CError* pcErrorCode) {
	CMatrix<T> c_matrix_new(i_row_size, i_col_size, pcErrorCode);
	if (t_matrix == NULL || cOther.t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else if (i_row_size != cOther.i_row_size || i_col_size != cOther.i_col_size) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_DIMENTIONS_OF_MATRIXES);
	for (int i = 0; i < cOther.i_row_size; i++)
		for (int j = 0; j < cOther.i_col_size; j++)
			c_matrix_new.t_matrix[i][j] = t_matrix[i][j] - cOther.t_matrix[i][j];
	return move(c_matrix_new);
}

template <typename T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix<T>& cOther) {
	CError c_error;
	CMatrix<T> c_result = move(cMultMatrix(cOther, &c_error));
	if (!c_error.bIsNoError()) throw MatrixException(c_error.sGetMessage());
	return move(c_result);
}

template <typename T>
CMatrix<T> CMatrix<T>::cMultMatrix(const CMatrix<T>& cOther, CError* pcErrorCode) {
	CMatrix<T> c_matrix_new(i_row_size, cOther.i_col_size, pcErrorCode);
	if (t_matrix == NULL || cOther.t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else if (i_col_size != cOther.i_row_size) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_DIMENTIONS_OF_MATRIXES);
	else {
		T t_sum = 0;
		for (int i = 0; i < i_row_size; i++)
			for (int j = 0; j < cOther.i_col_size; j++) {
				t_sum = 0;
				for (int k = 0; k < cOther.i_row_size; k++)
					t_sum += t_matrix[i][k] * cOther.t_matrix[k][j];
				c_matrix_new.t_matrix[i][j] = t_sum;
			}
	}
	return move(c_matrix_new);
}

template <typename T>
CMatrix<T> CMatrix<T>::operator*(T tMult) {
	CError c_error;
	CMatrix<T> c_result = move(cMultMatrixByNumber(tMult, &c_error));
	if (!c_error.bIsNoError()) throw MatrixException(c_error.sGetMessage());
	return move(c_result);
}

template <typename T>
CMatrix<T> CMatrix<T>::cMultMatrixByNumber(T tMult, CError* pcErrorCode) {
	CMatrix<T> c_matrix_new(i_row_size, i_col_size, pcErrorCode);
	if (t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else
		for (int i = 0; i < i_row_size; i++)
			for (int j = 0; j < i_col_size; j++)
				c_matrix_new.t_matrix[i][j] = tMult * t_matrix[i][j];
	return move(c_matrix_new);
}

template <typename T>
void CMatrix<T>::operator~() {
	CError c_error;
	vTransponate(&c_error);
	if (!c_error.bIsNoError()) throw MatrixException(c_error.sGetMessage());
}

template <typename T>
void CMatrix<T>::vTransponate(CError* pcErrorCode) {
	if (t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else {
		T** t_temp_matrix = pcInitialMatrix(i_row_size, i_col_size);
		for (int i = 0; i < i_row_size; i++)
			for (int j = 0; j < i_col_size; j++)
				t_temp_matrix[i][j] = t_matrix[j][i];
		vDeleteMatrix();
		t_matrix = t_temp_matrix;
		int i_row_temp = i_row_size;
		i_row_size = i_col_size;
		i_col_size = i_row_temp;

	}
}

template <typename T>
void CMatrix<T>::vSetIdentity(CError* pcErrorCode) {
	if (t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else if (i_row_size != i_col_size) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_DIMENTIONS_OF_MATRIXES);
	else {
		vFillMatrix(0);
		for (int i = 0; i < i_row_size; i++)
			t_matrix[i][i] = 1;
	}
}

template <typename T>
T CMatrix<T>::tCountScalarProduct(CMatrix<T>& cOther, CError* pcErrorCode) {
	T t_result = std::numeric_limits<double>::quiet_NaN();
	if (t_matrix == NULL || cOther.t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else if (!(i_row_size == 1 && cOther.i_row_size == 1 && i_col_size == cOther.i_col_size)) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_DIMENTIONS_OF_VECTOR);
	else {
		t_result = 0;
		for (int i = 0; i < i_col_size; i++)
			t_result += t_matrix[0][i] * cOther.t_matrix[0][i];
	}
	return t_result;
}

template <typename T>
CMatrix<T> CMatrix<T>::cVectorRow(int iRow, CError* pcErrorCode) {
	CMatrix<T> c_new_vector(1, i_row_size, pcErrorCode);
	if (t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else if (iRow <= 0 || iRow > i_row_size) pcErrorCode->vSetErrorCodeIfEmpty(INCORRECT_INDEX_X);
	else
		for (int i = 0; i < i_col_size; i++)
			c_new_vector.t_matrix[0][i] = t_matrix[iRow][i];
	return move(c_new_vector);
}

template <typename T>
CMatrix<T> CMatrix<T>::cVectorCol(int iCol, CError* pcErrorCode) {
	CMatrix<T> c_new_vector(1, i_col_size, pcErrorCode);
	if (t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else if (iCol < 0 || iCol >= i_col_size) pcErrorCode->vSetErrorCodeIfEmpty(INCORRECT_INDEX_Y);
	else
		for (int i = 0; i < i_col_size; i++)
			c_new_vector.t_matrix[0][i] = t_matrix[i][iCol];
	return move(c_new_vector);
}

template <typename T>
COperatorHelper<T> CMatrix<T>::operator[](int iRowIndex) {
	CError c_error;
	COperatorHelper<T> c_row = cRowGetter(iRowIndex, &c_error);
	if (!c_error.bIsNoError()) throw MatrixException(c_error.sGetMessage());
	return move(c_row);
}

template <typename T>
void CMatrix<T>::vCreateMatrixFromFile(string sFile, CError* pcErrorCode) {
	int* i_size = pcCountColAndRowNumber(sFile, pcErrorCode);
	int i_col_numb = i_size[0];
	int i_row_numb = i_size[1];
	if (i_row_numb <= 0 && pcErrorCode->bIsNoError()) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_X_SIZE_OF_NEW_MATRIX);
	else if (i_col_numb <= 0 && pcErrorCode->bIsNoError()) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_Y_SIZE_OF_NEW_MATRIX);
	else {
		vCreateEmptyMatrix(i_row_numb, i_col_numb, pcErrorCode);
		vFillMatrix(DEF_VALUE);
		vCreateMatrixOfSizeFromFile(i_row_numb, i_col_numb, sFile, pcErrorCode);
	}

}


template <typename T>
void CMatrix<T>::vAppendFromFromFile(string sFile, int iValToFill, CError* pcErrorCode) {
	int i_old_row = i_row_size;
	int* i_size = pcCountColAndRowNumber(sFile, pcErrorCode);
	int i_col_numb = max(i_size[0], i_col_size);
	int i_row_numb = i_row_size + i_size[1];

	if (i_row_numb <= 0 && pcErrorCode->bIsNoError()) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_X_SIZE_OF_NEW_MATRIX);
	else if (i_col_numb <= 0 && pcErrorCode->bIsNoError()) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_Y_SIZE_OF_NEW_MATRIX);
	vChangeDimentionOfMatrix(i_row_numb, i_col_numb, pcErrorCode, iValToFill);
	CMatrix<T> c_mat_from_file(i_size[1], i_size[0], pcErrorCode);
	c_mat_from_file.vCreateMatrixOfSizeFromFile(i_size[1], i_size[0], sFile, pcErrorCode);

	for (int i = i_old_row; i < i_row_numb; i++) {
		for (int j = 0; j < i_size[0]; j++) {
			t_matrix[i][j] = c_mat_from_file.t_matrix[i - i_old_row ][j];
		}
	}
}


// Private method

template <typename T>
void CMatrix<T>::vCreateMatrixOfSizeFromFile(int iRow, int iCol, string sFile, CError* pcErrorCode) {
	fstream s_file;
	s_file.open(sFile, ios::in);
	if (!s_file.good()) {
		pcErrorCode->vSetErrorCodeIfEmpty(INVALID_FILE_NAME);
	}
	else {
		string s_line;
		int i_curr_row = 0;
		int i_curr_col = 0;
		string s_curr_number = "";
		while (getline(s_file, s_line)) {
			s_curr_number = "";
			i_curr_col = 0;
			for (int i = 0; i < s_line.length() + 1; i++) {
				if (s_line[i] == SEPARATOR || i == s_line.length()) {
					t_matrix[i_curr_row][i_curr_col] = tParseStringToNumber(s_curr_number, pcErrorCode);
					s_curr_number = "";
					i_curr_col++;
					if (i < s_line.length())   // delete multi spaces beetwen
						while (s_line[i + 1] == SEPARATOR) {
							if (i <= s_line.length()) i++;
							pcErrorCode->vSetErrorCodeIfEmpty(INVALID_SEPARATOR);
						}
					if (i + 1 == s_line.length() && s_line[i] == SEPARATOR)  // delete space at the end
						i = s_line.length() + 1;
				}
				else 
					s_curr_number += s_line[i];
			}
			i_curr_row++;
		}
		s_file.close();
	}
}

template <typename T>
T CMatrix<T>::tParseStringToNumber(string sNumber, CError* pcErrorCode) {
	return T();
}

template <>
inline int CMatrix<int>::tParseStringToNumber(string sNumber, CError* pcErrorCode) {
	bool b_is_neagtive = false;
	if (sNumber[0] == NEGATIVE_SING) b_is_neagtive = true;
	int i_val = 0;
	int i_curr_val = 0;
	for (int i = b_is_neagtive; i < sNumber.length(); i++) {
		i_curr_val = iParseCharToInt(sNumber[i], pcErrorCode);
		if (i_curr_val == INVALID_CHAR) return DEF_VALUE;
		i_val += iNumberMultByPowOfTen(i_curr_val, sNumber.length() - i);
	}
	if (b_is_neagtive) i_val *= -1;
	return i_val;
}

template <>
inline double CMatrix<double>::tParseStringToNumber(string sNumber, CError* pcErrorCode) {
	bool b_is_neagtive = false;
	double d_val = 0;
	double d_curr_val = 0;
	int i_id_of_sep = sNumber.length();
	if (sNumber[0] == NEGATIVE_SING) b_is_neagtive = true;
	for (int i = b_is_neagtive; i < sNumber.length(); i++) 
		if (sNumber[i] == ',' || sNumber[i] == '.')  
			i_id_of_sep = i;

	for (int i = b_is_neagtive; i < i_id_of_sep; i++) {
		d_curr_val = iParseCharToInt(sNumber[i], pcErrorCode);
		if (d_curr_val == -1) return DEF_VALUE;
		d_val += iNumberMultByPowOfTen(d_curr_val, i_id_of_sep - i);
	}

	for (int i = i_id_of_sep + 1; i < sNumber.length(); i++) {
		d_curr_val = iParseCharToInt(sNumber[i], pcErrorCode);
		if (d_curr_val == -1) return DEF_VALUE;
		d_val += dNumberMultByNegativePowOfTen(d_curr_val,  i - i_id_of_sep);
	}
	if (b_is_neagtive) d_val *= -1;
	return d_val;
}

template <>
inline float CMatrix<float>::tParseStringToNumber(string sNumber, CError* pcErrorCode) {
	bool b_is_neagtive = false;
	float f_val = 0;
	float f_curr_val = 0;
	int i_id_of_sep = sNumber.length();
	if (sNumber[0] == NEGATIVE_SING) b_is_neagtive = true;
	for (int i = b_is_neagtive; i < sNumber.length(); i++) 
		if (sNumber[i] == ',' || sNumber[i] == '.')
			i_id_of_sep = i;

	for (int i = b_is_neagtive; i < i_id_of_sep; i++) {
		f_curr_val = iParseCharToInt(sNumber[i], pcErrorCode);
		if (f_curr_val == -1) return DEF_VALUE;
		f_val += iNumberMultByPowOfTen(f_curr_val, i_id_of_sep - i);
	}
	for (int i = i_id_of_sep + 1; i < sNumber.length(); i++) {
		f_curr_val = iParseCharToInt(sNumber[i], pcErrorCode);
		if (f_curr_val == -1) return DEF_VALUE;
		f_val += dNumberMultByNegativePowOfTen(f_curr_val, i - i_id_of_sep);
	}
	if (b_is_neagtive) f_val *= (-1);
	return f_val;
}


template <typename T>
double CMatrix<T>::dNumberMultByNegativePowOfTen(int iNumb, int iPow) {
	double d_number = iNumb;
	for (int i = 0; i < iPow; i++) {
		d_number *= BASE_OF_NEGATIVE_POWER;
	}
	return d_number;
}

template <typename T>
int CMatrix<T>::iNumberMultByPowOfTen(int iNumb, int iPow) {
	int i_number = iNumb;
	for (int i = 1; i < iPow; i++) {
		i_number *= BASE_OF_POWER;
	}
	return i_number;
}

template <typename T>
int CMatrix<T>::iParseCharToInt(char ch_sing, CError* pcErrorCode) {
	switch (ch_sing) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		pcErrorCode->vSetErrorCodeIfEmpty(INVALID_ELEMENT);
		return INVALID_CHAR;
	}
}

template <typename T>
int* CMatrix<T>::pcCountColAndRowNumber(string sFile, CError* pcErrorCode) {
	int i_max_row = 0;
	int i_max_col = 0;
	int i_numb_col = 1;
	int* pc_size = new int[2];
	fstream s_file;
	s_file.open(sFile, ios::in);
	if (!s_file.good()) {
		if (pcErrorCode->bIsNoError()) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_FILE_NAME);
		pc_size[0] = 0; pc_size[1] = 0;
		return pc_size;
	}
	else {
		string s_line;
		int i_curr_col = 0;
		string s_curr_number = "";
		while (getline(s_file, s_line)) {
			s_curr_number = "";
			i_curr_col = 0;
			for (int i = 0; i < s_line.length() + 1; i++) {
				if (s_line[i] == SEPARATOR || i == s_line.length()) {
					i_curr_col++;
					if (i < s_line.length())   // delete multi spaces beetwen
						while (s_line[i + 1] == SEPARATOR) {
							if (i <= s_line.length()) i++;
							pcErrorCode->vSetErrorCodeIfEmpty(INVALID_SEPARATOR);
						}
					if (i + 1 == s_line.length() && s_line[i] == SEPARATOR)  // delete space at the end
						i = s_line.length() + 1;
				}
			}
			if (i_curr_col > i_max_col) i_max_col = i_curr_col;
			if(i_curr_col != i_max_col) i_numb_col++;
			i_max_row++;
		}
		s_file.close();
	}
	if (i_numb_col > 1)
		pcErrorCode->vSetErrorCodeIfEmpty(INCORRECT_COLUMN_LENGTH);
	pc_size[0] = i_max_col; pc_size[1] = i_max_row;
	return pc_size;
}

template <typename T>
COperatorHelper<T> CMatrix<T>::cRowGetter(int iRowIndex, CError* pcErrorCode) {
	COperatorHelper<T> c_row(i_col_size);
	if (t_matrix == NULL) pcErrorCode->vSetErrorCodeIfEmpty(MEMORY_ALLOCATION_FAILURE);
	else if (iRowIndex <= 0 || iRowIndex > i_row_size) pcErrorCode->vSetErrorCodeIfEmpty(INCORRECT_INDEX_X);
	else
		c_row.vSetMatrix(t_matrix[iRowIndex]);
	return move(c_row);
}

template <typename T>
void CMatrix<T>::vDeleteMatrix() {
	if (t_matrix != NULL)
		for (int i = 0; i < i_row_size; i++)
			if (t_matrix[i] != NULL)
				delete[] t_matrix[i];
	delete t_matrix;
}

template <typename T>
void CMatrix<T>::vCreateMatrixOfSize(int iRow, int iCol, CError* pcErrorCode) {
	if (iRow < 0) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_VALUE_OF_X_SIZE);
	else if (iCol < 0) pcErrorCode->vSetErrorCodeIfEmpty(INVALID_VALUE_OF_Y_SIZE);

	if (iRow > 0 && iCol > 0) {
		i_row_size = iRow;
		i_col_size = iCol;
		t_matrix = new T * [iRow];
		for (int i = 0; i < iRow; i++)
			t_matrix[i] = new T[iCol];
	}
	else {
		i_row_size = DEF_ROW_SIZE;
		i_col_size = DEF_COL_SIZE;
		t_matrix = new T * [DEF_ROW_SIZE];
		for (int i = 0; i < DEF_ROW_SIZE; i++)
			t_matrix[i] = new T[DEF_COL_SIZE];
	}

}

template <typename T>
void CMatrix<T>::vFillMatrix(T tVal) {
	for (int i = 0; i < i_row_size; i++) {
		for (int j = 0; j < i_col_size; j++) {
			t_matrix[i][j] = tVal;
		}
	}
}

template <typename T>
void CMatrix<T>::vCopyMatrix(const CMatrix<T>& cOther) {
	for (int i = 0; i < i_row_size; i++) {
		for (int j = 0; j < i_col_size; j++)
			t_matrix[i][j] = cOther.t_matrix[i][j];
	}
}

template <typename T>
void CMatrix<T>::vMoveMatrix(CMatrix<T>& cOther) {
	i_row_size = cOther.i_row_size;
	i_col_size = cOther.i_col_size;
	t_matrix = cOther.t_matrix;
	cOther.t_matrix = NULL;
	cOther.i_row_size = 0;
	cOther.i_col_size = 0;
}

template <typename T>
T** CMatrix<T>::pcInitialMatrix(int iRow, int iCol) {
	T** t_temp_matrix = NULL;
	if (iRow > 0 && iCol > 0) {
		t_temp_matrix = new T * [iRow];
		for (int i = 0; i < iRow; i++)
			t_temp_matrix[i] = new T[iCol];
	}
	return t_temp_matrix;
}



template <typename T>
void CMatrix<T>::testFillAndPrint() {
	for (int i = 0; i < i_row_size; i++)
		for (int j = 0; j < i_col_size; j++)
			t_matrix[i][j] = i + 1;

	for (int i = 0; i < i_row_size; i++) {
		cout << endl;
		for (int j = 0; j < i_col_size; j++)
			cout << t_matrix[i][j] << " ";
	}

}

template <typename T>
void CMatrix<T>::testFill() {
	for (int i = 0; i < i_row_size; i++)
		for (int j = 0; j < i_col_size; j++)
			t_matrix[i][j] = i + 1;
}

template <typename T>
void CMatrix<T>::testPrint() {
	for (int i = 0; i < i_row_size; i++) {
		cout << endl;
		for (int j = 0; j < i_col_size; j++)
			cout << t_matrix[i][j] << " ";
	}
}


