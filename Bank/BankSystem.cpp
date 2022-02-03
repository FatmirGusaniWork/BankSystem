//Name : Fatmir Gusani //
//Date : 20.06.2021 - 27.01.2022 //

using namespace std;

#include <string>
#include <iostream>

#include <windows.h>
#include <algorithm>
#include <sstream>

// Personal Headers //
#include "BankSystem.h"
#include "MainBank.h"
#include "DatabaseSystem.h"
#include "LoginSystem.h"
#include "FileSystem.h"

#undef max

LoginSystem ls;
FileSystem fs;
BankSystem bs;
DatabaseSystem dbs;

// Display() // Withdraw() // Deposit() // Transfer() // RegisterBalance() //
int balance;
int amount;

// DisplayBank() //
int displayBankID;

// Transfer()  //
int transferCash;
int transferBankID;

// When the user runs the program, This is the first function that runs. //
// It helps the user navigate through the bank. //
void BankSystem::StartingOption()
{
	int option;

	cout << "Wellcome, please pick one of the options available" << endl;
	cout << "1 : Sign In. \n2 : Sign Up. \n3 : Exit Program. \n" << endl;
	cout << "Option : ";

	cin >> option;

	system("CLS");

	switch (option)
	{
	case 1:
		ls.SignInCode();
		break;

	case 2:
		ls.SignUpCode();
		break;

	case 3:
		exit(0);

	default:
		cout << "Wrong Entery, Try Again" << endl;
		StartingOption();
	}
}

// This part of the code displays the basic information to the user then signed in. //ww
void BankSystem::DisplayBank()
{
	// CheckRefund() runs to check if the user make a fail tranfer. //
	CheckRefund();
	dbs.BankIDValue(displayBankID);
	system("CLS");
	cout << "**************************************************" << endl;
	ls.PrintName();
	cout << "**************************************************" << endl;
	cout << "Bank ID Number : " << displayBankID << endl;
	cout << "Balance : " << balance << endl;
	cout << "Please pick one of the options available" << endl;
	cout << "1 : Withdrawal. \n2 : Deposit.\n3 : Statement.\n4 : Send Money\n5 : Sign Out\n" << endl;
	cout << "Option : ";
}

// This function allows the user to make withdraw from their account. //
void BankSystem::Withdraw()
{
	MainBank mb;
	cout << "**************************************************" << endl;
	cout << "                     WithDraw                     " << endl;
	cout << "**************************************************" << endl;
	cout << "Enter withdraw amount : ";

	// Makes sure the user enters digits as the amount. //
	while (!(cin >> amount))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input" << endl;
		cout << "Enter withdraw amount : ";
	}
	// If the user withdraws money that doesn't exceed their current balance. //
	if (balance >= amount && amount > 0)
	{
		// Withdraw amount will be subtracted from the current balance. //
		balance -= amount;
		cout << "Withdraw Successful" << endl;
		
		// The new balance will then be updated into the database using the [case 4]. //
		dbs.DatabaseOption(4);
		cout << "New Balance : " << balance << endl;
		
		// Withdraw details recorded into the statement.
		fs.Statement(1);
	}
	// If the user withdraws money that exceeds their current balance, an error will appear and the withdraw will be cancelled.
	else
	{
		cout << "Withdraw Denied" << endl;
		cout << "Not Enought Money" << endl;
		cout << "Balance : " << balance << endl;
	}

	// After the withdrawal is complete, the user returns to the MainMenu. //
	Sleep(3000);
	system("CLS");
	mb.MainMenu();
}

// This is the basic function where the user can deposit money to their account. //
void BankSystem::Deposit()
{
	MainBank mb;
	cout << "**************************************************" << endl;
	cout << "                      Deposit                     " << endl;
	cout << "**************************************************" << endl;
	cout << "Enter Deposit Amount : ";

	// Makes sure the user enters digits as the amount. //
	while (!(cin >> amount))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input" << endl;
		cout << "Enter Deposit Amount : ";
	}
	
	// Deposit amount added into to the current balance. //
	balance += amount;

	// New balance updated into the database using [case 4]. //
	cout << "Doposit Successfully" << endl;
	dbs.DatabaseOption(4);
	cout << "New Balance : " << balance << endl;

	// Deposit details recorded into the statement. //
	fs.Statement(2);

	// After the deposit is complete, the user returns to the MainMenu. //
	Sleep(3000);
	system("CLS");
	mb.MainMenu();
}

