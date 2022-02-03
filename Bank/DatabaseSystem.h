//Name : Fatmir Gusani //
//Date : 20.06.2021 - 27.01.2022 //

#ifndef DATABASESYSTEM_H
#define DATABASESYSTEM_H

class DatabaseSystem {
public:
	// Main Function //
	void DatabaseOption(int option);

	// Return Value // Pass Value //
	int Refund(int exist);
	int PassBankID(int ID);
	void BankIDValue(int& IDv);
};

#endif
