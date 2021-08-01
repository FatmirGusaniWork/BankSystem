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

string firstName;
string lastName;
string checkFirstName;
string checkLastName;
string test;

int checkBankPin;
int bankPin;
int tryAgain;

Function f;
UserDB db;
Bank b;


void Function::PassFullname(string passfirstName, string passlastName)
{
	firstName = passfirstName;
	lastName = passlastName;
}

void Function::SignUpCode()
{
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

	db.InsertDatabase();

	Sleep(3000);

	//Testing DataBase Viewing
	db.ViewDatabase();

	Sleep(5000);

	system("CLS");
	b.MainMenu();

}

void Function::SignInCode()
{
	int tryAgain;
	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;

	cout << "Enter First Name : ";
	cin >> checkFirstName;

	cout << "Enter Last Name : ";
	cin >> checkLastName;

	EnterPin(test, 2);

	if (checkFirstName == firstName && checkLastName == lastName && checkBankPin == bankPin)
	{
		system("CLS");
		b.MainMenu();
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

void Function::PickOption()
{
	//Register r;
	int option;
	cout << "Wellcome, please pick one of the options available" << endl;
	cout << "1 : Sign In. \n2 : Sign Up." << endl;
	cin >> option;

	switch (option)
	{
	case 1:
		f.SignInCode();
		break;
	case 2:
		f.SignUpCode();
		break;
	default:
		cout << "Wrong Entery, Try Again" << endl;
		PickOption();
	}
}

void Function::PrintName()
{
	cout << "Welcome " << firstName + " " + lastName +  "\n";
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
			if(whichfunction == 1)
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