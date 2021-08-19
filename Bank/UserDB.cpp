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

string fname;
string lname;
int money;
int bankID;


void UserDB::DatabaseOption(int option)
{
    Function f;
    Bank b;

    srand((unsigned)time(0));

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

            ss << "INSERT INTO bankuser.details (id, firstname, lastname, money) values ('" << bankID << "','" << f.PassFirstName(fname) << "','" << f.PassLastName(lname) << " ','" << b.PassBalance(money) << "')";

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
                    cout << "Money " << row[3] << endl;
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

            ss << "SELECT * FROM bankuser.details WHERE firstname = '" + searchName + "' ";

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
                    cout << "Money " << row[3] << endl;
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
            b.PassBalance(money);
           // qstate = mysql_query(conn, "UPDATE bankuser.details SET money = money + 1  WHERE id = 42");
           // qstate = mysql_query(conn,"UPDATE bankuser.details SET money = money + @money WHERE id = @bankID");
            //ss << "UPDATE bankuser.details SET money = money + @money";
            stringstream ss;

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
        /////////////// READ ///////////////
        
        if (conn)
        {
            string test[7] = {};
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
                    cout << "Money " << row[3] << endl;
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
