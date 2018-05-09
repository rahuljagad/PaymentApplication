#pragma once
#include <iostream>
#include <string>
//#include "Wallet.h"

class User {
	public:
		User(unsigned long, std::string username, unsigned balance);
		unsigned GetBalance();
		unsigned long GetUserId() { return fUserId; }
		std::string Username() { return fUserName; }
	protected:
		//Wallet fWallet; //Virtual Wallet to maintain the balance.
		unsigned long fUserId; //unique user id
		std::string fUserName;
		unsigned fBalance;
};
