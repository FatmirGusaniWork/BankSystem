//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Register.h"


void Register::MainMenu()
{
	Register r;
	int option;
	int balance = 5;

	r.PrintName();

	cout << "Please pick one of the options available" << endl;
	cout << "1 : Withdrawal. \n2 : Deposit.\n3 : Statement\n4 : Sign Out" << endl;
	cin >> option;

	switch (option)
	{
	case 1:
		//bank withdrawal
		break;
	case 2:
		//bank deposit
		break;
	case 3:
		//bank statement 
	case 4:
		r.PickOption();
		break;
	default:
		cout << "Wrong Entery, Try Again" << endl;
		MainMenu();
	}
}