//Name : Fatmir Gusani
//Date :29.07.2021

#ifndef USERDB_H
#define USERDB_H

class UserDB {
public:
	void DatabaseOption(int option);
	int PassBankID(int ID);
	int PassMoney(int mon);
	void PassABankID(int& ID);
};

#endif
