#include "User.h"

User::User(unsigned long randomId, std::string username, unsigned balance):
	fUserId(randomId),
	fUserName(username),
	fBalance(balance)
{
}

unsigned User::GetBalance()
{
	return fBalance;
}

void User::Credit(unsigned balance)
{
	if ( balance > fBalance ) throw ;
	fBalance -= balance;
}

void User::Debit(unsigned balance)
{
	fBalance += balance;
}
