//Name : Fatmir Gusani
//Date : 20.06.2021

#ifndef REGISTER_H
#define REGISTER_H


class Register {
public:
	void SignInCode();
	void SignUpCode();
	void PickOption();
	void MainMenu();
	void PrintName();
	int EnterPin(string test, int whichfunction);
	void PassFullname(string fullName, string lastName);
	void PassBalance(int money);

};

#endif
