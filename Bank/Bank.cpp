//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;


#include <string>
#include <iostream>
#include <fstream>  

#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#include "Function.h"
#include "Bank.h"
#include "UserDB.h"
#undef max


int option;
int amount;

int balance;
int getBankID;
int BankID;

int transferBankID;
int transferCash;

int PO;

void Bank::MainMenu()
{
	Function f;
	UserDB db;
	system("CLS");
	cout << "**************************************************" << endl;
	f.PrintName();
	cout << "**************************************************" << endl;
	db.PassABankID(BankID);
	cout << "Bank ID Number : " << BankID << endl;
	cout << "Balance : " << balance << endl;
	cout << "Please pick one of the options available" << endl;
	cout << "1 : Withdrawal. \n2 : Deposit.\n3 : Statement.\n4 : Send Money\n5 : Sign Out\n" << endl;
	cout << "Option : ";

	cin >> option;

	switch (option)
	{
	case 1:
		system("CLS");
		cout << "**************************************************" << endl;
		cout << "                     WithDraw                     " << endl;
		cout << "**************************************************" << endl;

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
			Statement(1);
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
		system("CLS");
		cout << "**************************************************" << endl;
		cout << "                      Deposit                     " << endl;
		cout << "**************************************************" << endl;
		cout << "Enter Deposit Amount : " << endl;

		while (!(cin >> amount))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input" << endl;
			cout << "Enter Deposit Amount : " << endl;
		}

		balance += amount;

		cout << "Doposit Successfully" << endl;
		db.DatabaseOption(4);
		cout << "New Balance : " << balance << endl;
		Statement(2);
		PassBalance(balance);


		Sleep(3000);
		system("CLS");
		MainMenu();
		break;

	case 3:
		break;

	case 4:
		system("CLS");
		cout << "**************************************************" << endl;
		cout << "                     Transfer                     " << endl;
		cout << "**************************************************" << endl;

		cout << "Enter Bank ID : ";
		cin >> transferBankID;

		cout << "Enter Amount : ";
		cin >> transferCash;

		if (balance >= transferCash && amount >= 0)
		{
			balance -= transferCash;
			db.DatabaseOption(4);
			Statement(3);
			db.DatabaseOption(6);
			
		}
		else
		{
			cout << "Transfor Failed...\nNot Enought Money";
			Sleep(3000);
			MainMenu();
		}

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
	cout << "1 : View Database.\n2 : Search Database.\n3 : Sign Out" << endl;

	cout << "\nOption : ";
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
		Function f;
		f.PickOption();
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

int Bank::PassTBankID(int Tid)
{
	return transferBankID;
}

void Bank::PassTCash(int& Tcash)
{
	Tcash = transferCash;
}

void Bank::ReturnBankID(int& ID)
{
	ID = BankID;
}

void Bank::PrintTime()
{

}

void Bank::Statement(int pick)
{
	UserDB db;
	
	
	//std::to_string(BankID).c_str();

	//_mkdir("C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID");
	const char* path = "C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID//T1.txt";
	ofstream file(std::to_string(BankID).c_str(), ios::app);
	
	

	if (file.is_open())
	{
		if (pick == 1)
		{
			file << "\n**************************************************";
			file << "WithDraw";
			file << "**************************************************";
			file << "\nBankID : " << db.PassBankID(getBankID);
			file << "\nCurrent Balance : " << balance;
			file << "\nAmount : " << amount;
			file << "\nOld Balance : " << balance + amount;
			file << "\n**************************************************";
			file << "WithDraw";
			file << "**************************************************\n";

			file.close();
		}

		if (pick == 2)
		{
			file << "\n**************************************************";
			file << "Deposit";
			file << "**************************************************";
			file << "\nBankID : " << db.PassBankID(getBankID);
			file << "\nCurrent Balance : " << balance;
			file << "\nAmount : " << amount;
			file << "\nOld Balance : " << balance - amount;
			file << "\n**************************************************";
			file << "Deposit";
			file << "**************************************************\n";

			file.close();
		}

		if (pick == 3)
		{

			file << "\n**************************************************";
			file << "Transfer";
			file << "**************************************************";
			file << "\nBankID : " << BankID;
			file << "\nCurrent Balance : " << balance;
			file << "\nTransfer Amount : " << transferCash;
			file << "\nOld Balance : " << balance + transferCash;
			file << "\nTransfer BankID : " << transferBankID;
			file << "\n**************************************************";
			file << "Transfer";
			file << "**************************************************\n";

			file.close();
		}
	}


	/*
	if (pick == 4)
	{
		file << "\n**************************************************";
		file << "Transfer";
		file << "**************************************************";
		file << "\nBankID : " << db.PassBankID(getBankID);
		file << "\nCurrent Balance : " << balance;
		file << "\nTransfer Amount : " << transferCash;
		file << "\nOld Balance : " << balance - amount;
		file << "\nTransfer BankID : " << transferBankID;
		file << "\n**************************************************";
		file << "Transfer";
		file << "**************************************************\n";
		file.close();
	}
	*/

}