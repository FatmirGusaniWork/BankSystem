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

int bankID;
string fname;
string lname;
int money;


string UserDB::TestName(string firstname)
{
    firstname = fname;
    return fname;
}

void UserDB::InsertDatabase()
{
    Function f;
    Bank b;

    srand((unsigned)time(0));    
    for (int index = 0; index < 1; index++) {
        bankID = 100000  + (rand() % 10000000) + 1;
        cout << "Bank ID : " <<  bankID << endl;
    }

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    int qstate;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "Fatmir16", "bankuser", 0, NULL, 0);

    if (conn)
    {
       
        stringstream ss;

        ss << " INSERT INTO bankuser.details (id, firstname, lastname, money) values ('" << bankID << "','" << f.PassFirstName(fname) << "','" << f.PassLastName(lname) << " ','" << b.PassBalance(money) << "')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        if (qstate == 0)
        {

            cout << " Record inserted successfully ..." << endl;
        }
        else
        {
            cout << " Error, data not inserted..." << endl;
        }
    }

    else
    {
        cout << " Connection failure" << endl;
    }
}


void UserDB::ViewDatabase()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    int qstate;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "Fatmir16", "bankuser", 0, NULL, 0);

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

}