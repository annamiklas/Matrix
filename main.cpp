#include "CMatrix.h"
#include <iostream>
#include<vector>
#include "CError.h"

using namespace std;
class CError;


int main() {
	CError* c_error;
	c_error = new CError;

	CMatrix<double> cd_square(3, 3, c_error);
	CMatrix<double> cd_square1(3, 3, c_error);
	CMatrix<double> cd_result(3, 3, c_error);


	CMatrix<int> ci_square(3, 3, c_error);
	CMatrix<int> ci_square1(3, 3, c_error);
	CMatrix<int> ci_result(3, 3, c_error);

	CMatrix<float> cf_square(3, 3, c_error);
	CMatrix<float> cf_square1(3, 3, c_error);
	CMatrix<float> cf_result(3, 3, c_error);

	////Wczytywanie double
	//c_error->vClear();
	//cd_square.vCreateMatrixFromFile("matDouOK.txt", c_error);
	//cout << c_error->sGetMessage();
	//cd_square.testPrint();
	//cout << endl;

	//c_error->vClear();
	//cd_square1.vCreateMatrixFromFile("matrixFail.txt", c_error);
	//cout << c_error->sGetMessage();
	//cd_square1.testPrint();
	//cout << endl;

	////Wczytywanie int
	//c_error->vClear();
	//ci_square.vCreateMatrixFromFile("matIntOK.txt", c_error);
	//cout << c_error->sGetMessage();
	//ci_square.testPrint();
	//cout << endl;
	//
	//c_error->vClear();
	//ci_square1.vCreateMatrixFromFile("matrixFail.txt", c_error);
	//cout << c_error->sGetMessage();
	//ci_square1.testPrint();
	//cout << endl;

	////Wczytywanie float
	//c_error->vClear();
	//cf_square.vCreateMatrixFromFile("matDouOK.txt", c_error);
	//cout << c_error->sGetMessage();
	//cf_square.testPrint();
	//cout << endl;

	//c_error->vClear();
	//cf_square1.vCreateMatrixFromFile("matrixFail.txt", c_error);
	//cout << c_error->sGetMessage();
	//cf_square1.testPrint();
	//cout << endl;

	////Tworzenie macierzy z kopiowaniem
	//c_error->vClear();
	//ci_square.vChangeDimentionOfMatrix(5, 5, c_error);
	//cout << c_error->sGetMessage();
	//cf_square.testPrint();
	//cout << endl;

	//c_error->vClear();
	//ci_square.vChangeDimentionOfMatrix(0, 5, c_error);
	//cout << c_error->sGetMessage();
	//cf_square.testPrint();
	//cout << endl;

	//
	////Pobieranie wartości
	//c_error->vClear();
	//cout << "Value at position: " << cd_square.tGetValFromPosition(1, 1, c_error) << endl;
	//cout << c_error->sGetMessage();
	//cout << endl;

	//c_error->vClear();
	//cout << "Value at position: " << cd_square.tGetValFromPosition(-1, 1, c_error) << endl;
	//cout << c_error->sGetMessage();
	//cout << endl;

	////Ustawianie wartości
	//c_error->vClear();
	//cf_square.vSetValOnPosition(-1, 1, 100, c_error);
	//cout << c_error->sGetMessage();
	//cf_square.testPrint();
	//cout << endl;

	//c_error->vClear();
	//cf_square.vSetValOnPosition(1, 1, 100, c_error);
	//cout << c_error->sGetMessage();
	//cf_square.testPrint();
	//cout << endl;


	////Dodawanie
	//c_error->vClear();
	//try {
	//	cd_result = cd_square + cd_square1;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cd_result.testPrint();
	//cout << endl;

	//CMatrix<double> cd_bad(3, 2, c_error);
	//c_error->vClear();
	//try {
	//	cd_result = cd_square + cd_bad;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cd_result.testPrint();
	//cout << endl;

	////Odejmowanie
	//c_error->vClear();
	//try {
	//	cf_result = cf_square - cf_square1;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cf_result.testPrint();
	//cout << endl;

	//CMatrix<float> cf_bad(3, 2, c_error);
	//c_error->vClear();
	//try {
	//	cf_result = cf_square - cf_bad;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cf_result.testPrint();
	//cout << endl;

	////Mnożenie
	//CMatrix<float> cf_mul1(3, 2, c_error);
	//CMatrix<float> cf_mul2(2, 3, c_error);
	//cf_mul1.testFill();
	//cf_mul2.testFill();
	//c_error->vClear();
	//try {
	//	cf_result = cf_mul1 * cf_mul2;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cf_result.testPrint();
	//cout << endl;

	//c_error->vClear();
	//try {
	//	cf_result = cf_mul1 * cf_bad;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cf_result.testPrint();
	//cout << endl;

	////Mnożenie przez liczbe
	//c_error->vClear();
	//try {
	//	cd_result = cd_square * 5;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cd_result.testPrint();
	//cout << endl;

	////Transponowanie
	//c_error->vClear();
	//try {
	//	~cd_result;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cd_result.testPrint();
	//cout << endl;

	////Jednostkowa
	//c_error->vClear();
	//cd_bad.vSetIdentity(c_error);
	//cout << c_error->sGetMessage();
	//cd_bad.testPrint();
	//cout << endl;

	//c_error->vClear();
	//cd_result.vSetIdentity(c_error);
	//cout << c_error->sGetMessage();
	//cd_result.testPrint();
	//cout << endl;

	////Wektory z kolumn i wierszy
	//c_error->vClear();
	//CMatrix<int> ci_vect_long = ci_square.cVectorCol(1, c_error);
	//cout << c_error->sGetMessage();
	//ci_vect_long.testPrint();
	//cout << endl;

	//c_error->vClear();
	//CMatrix<int> ci_vect2 = ci_square1.cVectorRow(1, c_error);
	//cout << c_error->sGetMessage();
	//ci_vect2.testPrint();
	//cout << endl;

	//ci_square.vChangeDimentionOfMatrix(3, 3, c_error);
	//c_error->vClear();
	//CMatrix<int> ci_vect1 = ci_square.cVectorCol(1, c_error);
	//cout << c_error->sGetMessage();
	//ci_vect1.testPrint();
	//cout << endl;

	//c_error->vClear();
	//CMatrix<int> ci_vect_bad = ci_square1.cVectorRow(10, c_error);
	//cout << c_error->sGetMessage();
	//ci_vect_bad.testPrint();
	//cout << endl;

	//c_error->vClear();
	//CMatrix<int> ci_vect1_bad = ci_square.cVectorCol(10, c_error);
	//cout << c_error->sGetMessage();
	//ci_vect1_bad.testPrint();
	//cout << endl;

	////Iloczyn skalarny

	//c_error->vClear();
	//cout <<"SCALAR PRODUCT " <<ci_vect2.tCountScalarProduct(ci_vect1, c_error)<< endl;
	//cout << c_error->sGetMessage();
	//cout << endl;

	//c_error->vClear();
	//cout << "SCALAR PRODUCT " << ci_vect_long.tCountScalarProduct(ci_vect1, c_error) << endl;
	//cout << c_error->sGetMessage();
	//cout << endl;

	////Operator dostępu
	//c_error->vClear();
	//try {
	//	cout << "VAL ON POSITION "<< cf_square[1][1];
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cout << endl;

	//c_error->vClear();
	//try {
	//	cout << cf_square[1000][1];
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cout << endl;

	//
	////Operator move =
	//c_error->vClear();
	//try {
	//	ci_square = move(ci_square1);
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//ci_square.testPrint();
	//cout << endl;


	////Operator =
	//c_error->vClear();
	//try {
	//	cd_square = cd_square1;
	//}
	//catch (const MatrixException& e) { cout << e.what() << endl; }
	//cd_square.testPrint();
	//cout << endl;

	//cout << endl;
	//cout << endl;
	//cout << endl;

	cout << "WCZYTANIE PRZYKLADOWYCH PLIKOW WSADOWYCH: " << endl;
	cout << endl;
	CMatrix<int> ci_example;
	CMatrix<double> cd_example;
	CMatrix<float> cf_example;
	cout << "MACIERZ INT" << endl;
	c_error->vClear();
	ci_example.vCreateMatrixFromFile("INT1.txt", c_error);
	cout << c_error->sGetMessage();
	ci_example.testPrint();
	cout << endl;
	cout << endl;

	c_error->vClear();
	ci_example.vAppendFromFromFile("INT.txt", 5, c_error);
	cout << c_error->sGetMessage();
	ci_example.testPrint();





	/*cout << "MACIERZ DOUBLE" << endl;
	c_error->vClear();
	cd_example.vCreateMatrixFromFile("DOUBLE.txt", c_error);
	cout << c_error->sGetMessage();
	cd_example.testPrint();
	cout << endl;
	cout << endl;
	cout << "MACIERZ FLOAT" << endl;
	c_error->vClear();
	cf_example.vCreateMatrixFromFile("DOUBLE.txt", c_error);
	cout << c_error->sGetMessage();
	cf_example.testPrint();
	cout << endl;
	cout << endl;
	cout << "PLIK DOUBLE DO MACIERZY INT" << endl;
	c_error->vClear();
	ci_example.vCreateMatrixFromFile("DOUBLE.txt", c_error);
	cout << c_error->sGetMessage();
	ci_example.testPrint();*/


	

}


