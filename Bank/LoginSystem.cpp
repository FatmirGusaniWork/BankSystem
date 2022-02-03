//Name : Fatmir Gusani // 
//Date : 20.06.2021 - 27.01.2022 //
// This file is responsible for the Signing Up and Signing In part of the bank system. //

using namespace std;

#include <string>
#include <iostream>

#include <windows.h>
#include <algorithm>
#include <sstream>

// Personal Headers //
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
void LoginSystem::SignUpCode()
{
	BankSystem bs;

	PrintOption = 1;
	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	// Requests basic information from the user. //
	cout << "Enter First Name : ";
	cin >> firstName;

	cout << "Enter Last Name : ";
	cin >> lastName;

	// Sends a '1' to CheckPinCode(), this tells the code that we are checking the bank pin for SignUpCode(). //
	CheckPinCode(checkNumber, 1);

	// After the user enters their bank pin and it passes all the requirements. //
	cout << "Sign Up completed, BANK PIN : " << bankPin << endl;

	cout << "*********************************************" << endl;
	cout << "********************Sign Up******************" << endl;

	Sleep(3000);
	system("CLS");

	// The user asked to make a deposit. //
	bs.RegisterBalance();
}

// This code allows the user to sign into their accounts. //
// Asks the user to enter basic information and uses the details to check if it matches with the database in the DatabaseOption() //
// If the user detail doesn't match the database, it allows the user to try again, sign up or return to the starting screen. // 
void LoginSystem::SignInCode()
{
	BankSystem bs;
	DatabaseSystem dbs;

	int tryAgain;

	PrintOption = 2;

	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;

	// Asks the user for basic information that will be compared to the database. //
	cout << "Enter First Name : ";
	cin >> checkFirstName;

	cout << "Enter Last Name : ";
	cin >> checkLastName;

	CheckPinCode(checkNumber, 2);

	// Entered information will be used in DatabaseOption() [case 5]. //
	dbs.DatabaseOption(5);

	// If the entered information doesn't match any user in the database. //
	// An error will occur, the user will have a few options to pick from. //
	system("CLS");
	cout << "SIGN IN FAILED, Try Again" << endl;

	cout << "1 : Try Again\n2 : Sign Up\n3 : EXIT" << endl;
	cin >> tryAgain;
	switch (tryAgain)
	{
	case 1:
		// The user can try again. //
		system("CLS");
		SignInCode();
		break;
	case 2:
		// Sign up if the user doesn't have an account. //
		system("CLS");
		SignUpCode();
		break;
	case 3:
		// Can go back to the starting screen. //
		system("CLS");
		bs.StartingOption();
		break;
	default:
		cout << "Wrong Entry" << endl;
	}

	cout << "*********************************************" << endl;
	cout << "********************Sign In******************" << endl;
}

// The Code Below checks if the user entered a six digits pin. //
// It also checks if the entries are numbers or letters. //
// This code is used to check the bank pin code for SignUp() and SignIn(). //
int LoginSystem::CheckPinCode(string checkPin, int functionOption)
{
	// Asks the user to enter a 6 digit pin code. //
	cout << "\nEnter Bank Pin : ";
	cin >> checkPin;

	// Checks if there is 6 entery //
	if (checkPin.length() == 6)
	{
		bool b = false;

		// checks if any of the entries is a letter. //
		if (!checkPin.empty() && std::all_of(checkPin.begin(), checkPin.end(), [](char c) {return std::isdigit(c); }))
		{
			b = true;
			stringstream convert(checkPin);
			// FunctionOption = 1 means that we are checking the pincode for SignUpCode(). //
			if (functionOption == 1)
				// Saves checkpin as bank pin. //
				convert >> bankPin;

			// FunctionOption = 2 means that we are checking the pincode for SignInCode(). //
			if (functionOption == 2)
				// Saves checkpin as check bank pin. //
				convert >> checkBankPin;
		}
		else
		{
			// If the entry has letters. //
			if (functionOption == 1)
			{
				cout << "Error, Letters Entered.\nEntered 6 digits Pin." << endl;
				CheckPinCode(checkPin, 1);
			}
		}
	}
	else
	{
		// If the entry has more or less than 6 digits. //
		if (functionOption == 1)
		{
			cout << "Error, Entered Pin is Not 6 digits." << endl;
			CheckPinCode(checkPin, 1);
		}
	}
	if (functionOption == 1)
	// Returns the saved bank pin. //
		return bankPin;

	// Returns the saved check bank pin. //
	if (functionOption == 2)
		return checkBankPin;
}

// This code simply prints out the users first and last name. //
// It uses the PrintOption variable to determine if the user is SignUp() or SignIn(). //
void LoginSystem::PrintName()
{
	// Prints first and last name for SignUpCode(). //
	if (PrintOption == 1)
		cout << "                    " << firstName + " " + lastName + "\n";

	// Prints first and last name for SignInCode(). //
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