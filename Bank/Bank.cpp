//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <stdlib.h>
#include <windows.h>
#include "Register.h"
#include "SQLDB.h"
#undef max

int balance = 5;
int option;
int amount;

void Register::PassBalance(int passBalance)
{
	passBalance = balance;
}

void Register::MainMenu()
{
	Register r;

	r.PrintName();

	cout << "Balance : " <<  balance << endl;

	cout << "Please pick one of the options available" << endl;
	cout << "1 : Withdrawal. \n2 : Deposit.\n3 : Statement.\n4 : Sign Out.\n" << endl;
	
	cin >> option;

	switch (option)
	{
	case 1:
		cout << "Enter withdraw amount : ";
		while (!(cin >> amount))
		{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input" << endl;
				cout << "Enter withdraw amount : " << endl;
		}

		if (balance >= amount && amount > 0)
		{
			cout << balance << endl;
			balance -= amount;
			cout << "Withdraw Successful" << endl;
			cout << "New Balance : " << balance << endl;
		}
		else
		{
			cout << "Withdraw Denied" << endl;
			cout << "Not Enought Money" << endl;
			cout << "Balance : " << balance << endl;
		}

		Sleep(3000);
		system("CLS");
		MainMenu();
		break;

	case 2:
		cout << "Enter Deposit Amount : " << endl;

		while (!(cin >> amount)) 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input" << endl;
			cout << "Enter Deposit Amount : " << endl;
			
		}

		balance += amount;

		cout << "Doposit Successfully ";
		cout << "Balance : " << balance << endl;

		Sleep(3000);
		system("CLS");
		MainMenu();

		break;

	case 3:
		//bank statement

		break;

	case 4:
		system("CLS");
		r.PickOption();
		break;

	default:
		cout << "Wrong Entery, Try Again" << endl;
		Sleep(3000);
		system("CLS");
		MainMenu();
	}
}