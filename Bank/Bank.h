//Name : Fatmir Gusani
//Date :01.08.2021

#ifndef BANK_H
#define BANK_H


class Bank {
public:
	void MainMenu();
	int PassBalance(int balance);
	void EnterBalance();
	void AdminMode();
	void PassBalanceDetails(int &cash);
	int PassTBankID(int Tid);
	void PassTCash(int &Tcash);
	void Statement(int pick);
};

#endif
