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

	string PassFirstName(string firstname);
	string PassLastName(string lastname);

	string PassCheckFN(string checkfirstname);
	string PassCheckLN(string checklastname);

	int PassBankPin(int bpin);
	int EnterPin(string test, int whichfunction);
};

#endif
