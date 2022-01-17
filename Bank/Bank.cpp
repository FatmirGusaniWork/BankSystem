//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;


#include <string>
#include <iostream>
#include <fstream>  

#include <ctime>

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
int checkExist;

void Bank::MainMenu()
{
	Function f;
	UserDB db;

	system("CLS");
	cout << "**************************************************" << endl;
	f.PrintName();
	cout << "**************************************************" << endl;

	CheckRefund();
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
			cout << "Enter withdraw amount : ";
		}

		if (balance >= amount && amount > 0)
		{
			balance -= amount;
			cout << "Withdraw Successful" << endl;

			db.DatabaseOption(4);
			cout << "New Balance : " << balance << endl;
			Statement(1,1);
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
		cout << "Enter Deposit Amount : ";

		while (!(cin >> amount))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input" << endl;
			cout << "Enter Deposit Amount : ";
		}

		balance += amount;

		cout << "Doposit Successfully" << endl;
		db.DatabaseOption(4);
		cout << "New Balance : " << balance << endl;
		Statement(1,2);
		PassBalance(balance);
		Sleep(3000);
		system("CLS");
		MainMenu();
		break;

	case 3:
		system("CLS");
		
		Statement(2, 4);
		system("pause");

		MainMenu();
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
			//balance -= transferCash;
			db.DatabaseOption(4);
			Statement(1,3);
			balance -= transferCash;
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


void Bank::CheckRefund()
{
	UserDB db;

	if (db.Refund(checkExist) == 2)
	{
		balance += transferCash;
	}
}

void Bank::Statement(int readOrwrite ,int pick)
{
	if (readOrwrite == 1)
	{
		const char* path = "C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID//";

		_chdir(path);

		//ofstream object("C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID");
		ofstream file(to_string(BankID).c_str(), ios::app);

		time_t currentTime = time(0);
		char* dataTime = ctime(&currentTime);


		//ofstream file(path, ios::app);
		if (file.is_open())
		{
			if (pick == 1)
			{
				file << "**************************************************";
				file << "WithDraw";
				file << "**************************************************";
				file << "\nBankID : " << BankID;
				file << "\nCurrent Balance : " << balance;
				file << "\nAmount : " << amount;
				file << "\nOld Balance : " << balance + amount;
				file << "\nDate And Time : " << dataTime;
				file << "**************************************************";
				file << "WithDraw";
				file << "**************************************************\n\n";

				file.close();
			}

			if (pick == 2)
			{
				file << "**************************************************";
				file << "Deposit";
				file << "**************************************************";
				file << "\nBankID : " << BankID;
				file << "\nCurrent Balance : " << balance;
				file << "\nAmount : " << amount;
				file << "\nOld Balance : " << balance - amount;
				file << "\nDate And Time : " << dataTime;
				file << "**************************************************";
				file << "Deposit";
				file << "**************************************************\n\n";

				file.close();
			}

			if (pick == 3)
			{
				file << "**************************************************";
				file << "Transfer";
				file << "**************************************************";
				file << "\nBankID : " << BankID;
				file << "\nCurrent Balance : " << balance;
				file << "\nTransfer Amount : " << transferCash;
				file << "\nOld Balance : " << balance + transferCash;
				file << "\nTransfer BankID : " << transferBankID;
				file << "\nDate And Time : " << dataTime;
				file << "**************************************************";
				file << "Transfer";
				file << "**************************************************\n\n";

				file.close();
			}
		}
	}
	if (readOrwrite == 2)
	{
		if (pick == 4)
		{
			string fileContext;

			ifstream MyReadFile(to_string(BankID).c_str(), ios::app);

			while (getline(MyReadFile, fileContext)) {
				
				cout << fileContext << endl;
			}
			MyReadFile.close();
		}
		
	}
}