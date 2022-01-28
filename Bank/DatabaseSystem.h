//Name : Fatmir Gusani //
//Date : 20.06.2021 - 27.01.2022 //

#ifndef DATABASESYSTEM_H
#define DATABASESYSTEM_H

class DatabaseSystem {
public:
	void DatabaseOption(int option);
	int PassBankID(int ID);
	void BankIDValue(int& IDv);
	//int PassMoney(int pMoney);
	int Refund(int exist);
};

#endif
