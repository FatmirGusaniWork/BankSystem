//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
//#include <sstream>
//#include <limits>
#include <stdlib.h>
#include <windows.h>
#include "Function.h"
#include "Bank.h"
#include "UserDB.h"
#include "UserDB.h"

#undef max

int option;
int amount;
int balance;
int getBankID;
int transforBankID;
int transforCash;

int PO;

void Bank::MainMenu()
{
	Function f;
	UserDB db;
	system("CLS");

	f.PrintName();

	cout << "Bank ID Number : " << db.PassBankID(getBankID) << endl;
	cout << "Balance : " << balance << endl;


	cout << "Please pick one of the options available" << endl;
	cout << "1 : Withdrawal. \n2 : Deposit.\n3 : Statement.\n4 : Send Money\n5 : Sign Out\n" << endl;
	cout << "Option : ";

	cin >> option;

	switch (option)
	{
	case 1:
		cout << "Enter withdraw amount : ";
		while (!(cin >> amount))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input" << endl;
			cout << "Enter withdraw amount : " << endl;
		}

		if (balance >= amount && amount > 0)
		{
			balance -= amount;
			cout << "Withdraw Successful" << endl;
			db.DatabaseOption(4);
			cout << "New Balance : " << balance << endl;
			PassBalance(balance);
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
			cout << "Invalid Input" << endl;
			cout << "Enter Deposit Amount : " << endl;
		}

		balance += amount;

		cout << "Doposit Successfully, ";
		db.DatabaseOption(4);
		cout << "New Balance : " << balance << endl;
		PassBalance(balance);


		Sleep(3000);
		system("CLS");
		MainMenu();
		break;

	case 3:
		//bank statement

		break;

	case 4:
		system("CLS");
		TransferMoney();
		break;

	case 5:
		system("CLS");
		f.PickOption();
		break;

	default:
		cout << "Wrong Entery, Try Again" << endl;
		Sleep(3000);
		system("CLS");
		MainMenu();
	}
}

void Bank::AdminMode()
{
	UserDB db;

	int adminOption;
	cout << "***************************************************" << endl;
	cout << "                Administrator Mode                 " << endl;
	cout << "***************************************************" << endl;

	cout << "Please pick one of the options available" << endl;
	cout << "1 : View Database.\n2 : Search Database.\n3: Update Details" << endl;

	cin >> adminOption;

	switch (adminOption)
	{
	case 1:
		system("CLS");
		db.DatabaseOption(2);
		AdminMode();
		break;
	case 2:
		system("CLS");
		db.DatabaseOption(3);
		Sleep(5000);
		AdminMode();
		break;

	case 3:
		system("CLS");
		db.DatabaseOption(6);
		Sleep(5000);
		break;

	case 4:
		system("CLS");
		db.DatabaseOption(5);
		Sleep(5000);
		break;

	default:
		cout << "Wrong Entery, Try Again" << endl;
		Sleep(3000);
		system("CLS");
		AdminMode();
	}
}


void Bank::EnterBalance()
{
	Function f;
	UserDB db;

	cout << "*************************************************************" << endl;
	cout << "Deposit needs to be between 5 and 1000 to create new account." << endl;
	cout << "Enter 0 to go back to Main Menu" << endl;
	cout << "*************************************************************" << endl;
	cout << "Enter Deposit Amount : ";

	while (!(cin >> balance))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		EnterBalance();
	}

	if (balance == 0)
	{
		system("CLS");
		f.PickOption();
	}

	else if (balance >= 5 && balance <= 1000)
	{
		db.DatabaseOption(1);
		cout << "Account Created Successful ..." << endl;
		Sleep(3000);
		system("CLS");
		MainMenu();
	}
	else
	{
		cout << "Error, not within the limits, try again" << endl;
		Sleep(3000);
		system("CLS");
		EnterBalance();
	}
}

int Bank::PassBalance(int bal)
{
	return balance;
}

void Bank::PassBalanceDetails(int& cash)
{
	balance = cash;
}

void Bank::TransferMoney()
{
	UserDB db;

	cout << "Enter Bank ID : ";
	cin >> transforBankID;

	cout << "Enter Amount : ";
	cin >> transforCash;

	if (balance >= transforCash && amount >= 0)
	{
		balance -= transforCash;
		db.DatabaseOption(4);
		db.DatabaseOption(6);
	}
	else
	{
		cout << "Transfor Failed...\nNot Enought Money";
		Sleep(3000);
		MainMenu();
	}
}

int Bank::PassTBankID(int Tid)
{
	return transforBankID;
}

int Bank::PassTCash(int Tcash)
{
	return balance;
}