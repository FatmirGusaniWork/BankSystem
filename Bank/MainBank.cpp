//Name : Fatmir Gusani //
//Date : 20.06.2021 - 27.01.2022 //
// This file allows the user to perform all the bank functions when the sign in to their account. //

using namespace std;

#include <string>
#include <iostream>
#include <windows.h>

// Person Headers //
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

	bs.DisplayBank();

	cin >> mainOption;

	switch (mainOption)
	{
	case 1:
		system("CLS");
		bs.Withdraw();
		break;

	case 2:
		system("CLS");
		bs.Deposit();
		break;

	case 3:
		system("CLS");
		fs.ReadStatement();
		system("pause");

		MainMenu();
		break;

	case 4:
		system("CLS");
		bs.Transfer();
		break;

	case 5:
		system("CLS");
		bs.StartingOption();
		break;

	default:
		system("CLS");

		cout << "Wrong Entery, Try Again" << endl;
		Sleep(3000);
		MainMenu();
	}
}