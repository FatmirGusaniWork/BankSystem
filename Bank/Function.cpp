//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include "Function.h"
#include "UserDB.h"
#include "Bank.h"
#undef max

string checkFirstName;
string checkLastName;
string firstName;
string lastName;
string test;

string testpass;

int checkBankPin;
int bankPin;
int tryAgain;

int PrintOption;

UserDB db;
Bank b;
Function f;

void Function::SignUpCode()
{
	PrintOption = 1;

	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	cout << "Enter First Name : ";
	cin >> firstName;

	cout << "Enter Last Name : ";
	cin >> lastName;

	EnterPin(test, 1);

	cout << "Sign Up completed, BANK PIN : " << bankPin << endl;

	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	Sleep(3000);
	system("CLS");
	b.EnterBalance();
}

void Function::SignInCode()
{
	PrintOption = 2;
	int tryAgain;
	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;

	cout << "Enter First Name : ";
	cin >> checkFirstName;

	cout << "Enter Last Name : ";
	cin >> checkLastName;

	EnterPin(test, 2);
	db.DatabaseOption(5);


	if (checkFirstName == "Admin" && checkLastName == "Mode" && checkBankPin == 0)
	{
		system("CLS");
		b.AdminMode();
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
			system("CLS");
			SignInCode();
			break;
		case 2:
			system("CLS");
			SignUpCode();
			break;
		case 3:
			system("CLS");
			PickOption();
			break;
		default:
			cout << "Wrong Entry" << endl;
		}
	}

	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;
}

void Function::PickOption()
{
	//Register r;
	int option;
	cout << "Wellcome, please pick one of the options available" << endl;
	cout << "1 : Sign In. \n2 : Sign Up. \n3 : Exit Program. \n" << endl;
	cout << "Option : ";

	cin >> option;

	system("CLS");

	switch (option)
	{
	case 1:
		SignInCode();
		break;
	case 2:
		SignUpCode();
		break;
	case 3:
		exit(0);
	default:
		cout << "Wrong Entery, Try Again" << endl;
		PickOption();
	}
}

int Function::EnterPin(string test, int whichfunction)
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
			if (whichfunction == 1)
				convert >> bankPin;
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
		return bankPin;
	if (whichfunction == 2)
		return checkBankPin;
}

void Function::PrintName()
{
	if(PrintOption == 1)
		cout << "Welcome " << firstName + " " + lastName + "\n";
	if(PrintOption == 2)
		cout << "Welcome " << checkFirstName + " " + checkLastName + "\n";
}


string Function::PassValueOption(string value, int option)
{
	if (option == 1)
		return firstName;
	if (option == 2)
		return lastName;
	if (option == 3)
		return checkFirstName;
	if (option == 4)
		return checkLastName;
}

int Function::PassBankPin(int bpin)
{
	return bankPin;
}

int Function::PassCheckBankPin(int checkbpin)
{
	return checkBankPin;
}
