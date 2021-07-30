using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <Windows.h>
#include <mysql.h>
#include <iomanip>
#include <stdio.h>
#include "SQLDB.h"
#include "Register.h"

int bankID;
string fname;
string lname;

int testbalance;
string lastname;
string firstname;


void SQLDB::InsertDatabase()
{
    Register r;

	for (int bankID = 1; bankID < 7; bankID++) {
		bankID = bankID * 10 + rand() % 10;      //Generate the next 6 digits.
	}

    /*
    cout << bankID << endl;

    r.PassFullname(fname, lname);
    r.PassBalance(testbalance);

    cout << fname << endl;
    cout << lname << endl;
    cout << testbalance << endl;
   
    fname = firstname;
    lastname = lname;
    */


    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    int qstate;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "******", "bankid", 0, NULL, 0);

    if (conn)
    {
       
        stringstream ss;

        ss << " INSERT INTO bankuser.details (id, firstname, lastname, money) values ('" << bankID << "','" << firstname << "','" << lastname << " ','" << testbalance << "')";

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



void SQLDB::ViewDatabase()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    int qstate;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "*******", "bankid", 0, NULL, 0);

    if (conn)
    {
        qstate = mysql_query(conn, "SELECT * FROM bankuser.details");

        if (!qstate)
        {
            res = mysql_store_result(conn);

            while (row = mysql_fetch_row(res))
            {
                cout << " ID : " << row[0] << endl;
                cout << " First name: " << row[1] << endl;
                cout << " Last name: " << row[2] << endl;
                cout << " Money " << row[3] << endl;
            }
        }
    }

    else
    {
        cout << " Connection failure" << endl;
    }

}