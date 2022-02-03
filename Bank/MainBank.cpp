//Name : Fatmir Gusani //
//Date : 20.06.2021 - 27.01.2022 //
// This file allows the user to perform all the bank functions when they sign in to their account. //

using namespace std;

#include <string>
#include <iostream>
#include <windows.h>

// Personal Headers //
#include "BankSystem.h"
#include "MainBank.h"
#include "DatabaseSystem.h"
#include "LoginSystem.h"
#include "FileSystem.h"
#undef max

// This code is in charge of all the function calls used in the Bank system. //
void MainBank::MainMenu()
{
	FileSystem fs;
	BankSystem bs;

	int mainOption;

	// Displays all the current information to the user. //
	bs.DisplayBank();

	// MainOption allows the user to navigate through the Bank System. //
	cin >> mainOption;

	switch (mainOption)
	{
	case 1:
		// This case calls the Withdraw funtion from Bank System. //
		system("CLS");
		bs.Withdraw();
		break;

	case 2:
		// This case calls the Deposit function from the Bank System. //
		system("CLS");
		bs.Deposit();
		break;

	case 3:
		// This case calls the statement function from the File System. //
		system("CLS");
		fs.ReadStatement();
		system("pause");

		MainMenu();
		break;

	case 4:
		// This case calls the Tranfer function from the Bank System. //
		system("CLS");
		bs.Transfer();
		break;

	case 5:
		// This case calls the starting option function from the Bank System. //
		system("CLS");
		bs.StartingOption();
		break;

	default:
		// If the user enters a digit or letter that's not a case. //
		system("CLS");
		// Error message and they will be send to main menu. //
		cout << "Wrong Entery, Try Again" << endl;
		Sleep(3000);
		MainMenu();
	}
}