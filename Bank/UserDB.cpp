///////////////////////////////////////////
//Need to make this code all in one function//
///////////////////////////////////////////

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <Windows.h>
#include <mysql.h>
#include <iomanip>
#include <stdio.h>
#include "UserDB.h"
#include "Function.h"
#include "Bank.h"


string checkfname;
string checklname;
int checkbpin;

string fname;
string lname;
int bpin;

int money;
int tempMoney;
int bankID;
int testBankID;
int tempBankID;

string rowValue1;
string rowValue2;

void UserDB::DatabaseOption(int option)
{
    Function f;
    Bank b;

    srand((unsigned)time(0));

    //int bankID = rand() % 9000 + 100000;


    for (int index = 0; index < 1; index++) {
        bankID = 100000 + (rand() % 10000000) + 1;
        //cout << "Bank ID : " << bankID << endl;
    }


    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    int qstate;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "Fatmir16", "bankuser", 0, NULL, 0);

    switch (option)
    {

    case 1:
        /////////////// INSERT ///////////////
        if (conn)
        {
            stringstream ss;

            ss << "INSERT INTO bankuser.details (id, firstname, lastname, bankpin, money) values ('" << bankID << "','" << f.PassValueOption(fname, 1) << "','" << f.PassValueOption(lname, 2) << " ','" << f.PassBankPin(bpin) << " ','" << b.PassBalance(money) << "')";

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
            }
        }

        else
        {
            cout << " Connection failure" << endl;
        }

        break;

    case 3:
        /////////////// SEARCH ///////////////
        if (conn)
        {
            string searchName;

            cout << "Enter Search Name : ";
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
            }
        }

        else
        {
            cout << " Connection failure" << endl;
        }

        break;

    case 4:
        /////////////// UPDATE ///////////////
        if (conn)
        {
            stringstream ss;
            ss << "UPDATE bankuser.details SET money = " << b.PassBalance(money) << " WHERE id = " << testBankID;

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
        if (conn)
        {
            char* val0;
            char* val1;
            char* val2;
            char* val3;
            char* val4;
            stringstream ss;
            ss << "SELECT * FROM bankuser.details";
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
            //qstate = mysql_query(conn, "SELECT * FROM bankuser.details");

            if (!qstate)
            {
                res = mysql_store_result(conn);

                while (row = mysql_fetch_row(res))
                {
                    val0 = row[0];
                    val1 = row[1];
                    val2 = row[2];
                    val3 = row[3];
                    val4 = row[4];

                    stringstream s1;
                    s1 << val1;
                    s1 >> rowValue1;

                    stringstream s2;
                    s2 << val2;
                    s2 >> rowValue2;

                    bankID = atoi(val0);
                    testBankID = bankID;

                    //test = bankID;
                    int rowValue3 = atoi(val3);
                    money = atoi(val4);
                    //testMoney = money;
                    b.PassBalanceDetails(money);

                    if (rowValue1 == f.PassValueOption(checkfname, 3) && rowValue2 == f.PassValueOption(checklname, 4) && f.PassCheckBankPin(checkbpin) == rowValue3)
                    {
                        b.MainMenu();
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
        if (conn)
        {
            int PTbankID;
            int PTcash;

            char* val0;
            char* val4;

            b.ReturnBankID(tempBankID);
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
                    val0 = row[0];
                    val4 = row[4];

                    bankID = atoi(val0);

                    int tempmoney;
                    tempmoney = atoi(val4);

                    if (b.PassTBankID(PTbankID) == bankID)
                    {
                        b.PassTCash(PTcash);
                        tempmoney += PTcash;

                        stringstream ss;
                        ss << "UPDATE bankuser.details SET money = '" << tempmoney << "' WHERE id = '" << b.PassTBankID(PTbankID) << "'";

                        string query = ss.str();
                        const char* q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (!qstate)
                        {
                            res = mysql_store_result(conn);
                        }

                        bankID = tempBankID;

                        b.MainMenu();
                    }  
                }
            }
        }

        else
        {
            cout << " Connection failure" << endl;
        }

        break;
    }
}

int UserDB::PassBankID(int ID)
{
    return bankID;
}

void UserDB::PassABankID(int &ID)
{
    ID = bankID;
}

int UserDB::PassMoney(int mon)
{
    return money;
}