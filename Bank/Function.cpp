//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#include "Register.h"


string fullName;
string BankPin;
string checkBankPin;
string checkFullName;
int num;
int tryAgain;

Register r;

void Register::SignUpCode()
{
	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	cout << "Enter your full name : ";
	cin >> fullName;
	cout << "" << endl;
	cout << "Enter Bank Pin : ";
	cin >> BankPin;

	cout << "Sign Up completed, BANK PIN : " + BankPin << endl;

	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	Sleep(3000);

	system("CLS");
	r.MainMenu();

}

void Register::SignInCode()
{
	int tryAgain;
	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;

	cout << "Enter your full name : ";
	cin >> checkFullName;
	cout << "" << endl;

	cout << "Enter Bank Pin : " << endl;
	cin >> checkBankPin;

	if (checkFullName == fullName && checkBankPin == BankPin)
	{
		system("CLS");
		r.MainMenu();
	}
	else
	{
		system("CLS");
		cout << "SIGN IN FAILED, Try Again" << endl;

		cout << "1 : Try Again\n2 : Sign Up\n3 : EXIT" << endl;
		cin >> tryAgain;
		switch (tryAgain)
		{
		case 1:
			SignInCode();
			break;
		case 2:
			SignUpCode();
			break;
		case 3:
			exit(0);
			break;
		default:
			cout << "Wrong Entry" << endl;
		}
	}
	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;
}

void Register::PickOption()
{
	Register r;
	int option;
	cout << "Wellcome, please pick one of the options available" << endl;
	cout << "1 : Sign In. \n2 : Sign Up." << endl;
	cin >> option;

	switch (option)
	{
	case 1:
		r.SignInCode();
		break;
	case 2:
		r.SignUpCode();
		break;
	default:
		cout << "Wrong Entery, Try Again" << endl;
		PickOption();
	}
}

void Register::PrintName()
{
	cout << "Welcome " + fullName + "\n";
}