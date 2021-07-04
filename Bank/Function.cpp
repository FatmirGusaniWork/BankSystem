//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include "Register.h"
#undef max


string fullName;
string checkFullName;
string test;
int checkBankPin;
int BankPin;
int tryAgain;
//int whichfunction;
char characterCkeck = 0;



Register r;

void Register::SignUpCode()
{
	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	cout << "Enter Full Name : ";
	cin.ignore();
	getline(cin, fullName);

	EnterPin(test, 1);

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
	cin.ignore();
	getline(cin, checkFullName);

	EnterPin(test, 2);

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


int Register::EnterPin(string test, int whichfunction)
{
	cout << "\nEnter Bank Pin : ";
	cin >> test;

	if (test.length() == 6)
	{
		bool b = false;
		if (!test.empty() && std::all_of(test.begin(), test.end(), [](char c) {return std::isdigit(c); })) 
		{
			b = true;
			stringstream convert(test);
			if(whichfunction == 1)
				convert >> BankPin;
			if (whichfunction == 2)
				convert >> checkBankPin;
		}
		else
		{
			if (whichfunction == 1)
			{
				cout << "Error, Letters Entered.\nEntered 6 digits Pin." << endl;
				EnterPin(test, 1);
			}
		}
	}
	else
	{
		if (whichfunction == 1)
		{
			cout << "Error, Entered Pin is Not 6 digits." << endl;
			EnterPin(test, 1);
		}
	}
	if (whichfunction == 1)
		return BankPin;
	if (whichfunction == 2)
		return checkBankPin;
}