//Name : Fatmir Gusani //
//Date : 20.06.2021 - 27.01.2022 //
// This file handles all the database functions. //

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <Windows.h>
#include <mysql.h>
#include <iomanip>
#include <stdio.h>

// Person Headers //
#include "BankSystem.h"
#include "MainBank.h"
#include "DatabaseSystem.h"
#include "LoginSystem.h"
#include "FileSystem.h"

// All Funtions //
int bankID;

// DatabaseOption() //
string fName;
string lName;
int bPin;
int bMoney;

// DatabaseOption(6) // 
int tempBankID;
int TBankIDExist;

// The code below is the main function of the database. //
// The cases act as function calls with each case performing a task the user requested. //
void DatabaseSystem::DatabaseOption(int option)
{
    BankSystem bs;
    LoginSystem ls;
    MainBank mb;

    // Randomly generates a 6 digit BankID. // 
    srand((unsigned)time(0));

    for (int index = 0; index < 1; index++) {
        bankID = 100000 + (rand() % 10000000) + 1;
    }

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    int qstate;

    // Details to access the MySQL database. //
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "Fatmir16", "bankuser", 0, NULL, 0);

    switch (option)
    {
    case 1:
        /////////////// INSERT ///////////////
        // This case creates and add the user datails into the database. //
        // The detail is requested from the LoginSystem file [SignUpCode()] and the BankSystem file [RegisterBalance()] //
        // The requested detail is bankID, first name, last name, pincode and money. //
        if (conn)
        {
            stringstream ss;
            // "INSERT" is a keyword that takes the data and enters it into the database. //
            // The requested information is stored in the database. //
            ss << "INSERT INTO bankuser.details (id, firstname, lastname, bankpin, money) values ('" << bankID << "','" << ls.PassFirstName(fName) << "','" << ls.PassLastName(lName) << " ','" << ls.PassBankPin(bPin) << " ','" << bs.PassBalance(bMoney) << "')";

            // TempBankID gets the current bankID. //
            tempBankID = bankID;

            // Runs SS into the mysql. //
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            // If the information is entered correlty. //
            if (qstate == 0)
            {
                cout << "Record inserted successfully ..." << endl;
            }
            else
            {
                cout << "Error, data not inserted..." << endl;
            }
        }
        // If there is an error connecting to the database. //
        else
        {
            cout << " Connection failure" << endl;
        }

        break;

    case 2:
        /////////////// VIEW ///////////////
        // This case can only be accessed with Admin Mode. //
        // It allows the Admin to view all the user's data in the database. //
        // The code will also specify the type of data. // 
        if (conn)
        {
            // "SELECT" is a keyword that select data from the database. // //
            qstate = mysql_query(conn, "SELECT * FROM bankuser.details");

            if (!qstate)
            {
                res = mysql_store_result(conn);

                // Fetches the data from the database and prints data. //
                while (row = mysql_fetch_row(res))
                {
                    cout << endl;
                    cout << "********************" << endl;
                    cout << "ID : " << row[0] << endl;
                    cout << "First name: " << row[1] << endl;
                    cout << "Last name: " << row[2] << endl;
                    cout << "Bank Pin: " << row[3] << endl;
                    cout << "Money " << row[4] << endl;
                    cout << "********************" << endl;
                }
                cout << "" << endl;
                system("pause");
            }
        }

        else
        {
            cout << " Connection failure" << endl;
        }

        break;

    case 3:
        /////////////// SEARCH ///////////////
        // This case can only be accessed with Admin Mode. //
        // Allows the admin to search for specify user in the database. //
        // The only reqirement is first name. //
        // The code will also specify the type of data. // 
        if (conn)
        {
            string searchName;

            // Admin is asked to enter a first name. //
            cout << "Search First Name : ";
            cin >> searchName;

            // Selects all the data with the first name that matches what the admin entered. //
            stringstream ss;
            ss << "SELECT * FROM bankuser.details WHERE firstname = '" << searchName << "'";

            // Runs SS into the mysql. //
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                res = mysql_store_result(conn);

                // Fetches the data from the database with the same first name as the entered one and prints data. //
                while (row = mysql_fetch_row(res))
                {
                    cout << endl;
                    cout << "ID : " << row[0] << endl;
                    cout << "First name: " << row[1] << endl;
                    cout << "Last name: " << row[2] << endl;
                    cout << "Bank Pin: " << row[3] << endl;
                    cout << "Money " << row[4] << endl;
                }
                cout << "" << endl;
                system("pause");
            }
        }
        else
        {
            cout << " Connection failure" << endl;
        }

        break;

    case 4:
        /////////////// UPDATE ///////////////
        // This case handles all the changes a user makes to their balance. //
        // This case is called when the user withdraw(), deposit(), transfers() money from their account.
        if (conn)
        {
            stringstream ss;

            // "UPDATE" is a key word that updates a specify data to a specify bankID. //
            // In this part of the code, its updating money to a specify BankID. //
            ss << "UPDATE bankuser.details SET money = " << bs.PassBalance(bMoney) << " WHERE id = " << tempBankID;

            // Runs SS into the mysql. //
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                res = mysql_store_result(conn);
            }
        }
        else
        {
            cout << " Connection failure" << endl;
        }

        break;

    case 5:
        /////////////// LOG IN ///////////////
        // This case allows the user to Sign In. //
        // It takes variables from LoginSystem file [SignInCode()] and compares it with the database. //
        // First name, last name and picode is reqired to sign in. //
        if (conn)
        {
            char* idV;
            char* firstNameV;
            char* lastNameV;
            char* bankPinV;
            char* moneyV;

            string fnRowV;
            string lnRowV;
            int bPinRowV;

            string checkFName;
            string checkLName;
            int checkBPin;

            // Selects all the data in the database. //
            stringstream ss;
            ss << "SELECT * FROM bankuser.details";

            // Runs SS into the mysql. //
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                res = mysql_store_result(conn);

                // Searchs database row by row. //
                while (row = mysql_fetch_row(res))
                {
                    idV = row[0];
                    firstNameV = row[1];
                    lastNameV = row[2];
                    bankPinV = row[3];
                    moneyV = row[4];

                    /// Convert first name char to string. //
                    stringstream s1;
                    s1 << firstNameV;
                    s1 >> fnRowV;

                    // Convert last name char to string. //
                    stringstream s2;
                    s2 << lastNameV;
                    s2 >> lnRowV;

                    // Converts bankIDchar to int. //
                    bankID = atoi(idV);
                    tempBankID = bankID;

                    // Converts bank pin char to int. //
                    bPinRowV = atoi(bankPinV);
                    bMoney = atoi(moneyV);

                    // Sends money value to Bank System. //
                    bs.BalanceValue(bMoney);

                    // If a row matches the data entered by the user, it allows the user to sign in and head to the main menu.
                    if (fnRowV == ls.PassCheckFirstName(checkFName) && lnRowV == ls.PassCheckLastName(checkLName) && bPinRowV == ls.PassCheckBankPin(checkBPin))
                    {
                        // Sign in successfully, sends user to MainMenu(). //
                        mb.MainMenu();
                    }
                    // If the user Enters "Admin" for the first name, "Mode" for last name, and "007007" for pin code. //
                    else if ("Admin" == ls.PassCheckFirstName(checkFName) && "Mode" == ls.PassCheckLastName(checkLName) && 007007 == ls.PassCheckBankPin(checkBPin))
                    {
                        // Enters Administrator Mode. //
                        system("CLS");
                        bs.AdminMode();
                    }
                }
            }
        }
        else
        {
            cout << " Connection failure" << endl;
        }
        break;

    case 6:
        /////////////// TRANSFER ///////////////
        // This case allows the user to transfer money from one account to another. //
        // To perform a transfer, BankId and the amount of money is required. //
        if (conn)
        {
            // Pass Transfer BankID, Pass Transfer Cash //
            int PTbankID;
            int PTcash;

            char* idV;
            char* moneyV;

            // Sends BankID value to Bank System. //
            bs.BankIDValue(tempBankID);

            // Runs SS into the mysql. //
            stringstream ss;
            ss << "SELECT * FROM bankuser.details";

            // Runs SS into the mysql. //
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                res = mysql_store_result(conn);

                while (row = mysql_fetch_row(res))
                {
                    // Saves the 1st row to bank Id. //
                    idV = row[0];

                    // Saves the 5th row to money. //
                    moneyV = row[4];

                    // Saves 1st row to bankID. //
                    bankID = atoi(idV);

                    int tempmoney;

                    // Saves 5th row to money. //
                    tempmoney = atoi(moneyV);

                    // Gets the transfer BankID. //
                    bs.TBankIDValue(PTbankID);

                    // if the transfer bankID matches a bankID in the database. //
                    if (PTbankID == bankID)
                    {
                        // Gets transfer amount and adds its the transferID balance. //
                        bs.TBalanceValue(PTcash);
                        tempmoney += PTcash;

                        // Updates the new balance of the transfers account. //
                        stringstream ss;
                        ss << "UPDATE bankuser.details SET money = '" << tempmoney << "' WHERE id = '" << PTbankID << "'";

                        // Runs SS into the mysql. //
                        string query = ss.str();
                        const char* q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (!qstate)
                        {
                            res = mysql_store_result(conn);
                        }

                        cout << "Transfer Completed...\nReturning to Main Menu...";
                        Sleep(3000);

                        // TBankIDExist = 2, this tells the code that the user compeleted the transfer. //
                        bankID = tempBankID;
                        TBankIDExist = 1;
                        mb.MainMenu();
                    }
                }
                // If the transfer bankID doesn't match with the databse. returns to the main menu. //
                cout << "Error, Transfer Failed...\nBank ID Entered Doesn't Exist...\nReturning to Main Menu...";
                Sleep(3000);

                // TBankIDExist = 2, this tells the code that the user failed to transfer money because BankID doesn't exist. //
                TBankIDExist = 2;
                mb.MainMenu();
            }
        }
        else
        {
            cout << " Connection failure" << endl;
        }

        break;


    case 7:
        /////////////// DELETE USER ///////////////
        // This case can only be accessed by the admin. //
        // Allows the user to delete an account from the database. //
        // Reqired information is bankID, first name, last name, pincode, current money. //
        if (conn)
        {
            char* idV;
            char* firstNameV;
            char* lastNameV;
            char* PinV;
            char* moneyV;

            string firstNameRow;
            string lastNameRow;

            // Deleted information // 
            int deleteBankID;
            string deleteFirstName;
            string deleteLastName;
            int deletePinCode;
            int deleteMoney;

            // Runs SS into the mysql. //
            stringstream ss;
            ss << "SELECT * FROM bankuser.details";

            // Runs SS into the mysql. //
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            cout << "***************************************************" << endl;
            cout << "                  Delete Account                   " << endl;
            cout << "***************************************************" << endl;

            // Asks the Admin for information. //
            cout << "Enter BankID : ";
            cin >> deleteBankID;

            cout << "Enter First Name : ";
            cin >> deleteFirstName;

            cout << "Enter Last Name : ";
            cin >> deleteLastName;

            cout << "Enter Pin Code : ";
            cin >> deletePinCode;

            cout << "Enter Current Balance : ";
            cin >> deleteMoney;

            if (!qstate)
            {
                res = mysql_store_result(conn);

                while (row = mysql_fetch_row(res))
                {
                    idV = row[0];
                    firstNameV = row[1];
                    lastNameV = row[2];
                    PinV = row[3];
                    moneyV = row[4];

                    // Convert first name char to string. //
                    stringstream s1;
                    s1 << firstNameV;
                    s1 >> firstNameRow;

                    // Convert last name char to string. //
                    stringstream s2;
                    s2 << lastNameV;
                    s2 >> lastNameRow;
                    
                    // Convert char to int. //
                    bankID = atoi(idV);
                    bPin = atoi(PinV);
                    bMoney = atoi(moneyV);

                    // If the entered informaton matches with the data in the database. //
                    if (deleteBankID == bankID && deleteFirstName == firstNameRow && deleteLastName == lastNameRow && deletePinCode == bPin && deleteMoney == bMoney)
                    {
                        // The account will be deleted using the BankID. //
                        stringstream ss;
                        ss << "DELETE FROM bankuser.details WHERE id = '" << deleteBankID << "'";

                        // Runs SS into the mysql. //
                        string query = ss.str();
                        const char* q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (!qstate)
                        {
                            res = mysql_store_result(conn);
                        }

                        cout << "Account Deleted...\nReturning to Main Menu...";
                        Sleep(3000);
                        bs.AdminMode();
                    }
                }
                cout << "Error, Account Failed to Delete...\nReturning to Administrator Mode...";
            }
        }
        else
        {
            cout << " Connection failure" << endl;
        }
        break;
    }
}

// Passing Variables //

int DatabaseSystem::Refund(int exist)
{
    return TBankIDExist;
}

int DatabaseSystem::PassBankID(int ID)
{
    return bankID;
}

void DatabaseSystem::BankIDValue(int& IDv)
{
    IDv = tempBankID;
}
