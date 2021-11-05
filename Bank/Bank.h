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
	void TransferMoney();

	void PassTransforBalance(int &Tbal);
	void PassTransforBankID(int &TbankID);
};

#endif
