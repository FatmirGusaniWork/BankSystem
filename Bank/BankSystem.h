//Name : Fatmir Gusani
//Date : 20.06.2021

#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

class BankSystem {
public:
	// Main Functions //
	void StartingOption();
	void DisplayBank();
	void Withdraw();
	void Deposit();
	void Transfer();
	void AdminMode();
	void RegisterBalance();
	void CheckRefund();

	// Pass Value // Return Value //
	void BalanceValue(int& bal);
	void PrintBalanceValue(int& pBal);
	void TBankIDValue(int& tID);
	void TBalanceValue(int& tBal);
	void AmountValue(int& av);
	int PassBalance(int passBal);
	void BankIDValue(int& id);
};

#endif



