//Name : Fatmir Gusani
//Date : 20.06.2021

using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Register.h"


class Bank {

private:
	Register r;

public:
	void PickOption()
	{
		int option;
		cout << "Wellcome, please pick one of the options available" << endl;
		cout << "1 : Sign In. \n2 : Sign Up." << endl;
		cin >> option;

		switch (option)
		{
		case 1:
			r.SignInCode();
			break;
		case 2:
			r.SignUpCode();
			break;
		default:
			cout << "Wrong Entery, Try Again" << endl;
			PickOption();
		}
	}
	
};