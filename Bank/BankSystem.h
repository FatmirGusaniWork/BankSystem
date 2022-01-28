//Name : Fatmir Gusani
//Date : 20.06.2021

#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

class BankSystem {
public:
	void StartingOption();
	void DisplayBank();
	void Withdraw();
	void Deposit();
	void Transfer();
	void AdminMode();

	// Pass Value //
	void BalanceValue(int& bal);
	void TBankIDValue(int& tID);
	void TBalanceValue(int& tBal);
	int PassBalance(int passBal);
	void AmountValue(int& av);
	void BankIDValue(int& id);
	void PrintBalanceValue(int& pBal);
	void CheckRefund();
	void RegisterBalance();
};

#endif



