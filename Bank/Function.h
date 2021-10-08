//Name : Fatmir Gusani
//Date : 20.06.2021

#ifndef FUNCTION_H
#define FUNCTION_H

class Function {
public:
	void SignInCode();
	void SignUpCode();
	void PickOption();
	void PrintName();

	int EnterPin(string test, int whichfunction);
	string PassValueOption(string value, int option);
	int PassBankPin(int bpin);
	int PassCheckBankPin(int checkbpin);
};

#endif
