//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#include "Register.h"
#undef max


string fullName;
string checkFullName;
int checkBankPin;
int BankPin;
int tryAgain;

Register r;

void Register::SignUpCode()
{
	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	cout << "Enter Full Name : ";
	cin.ignore();
	getline(cin, fullName);

	cout << "\nEnter Bank Pin : ";
	while (!(cin >> BankPin))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << endl;
		cout << "Enter Pin : " << endl;
	}

	cout << "Sign Up completed, BANK PIN : " << BankPin << endl;

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
	getline(cin, checkFullName);

	cout << "\nEnter Bank Pin : " << endl;
	while (!(cin >> BankPin))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << endl;
		cout << "Enter Pin : " << endl;
	}

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
	cout << "Welcome " << fullName + "\n";
}