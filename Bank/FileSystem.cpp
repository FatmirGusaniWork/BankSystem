//Name : Fatmir Gusani //
//Date : 20.06.2021 - 27.01.2022 //
// This file is responsible for creating/reading/writing a file into the BankID folder in the C drive. //


using namespace std;

#include <iostream>
#include <string>

#include <ctime>
#include <fstream>
#include <direct.h>
#include <windows.h>

// Person Headers //
#include "BankSystem.h"
#include "MainBank.h"
#include "DatabaseSystem.h"
#include "LoginSystem.h"
#include "FileSystem.h"

#undef max

// The code below is used to create a file with the user's bankID as the name. //
// when the user makes a withdraw/depost or a transfer, the details will be saved into a file. //
// The write variables tells the code what action the user has performed. //
void FileSystem::Statement(int write)
{
	BankSystem bs;
	DatabaseSystem dbs;

	int printTransferCash;
	int printBalance;
	int printAmount;
	int printTransferBankID;
	int printBankID;

	bs.TBalanceValue(printTransferCash);
	bs.TBankIDValue(printTransferBankID);
	bs.PrintBalanceValue(printBalance);
	bs.AmountValue(printAmount);
	dbs.BankIDValue(printBankID);


	const char* path = "C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID//";

	_chdir(path);

	ofstream file(to_string(printBankID).c_str(), ios::app);

	time_t currentTime = time(0);
	char* dataTime = ctime(&currentTime);

	if (file.is_open())
	{
		if (write == 1)
		{
			file << "**************************************************";
			file << "WithDraw";
			file << "**************************************************";
			file << "\nBankID : " << printBankID;
			file << "\nCurrent Balance : " << printBalance;
			file << "\nAmount : " << printAmount;
			file << "\nOld Balance : " << printBalance + printAmount;
			file << "\nDate And Time : " << dataTime;
			file << "**************************************************";
			file << "WithDraw";
			file << "**************************************************\n\n";

			file.close();
		}

		if (write == 2)
		{
			file << "**************************************************";
			file << "Deposit";
			file << "**************************************************";
			file << "\nBankID : " << printBankID;
			file << "\nCurrent Balance : " << printBalance;
			file << "\nAmount : " << printAmount;
			file << "\nOld Balance : " << printBalance - printAmount;
			file << "\nDate And Time : " << dataTime;
			file << "**************************************************";
			file << "Deposit";
			file << "**************************************************\n\n";

			file.close();
		}

		if (write == 3)
		{
			file << "**************************************************";
			file << "Transfer";
			file << "**************************************************";
			file << "\nBankID : " << printBankID;
			file << "\nCurrent Balance : " << printBalance;
			file << "\nTransfer Amount : " << printTransferCash;
			file << "\nOld Balance : " << printBalance + printTransferCash;
			file << "\nTransfer BankID : " << printTransferBankID;
			file << "\nDate And Time : " << dataTime;
			file << "**************************************************";
			file << "Transfer";
			file << "**************************************************\n\n";

			file.close();
		}
	}
}

// Thie code allows the user to read their bank statement. //
void FileSystem::ReadStatement()
{
	DatabaseSystem dbs;

	int readBankID;
	string fileContext;

	dbs.BankIDValue(readBankID);

	const char* path = "C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID//";
	_chdir(path);

	ifstream MyReadFile(to_string(readBankID).c_str(), ios::app);

	while (getline(MyReadFile, fileContext)) {

		cout << fileContext << endl;
	}
	MyReadFile.close();

}

// This part of the code can only be accessed by an Admin. //
// This code allows the admin to read the statement of all the user's in the Bank system along as they have the bankID. //
void FileSystem::SearchStatement()
{
	int searchStatement;
	string fileContext;

	cout << "Enter BankID Statement that you want to read : ";
	cin >> searchStatement;

	const char* path = "C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID//";
	_chdir(path);

	ifstream MyReadFile(to_string(searchStatement).c_str(), ios::app);

	while (getline(MyReadFile, fileContext)) {

		cout << fileContext << endl;
	}
	MyReadFile.close();
}