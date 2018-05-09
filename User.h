#include <iostream>
#include <string>
//#include "Wallet.h"

class User {
	public:
		User(unsigned long, std::string username, unsigned balance);
		unsigned GetBalance();
		unsigned long GetUserId() { return fUserId; }
	protected:
		//Wallet fWallet; //Virtual Wallet to maintain the balance.
		unsigned long fUserId; //unique user id
		std::string fUserName;
		unsigned fBalance;
};
