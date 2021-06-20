//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Register.h"

class Function
{
private:
	string fullName;
	string BankPin;
	string checkBankPin;
	string checkFullName;
	int num;
	int tryAgain;

public:
	Register r;

	void SignUpCode()
	{
		cout << "*********************************************" << endl;
		cout << "********************Sign Up******************" << endl;

		cout << "Enter your full name : ";
		cin >> fullName;
		cout << "" << endl;

		cout << "Enter a pin.\n *NOTE* Don't make the pin easy and don't forget it." << endl;


		while (!(cin >> BankPin))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "WRONG ENTRY" << endl;

			cout << BankPin;
		}

		stringstream ss;
		ss << BankPin;
		ss >> num;

		cout << BankPin << endl;
		cout << num << endl;


		cout << "Sign Up completed, BANK PIN : " + BankPin << endl;

		cout << "*********************************************" << endl;
		cout << "********************Sign Up******************" << endl;
	}

	void SignInCode()
	{
		cout << "*********************************************" << endl;
		cout << "********************Sign In******************" << endl;

		cout << "Enter your full name : ";
		cin >> checkFullName;
		cout << "" << endl;

		cout << "Enter Bank Pin : " << endl;
		for (int i = 0; i < 6; i++)
		{
			cin >> checkBankPin;
			cout << "*";
		}

		if (checkFullName == fullName && checkBankPin == BankPin)
		{
			cout << "WELCOME " + fullName << endl;
			//Enter Code that bring the user to main screen.
		}
		else
		{
			cout << "SIGN IN FAILED, Try Again" << endl;
			cout << "1 : Try Again\n2 : Sign Up\n3 : Home" << endl;
			switch (tryAgain)
			{
			case 1:
				SignInCode();
				break;
			case 2:
				SignUpCode();
				break;
			case 3:
				r.PickOption();
				break;
			default:
				cout << "Wrong Entry" << endl;
				
			}
		}
		cout << "*********************************************" << endl;
		cout << "********************Sign In******************" << endl;
	}
};