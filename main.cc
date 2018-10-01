/* 
 *		Venmo type payment application program
 *		Way to run the program:
 *		Compiling:
 *			./compile.sh
 *		Running:
 *			./venmo --user usera:50 --user userb:60
 * */
//System headers on the top
#include <thread>
#include <iostream>
#include <unistd.h>
#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string>
#include <memory>
#include <queue>
#include <string.h>
#include <istream>
#include <sstream>      // std::istringstream
#include <iterator>
#include <map>

//Project specific headers down below 
#include "User.h"
#include "tasks.h"
#include "paymentApp.h"

//These are the globals ( probably can be stored in the database somewhere as well )
extern std::queue<std::unique_ptr<GenericTask>>		gTasks;
extern std::mutex			                        gMutex;
extern std::map<unsigned long, User *> 	            gUsers;
//Hope no compilation error

/* 
	Parses the input parameter to get the list of users
*/
void ParseUserInput(char *input)
{
	std::string inputString (input);
	std::string username = inputString.substr(0, inputString.find(":"));
	std::string balance = inputString.substr(inputString.find(":") + 1, inputString.size());
	unsigned long randomId = random();
	gUsers.emplace(std::make_pair(randomId , new User(randomId, username, atoi(balance.c_str()))));
}

/* 
	Accept the input from the user and converts it onto the tasks
*/
void AcceptInput()
{
    // List of tasks ?
    gTasks.push(std::unique_ptr<Task<CheckBalance>>{new Task<CheckBalance>{"user1"}});
    gTasks.push(std::unique_ptr<Task<DoPayment>>{new Task<DoPayment>{"user1","user2",50}});
}

int main ( int argc, char *argv[] )
{
    //TODO: Implement the whole application
}
