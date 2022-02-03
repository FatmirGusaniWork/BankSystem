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

// Personal Headers //

#include "BankSystem.h"
#include "MainBank.h"
#include "DatabaseSystem.h"
#include "LoginSystem.h"
#include "FileSystem.h"
#undef max

// The code below is used to create a file with the user's bankID as the name. //
// when the user makes a withdrawal/deposit or a transfer, the details will be saved into a file. //
// The write variables tell the code what action the user has performed. //
void FileSystem::Statement(int write)
{
	BankSystem bs;
	DatabaseSystem dbs;

	int printTransferCash;
	int printBalance;
	int printAmount;
	int printTransferBankID;
	int printBankID;

	// Function call to get the right information. //
	bs.TBalanceValue(printTransferCash);
	bs.TBankIDValue(printTransferBankID);
	bs.PrintBalanceValue(printBalance);
	bs.AmountValue(printAmount);
	dbs.BankIDValue(printBankID);

	// Gets path to the right folder in C drive.
	const char* path = "C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID//";

	// changes the directory to the right location in my C drive. //
	_chdir(path);

	// Covert printBankpin to a string and saves it a the file name. //
	ofstream file(to_string(printBankID).c_str(), ios::app);
	
	// Gets the current time and date from the computer. //
	time_t currentTime = time(0);
	char* dataTime = ctime(&currentTime);

	// Opens the file. //
	if (file.is_open())
	{
		// After the user makes a withdrawal, the information is saved into the file. //
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

			// Once the information is written into the file, it closes. //
			file.close();
		}

		// After the user makes a deposit, the information is saved into the file. //
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

			// Once the information is written into the file, it closes. //
			file.close();
		}

		// After the user makes a transfer, the information is saved into the file. //
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

			// Once the information is written into the file, it closes. //
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

	// Get the current BankID from the database saves the value into readBankID. //
	dbs.BankIDValue(readBankID);

	// Path to right location in the C drive. //
	const char* path = "C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID//";

	// Changes to the dircorty to the path. //
	_chdir(path);

	// Coverts readBankID to string and opens the file with that name. //
	ifstream MyReadFile(to_string(readBankID).c_str(), ios::app);

	// Reads and prints the details inside the file. //
	while (getline(MyReadFile, fileContext)) {

		cout << fileContext << endl;
	}
	
	// Closes the file. //
	MyReadFile.close();
}

// This part of the code can only be accessed by an Admin. //
// This code allows the admin to read the statement of all the user's in the Bank system as long as they have the bankID. //
void FileSystem::SearchStatement()
{
	int searchStatement;
	string fileContext;

	// Asks the Admin to enter the BankID of the statement that they want to read. //
	cout << "Enter BankID Statement that you want to read : ";
	cin >> searchStatement;

	// Path to right location in the C drive. //
	const char* path = "C://Users//Fatmir//source//repos//FatmirGusaniWork//Bank//BankID//";

	// Changes to the dircorty to the path. //
	_chdir(path);

	// Coverts searchStatement to string and opens the file with that name. //
	ifstream MyReadFile(to_string(searchStatement).c_str(), ios::app);

	// Reads and prints the details inside the file. //
	while (getline(MyReadFile, fileContext)) {

		cout << fileContext << endl;
	}

	// Closes the file. //
	MyReadFile.close();
}