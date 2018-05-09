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
