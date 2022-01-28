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

// The code below is the main fuction of the databae. //
// The cases act as functoin calls with each case per of the code performing a task the user requested.
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
            // INSERT is a key word that takes the data and enters it into the database.
            ss << "INSERT INTO bankuser.details (id, firstname, lastname, bankpin, money) values ('" << bankID << "','" << ls.PassFirstName(fName) << "','" << ls.PassLastName(lName) << " ','" << ls.PassBankPin(bPin) << " ','" << bs.PassBalance(bMoney) << "')";

            tempBankID = bankID;

            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            if (qstate == 0)
            {
                cout << "Record inserted successfully ..." << endl;
            }
            else
            {
                cout << "Error, data not inserted..." << endl;
            }
        }
        else
        {
            cout << " Connection failure" << endl;
        }
        break;

    case 2:
        /////////////// VIEW ///////////////
        // This case can only be accessed with Admin Mode. //
        // It allows the Admin to view all the user data in the Bank database. //
        // The code will also specify the type of data. // 
        if (conn)
        {
            qstate = mysql_query(conn, "SELECT * FROM bankuser.details");

            if (!qstate)
            {
                res = mysql_store_result(conn);

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

            cout << "Search First Name : ";
            cin >> searchName;

            stringstream ss;
            ss << "SELECT * FROM bankuser.details WHERE firstname = '" << searchName << "'";

            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                res = mysql_store_result(conn);

                while (row = mysql_fetch_row(res))
                {
                    cout << endl;
                    cout << "ID : " << row[0] << endl;
                    cout << "First name: " << row[1] << endl;
                    cout << "Last name: " << row[2] << endl;
                    cout << "Bank Pin: " << row[3] << endl;
                    cout << "Money " << row[4] << endl;
                }
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
        // This case is called when the user withdraw(), depost(), transfers() money from their account.
        if (conn)
        {
            stringstream ss;

            // UPDATE is a key word that updates a specify data to a specify bankID. //
            // In this part of the code, its updating money to a specify user. //
            ss << "UPDATE bankuser.details SET money = " << bs.PassBalance(bMoney) << " WHERE id = " << tempBankID;

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

            stringstream ss;
            ss << "SELECT * FROM bankuser.details";

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

                    /// Convert first name char to string //
                    stringstream s1;
                    s1 << firstNameV;
                    s1 >> fnRowV;

                    // Convert last name char to string //
                    stringstream s2;
                    s2 << lastNameV;
                    s2 >> lnRowV;

                    // converts char to int
                    bankID = atoi(idV);
                    tempBankID = bankID;

                    // converts char to int
                    bPinRowV = atoi(bankPinV);
                    bMoney = atoi(moneyV);

                    bs.BalanceValue(bMoney);

                    // If a row natchs the data entered by the user, it allows the user to sign in and head to the main menu.
                    if (fnRowV == ls.PassCheckFirstName(checkFName) && lnRowV == ls.PassCheckLastName(checkLName) && bPinRowV == ls.PassCheckBankPin(checkBPin))
                    {
                        mb.MainMenu();
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
        // This case allow the user to transfer money from one account to another. //
        // To perform a transfer, BankId and the amount of money is reqired. //
        if (conn)
        {
            // Pass Transfer BankID, Pass Transfer Cash //
            int PTbankID;
            int PTcash;

            char* idV;
            char* moneyV;

            bs.BankIDValue(tempBankID);

            stringstream ss;
            ss << "SELECT * FROM bankuser.details";

            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                res = mysql_store_result(conn);

                while (row = mysql_fetch_row(res))
                {
                    idV = row[0];
                    moneyV = row[4];

                    bankID = atoi(idV);

                    int tempmoney;
                    tempmoney = atoi(moneyV);

                    // Gets the transfered BankID
                    bs.TBankIDValue(PTbankID);

                    // if the transfer bankid matchs a bankid in the databse. //
                    if (PTbankID == bankID)
                    {
                        // Gets transfer amount and adds its the transferID balance. //
                        bs.TBalanceValue(PTcash);
                        tempmoney += PTcash;

                        // Updates the new balance of the transfers account.//
                        stringstream ss;
                        ss << "UPDATE bankuser.details SET money = '" << tempmoney << "' WHERE id = '" << PTbankID << "'";

                        string query = ss.str();
                        const char* q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (!qstate)
                        {
                            res = mysql_store_result(conn);
                        }

                        cout << "Transfer Completed...\nReturning to Main Menu...";
                        Sleep(3000);

                        bankID = tempBankID;
                        TBankIDExist = 1;
                        mb.MainMenu();
                    }
                }
                // If the transfer bankID doesn't match with the databse. returns to the main menu. //
                cout << "Error, Transfer Failed...\nBank ID Entered Doesn't Exist...\nReturning to Main Menu...";
                Sleep(2000);

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
        if (conn)
        {
            char* idV;
            char* firstNameV;
            char* lastNameV;
            char* PinV;
            char* moneyV;

            string firstNameRow;
            string lastNameRow;

            int deleteBankID;
            string deleteFirstName;
            string deleteLastName;
            int deletePinCode;
            int deleteMoney;

            //b.ReturnBankID(tempBankID);
            stringstream ss;
            ss << "SELECT * FROM bankuser.details";

            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);

            cout << "***************************************************" << endl;
            cout << "                  Delete Account                   " << endl;
            cout << "***************************************************" << endl;

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

                    // Convert first name char to string //
                    stringstream s1;
                    s1 << firstNameV;
                    s1 >> firstNameRow;

                    // Convert last name char to string //
                    stringstream s2;
                    s2 << lastNameV;
                    s2 >> lastNameRow;
                    
                    // Convert chat to int //
                    bankID = atoi(idV);
                    bPin = atoi(PinV);
                    bMoney = atoi(moneyV);

                    if (deleteBankID == bankID && deleteFirstName == firstNameRow && deleteLastName == lastNameRow && deletePinCode == bPin && deleteMoney == bMoney)
                    {
                        stringstream ss;
                        ss << "DELETE FROM bankuser.details WHERE id = '" << deleteBankID << "'";

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

int DatabaseSystem::PassBankID(int ID)
{
    return bankID;
}

void DatabaseSystem::BankIDValue(int& IDv)
{
    IDv = tempBankID;
}

int DatabaseSystem::Refund(int exist)
{
    return TBankIDExist;
}