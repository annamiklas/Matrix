#pragma once

#include <string>

using namespace std;

static const int NO_ERROR = 0;
//1-- - SIZE ERROR
static const int INVALID_VALUE_OF_X_SIZE = 100;
static const int INVALID_X_SIZE_OF_ARGUMENT = 101;
static const int INVALID_VALUE_OF_Y_SIZE = 102;
static const int INVALID_Y_SIZE_OF_ARGUMENT = 103;
static const int INCORRECT_INDEX_X = 104;
static const int INCORRECT_INDEX_Y = 105;
static const int INVALID_DIMENTIONS_OF_MATRIXES = 106;
static const int INVALID_DIMENTIONS_OF_VECTOR = 107;
static const int INVALID_X_SIZE_OF_NEW_MATRIX = 108;
static const int INVALID_Y_SIZE_OF_NEW_MATRIX = 109;

//2-- - FILE ERROR
static const int INVALID_FILE_NAME = 200;
static const int INVALID_ELEMENT = 201;
static const int INVALID_SEPARATOR = 202;
static const int INCORRECT_COLUMN_LENGTH = 203;

//3-- - MEMORY ERROR
static const int MEMORY_ALLOCATION_FAILURE = 300;


class CError
{
public:
	CError() { i_code = NO_ERROR;  }
	int iGetErrorCode() { return i_code; }
	void vSetErrorCode(int iCode) { i_code = iCode; }
	void vSetErrorCodeIfEmpty(int iCode) { if(bIsNoError()) i_code = iCode; }
	bool bIsNoError() { return i_code == NO_ERROR; }
	string sGetMessage() { return "ERROR CODE: " + to_string(i_code); }
	void vClear() { i_code = NO_ERROR; }

private:
	int i_code;

};

