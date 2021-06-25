//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#include "Register.h"


void Register::MainMenu()
{
	Register r;
	int option;
	int balance = 10;
	int amount;
	r.PrintName();
	cout << + balance << endl;

	cout << "Please pick one of the options available" << endl;
	cout << "1 : Withdrawal. \n2 : Deposit.\n3 : Statement.\n4 : Sign Out.\n" << endl;

	cin >> option;

	switch (option)
	{
	case 1:
		cout << "Enter Withdraw Amount : " << endl;
		cin >> amount;

		balance -= amount;

		if (balance <= 0)
		{
			cout << "Withdraw Unsuccessfully";
			cout << "Not Enought Money." << balance << endl;
		}
		else
		{
			cout << "Withdraw Successfully";
			cout << "New balance : " + balance << endl;
		}

		Sleep(3000);
		system("CLS");
		MainMenu();
		break;
	case 2:
		cout << "Enter Deposit Amount : " << endl;
		cin >> amount;

		balance += amount;

		cout << "Doposit Successfully ";
		cout << balance << endl;

		Sleep(3000);
		system("CLS");
		MainMenu();

		break;
	case 3:
		//bank statement

		break;

	case 4:
		r.PickOption();
		break;
	default:
		cout << "Wrong Entery, Try Again" << endl;
		MainMenu();
	}
}