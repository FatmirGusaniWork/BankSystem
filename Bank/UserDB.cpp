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
int checkbankpin;

string fname;
string lname;
int bpin;
int money;
int bankID;
string getID;
char* val;
char* val2;




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

            ss << "INSERT INTO bankuser.details (id, firstname, lastname, bankpin, money) values ('" << bankID << "','" << f.PassFirstName(fname) << "','" << f.PassLastName(lname) << " ','" << f.PassBankPin(bpin) << " ','" << b.PassBalance(money) << "')";

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

    case 3:
        /////////////// SEARCH ///////////////
        if (conn)
        {

            string searchName;
            cout << "Enter Search Name : ";
            cin >> searchName;

            stringstream ss;

            ss << "SELECT * FROM bankuser.details WHERE firstname = " << searchName;

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
            ///bankID not linked//
            stringstream ss;
            int ch;
            cin >> ch;
            cout << "TESTING : " << bankID << endl;
            ss << "UPDATE bankuser.details SET money = " << b.PassBalance(money) << " WHERE id = " << ch;

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

        if (conn)
        {
            qstate = mysql_query(conn, "SELECT * FROM bankuser.details");

            if (!qstate)
            {
                res = mysql_store_result(conn);

                while (row = mysql_fetch_row(res))
                {

                     val = row[1];
                     val2 = row[2];


                    
                    f.PassCheckFN(checkfname);
                    f.PassCheckLN(checklname);



                    cout << "check first name : " << f.PassCheckFN(checkfname) << endl;
                    cout << "check first name : " << f.PassCheckLN(checklname) << endl;

                    cout << endl;
                    cout << "First name: " << row[1] << endl;
                    cout << "Last name: " << row[2] << endl;


                    cout << "Char : " << val << endl;

                    if (checkfname == val && checklname == val2)
                        cout << "MATCH FN AND LN " << endl;
                    else
                        cout << "FN AND LN FAILED" << endl;

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

char* UserDB::PassVal1(string passVal1)
{
    return val;
}


char* UserDB::PassVal2(string passVal2)
{
    return val2;
}
