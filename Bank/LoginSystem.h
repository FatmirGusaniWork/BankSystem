//Name : Fatmir Gusani //
//Date : 20.06.2021 - 27.01.2022 //

#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

class LoginSystem {
public:
	// Main Functions //
	void SignInCode();
	void SignUpCode();
	int CheckPinCode(string checkPin, int functionOption);
	void PrintName();

	// Return Value //
	string PassFirstName(string rFirstName);
	string PassLastName(string rLastName);
	string PassCheckFirstName(string rCheckFirstName);
	string PassCheckLastName(string rCheckLastName);
	int PassBankPin(int bpin);
	int PassCheckBankPin(int checkbpin);
};

#endif
