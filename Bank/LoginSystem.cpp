//Name : Fatmir Gusani // 
//Date : 20.06.2021 - 27.01.2022 //
// This file is responeable for the Signing Up and Signing In part of the Bank system. //


using namespace std;

#include <string>
#include <iostream>

#include <windows.h>
#include <algorithm>
#include <sstream>

// Person Headers //
#include "BankSystem.h"
#include "MainBank.h"
#include "DatabaseSystem.h"
#include "LoginSystem.h"
#include "FileSystem.h"

#undef max

// SignUpCode() // PrintName() //
string firstName;
string lastName;
int bankPin;

// SignInCode() // PrintName() //
string checkFirstName;
string checkLastName;
int checkBankPin;

// CheckPinCode() //
string checkNumber;

// PrintName() //
int PrintOption;

// This function allows the user to sign up to the bank system. //
// It asks the the user basic information that is added to the database. //
// Before the account is created, the user has to add a minimum balance. //
// This is done using the RegisterBalance(). //
void LoginSystem::SignUpCode()
{
	BankSystem bs;

	PrintOption = 1;
	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	cout << "Enter First Name : ";
	cin >> firstName;

	cout << "Enter Last Name : ";
	cin >> lastName;

	CheckPinCode(checkNumber, 1);

	cout << "Sign Up completed, BANK PIN : " << bankPin << endl;

	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	Sleep(3000);
	system("CLS");
	bs.RegisterBalance();
}

// This code of the code allows the user to sign into their accounts or enter Administrator Mode. //
// Asks the user to enter basic information and uses the details to check if it matchs with the database in the DatabaseOption() //
// If the users detail doesn't match the database, it allows the user to try again, sign up or return to the starting screen. // 
void LoginSystem::SignInCode()
{
	BankSystem bs;
	DatabaseSystem dbs;

	PrintOption = 2;
	int tryAgain;
	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;

	cout << "Enter First Name : ";
	cin >> checkFirstName;

	cout << "Enter Last Name : ";
	cin >> checkLastName;

	CheckPinCode(checkNumber, 2);

	dbs.DatabaseOption(5);

	if (checkFirstName == "Admin" && checkLastName == "Mode" && checkBankPin == 0)
	{
		system("CLS");
		bs.AdminMode();
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
			bs.StartingOption();
			break;
		default:
			cout << "Wrong Entry" << endl;
		}
	}

	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;
}

// The Code Below checks if the user entered 6 digits pin code. //
// I added some error checking to see if the user entered number or letters and to make sure there is 6 entery. //
// This code is used to check the bank pin code for SignUp() and SignIn(). //
int LoginSystem::CheckPinCode(string checkPin, int functionOption)
{
	cout << "\nEnter Bank Pin : ";
	cin >> checkPin;

	// Checks if there is 6 entery //
	if (checkPin.length() == 6)
	{
		bool b = false;
		if (!checkPin.empty() && std::all_of(checkPin.begin(), checkPin.end(), [](char c) {return std::isdigit(c); }))
		{
			b = true;
			stringstream convert(checkPin);
			if (functionOption == 1)
				convert >> bankPin;
			if (functionOption == 2)
				convert >> checkBankPin;
		}
		else
		{
			if (functionOption == 1)
			{
				cout << "Error, Letters Entered.\nEntered 6 digits Pin." << endl;
				CheckPinCode(checkPin, 1);
			}
		}
	}
	else
	{
		if (functionOption == 1)
		{
			cout << "Error, Entered Pin is Not 6 digits." << endl;
			CheckPinCode(checkPin, 1);
		}
	}
	if (functionOption == 1)
		return bankPin;
	if (functionOption == 2)
		return checkBankPin;
}

// This code simply prints out the users first and last name. //
// It uses the PrintOption variable to deturnment if the user is SignUp() or SignIn(). //
void LoginSystem::PrintName()
{
	if (PrintOption == 1)
		cout << "                    " << firstName + " " + lastName + "\n";

	if (PrintOption == 2)
		cout << "                    " << checkFirstName + " " + checkLastName + "\n";
}

// Returning Variables //

string LoginSystem::PassFirstName(string rFirstName)
{
	return firstName;
}

string LoginSystem::PassLastName(string rLastName)
{
	return lastName;
}

string LoginSystem::PassCheckFirstName(string rCheckFirstName)
{
	return checkFirstName;
}

string LoginSystem::PassCheckLastName(string rCheckLastName)
{
	return checkLastName;
}

int LoginSystem::PassBankPin(int bpin)
{
	return bankPin;
}

int LoginSystem::PassCheckBankPin(int checkbpin)
{
	return checkBankPin;
}