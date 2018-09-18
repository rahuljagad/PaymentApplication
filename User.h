#pragma once
#include <iostream>
#include <string>

class User {
	public:
		//Constructor (no default constructor)
		User(unsigned long, std::string username, unsigned balance);
		unsigned GetBalance();
		unsigned long GetUserId() { return fUserId; }
		std::string Username() { return fUserName; }
		void Credit(unsigned balance);
		void Debit (unsigned balance);
	protected:
		//Wallet fWallet; //Virtual Wallet to maintain the balance.
		unsigned long fUserId; //unique user id
		std::string fUserName;
		unsigned fBalance;
};