// Allows the user to transfer money from one account to another.
void BankSystem::Transfer()
{
	MainBank mb;
	cout << "**************************************************" << endl;
	cout << "                     Transfer                     " << endl;
	cout << "**************************************************" << endl;

	// Requests the transfer BankID and the transfer amount. //
	cout << "Enter Bank ID : ";
	cin >> transferBankID;

	cout << "Enter Amount : ";
	cin >> transferCash;

	// If the transfer amount isn't greater then the current balance. //
	if (balance >= transferCash && amount >= 0)
	{
		// Subtract transfer amount from the current balance. //
		balance -= transferCash;

		// Update the current balance into the database. //
		dbs.DatabaseOption(4);

		// Transfer details recorded into the statement. //
		fs.Statement(3);

		// Detail passed to [case 6] in the databaseSystem. //
		dbs.DatabaseOption(6);
	}
	else
	{ 
		// If the transfer amount exceeds the current balance, an error will display and the user will return to the MainMenu. //
		cout << "Transfor Failed...\nNot Enought Money";
		Sleep(3000);
		mb.MainMenu();
	}
}

// This function can only be accessed by entered the admin details when signing in. //
// first name : "Admin", last name : "Mode", Pincode : "007007". //
void BankSystem::AdminMode()
{
	int adminOption;
	cout << "***************************************************" << endl;
	cout << "                Administrator Mode                 " << endl;
	cout << "***************************************************" << endl;

	cout << "Please pick one of the options available" << endl;
	cout << "1 : View Database.\n2 : Search Database.\n3 : Search Statement.\n4 : Delete Acoount\n5 : Sign Out" << endl;

	cout << "\nOption : ";
	cin >> adminOption;

	switch (adminOption)
	{
		// This case allows the admin to view all the user data in the database. //
		case 1:
			system("CLS");
			dbs.DatabaseOption(2);
			system("CLS");
			AdminMode();
			break;

		// This case allows the admin to search for a user in the database. //
		case 2:
			system("CLS");
			dbs.DatabaseOption(3);
			system("CLS");
			AdminMode();
			break;

		// This case allows the admin to search for a user statement. //
		case 3:
			system("CLS");
			fs.SearchStatement();
			system("pause");
			system("CLS");
			AdminMode();
			break;
		// This case allows the admin to delete a user from the database, this is the only way to delete a user from the bank. // 
		case 4:
			system("CLS");
			dbs.DatabaseOption(7);
			system("pause");
			system("CLS");
			break;

		// This case allows the Admin to go bank first display. //
		case 5:
			system("CLS");
			StartingOption();
			break;
		
		// Any other entery. //
		default:
			system("CLS");
			cout << "Wrong Entery, Try Again" << endl;
			Sleep(3000);
			system("CLS");
			AdminMode();
	}
}

// After the user enters the first/last name and Pincode this function runs. //
void BankSystem::RegisterBalance()
{
	DatabaseSystem dbs;
	BankSystem bs;
	MainBank mb;

	cout << "*************************************************************" << endl;
	cout << "Deposit needs to be between 5 and 1000 to create new account." << endl;
	cout << "Enter 0 to go back to Main Menu" << endl;
	cout << "*************************************************************" << endl;
	cout << "Enter Deposit Amount : ";

	// Makes sure the user enters digits as the balance. //
	while (!(cin >> balance))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		RegisterBalance();
	}

	// If the user doesn't want to deposit, they will return to the starting screen. //
	if (balance == 0)
	{
		system("CLS");
		bs.StartingOption();
	}

	// User has to deposit a minimum of 5 euro and a maximum of 1000 euro. //
	else if (balance >= 5 && balance <= 1000)
	{
		// Once the deposit is entered, the account will be created in the database and the user will be sent to the MainMenu. //
		dbs.DatabaseOption(1);
		cout << "Account Created Successful ..." << endl;
		Sleep(3000);
		system("CLS");
		mb.MainMenu();
	}
	else
	{
		// If the user doesn't deposit the right amount, an error will be displayed and the user can try again. //
		cout << "Error, not within the limits, try again" << endl;
		Sleep(3000);
		system("CLS");
		RegisterBalance();
	}
}

// This function is called when the user enters the MainMenu. //
// If the user enters a bankID that doesn't exist, this function returns the transfer amount. //
void BankSystem::CheckRefund()
{
	DatabaseSystem dbs;
	int checkExist;
	
	// If checkExist equals '2', the money will be refunded. //
	if (dbs.Refund(checkExist) == 2)
	{
		balance += transferCash;
	}
}

// Passing Variables // Returning Variables //

void BankSystem::BalanceValue(int& bal)
{
	balance = bal;
}

void BankSystem::PrintBalanceValue(int& pBal)
{
	pBal = balance;
}

void BankSystem::TBankIDValue(int& tID)
{
	tID = transferBankID;
}

void BankSystem::TBalanceValue(int& tBal)
{
	tBal = transferCash;
}

void BankSystem::AmountValue(int& av)
{
	av = amount;
}

int BankSystem::PassBalance(int passBal)
{
	return balance;
}

void BankSystem::BankIDValue(int& id)
{
	id = displayBankID;
}
