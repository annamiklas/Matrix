#pragma once
#include <iostream>
#include <exception>

using namespace std;
class MatrixException: public exception {

public:
	MatrixException(const string& sMessage) { s_message = sMessage;  }
	~MatrixException() {}
	virtual const char* what() const noexcept override
	{
		return s_message.c_str();
	}
	string sGetMessage() const { return(s_message); }
private:
	string s_message;
};

