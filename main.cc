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

//These are the globals ( probably can be stored in the database somewhere as well )
extern std::queue<Task*>		gTasks;
extern std::mutex			gMutex;
extern std::map<unsigned long, User *> 	gUsers;
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
Task* AcceptInput()
{
	std::string command;
	//Get the request type from the user
	//We should treat this as some type of class itself
	std::cout<<"[GetBalance, MakePayment, Quit]"<<std::endl;
	std::cout<<">";
	getline(std::cin,command);

	std::istringstream commandStr{command};
	std::vector<std::string> results(std::istream_iterator<std::string>{commandStr},
			std::istream_iterator<std::string>());

	Task *task ;
	if ( results.size() ) {
		std::string request = results[0];
		if ( request == "GetBalance" ) 
			task = new GetBalance(results[1]);
		else {
			if ( request == "MakePayment" ) {
				task = new MakePayment(results[1], results[2], atoi(results[3].c_str()));
			}
			else {
				if ( request == "Quit" ) 
					task = nullptr;
				else
					throw EINVAL;
			}
		}
	} else 
		throw ENOTSUP;

	return task;
}

int main ( int argc, char *argv[] )
{
    //Parse the input that is sent on the command line
    static const struct option options[] = {
        { "user", required_argument, NULL, 'u' }
    };

	for (
			int option;
			(option = getopt_long(argc, const_cast<char* const*>(argv), "u:", options, NULL)) != -1;
		) {
		switch (option) {
			case 'u':
				ParseUserInput(optarg);
				break;
			default:
				throw "Invalid usage";
		}
	}
    argc -= optind, argv += optind;

	if ( gUsers.empty() ) {
		std::cout<<"No Users initialized.. Exiting"<<std::endl;
		exit(0);
	}
   
	//Tasks worker pulls the tasks from the queue and does the tasks
	//There can be multiple worker threads, working on the queue of performing the task
    std::thread taskWorker{ PerformTasks };  

	//Wait for the user input and puts it in the tasks queue
	while ( 1 ) {
		try {
			//Accept the user command on the command-line
			Task *task = AcceptInput();
			
			if ( !task ) break;

			//scope
			{
				//lock the queue before puting the task in the queue
				std::unique_lock<std::mutex> lck{gMutex};
				gTasks.push(task);			//Pushing the task to the back of queue
			}
		} catch ( ... )  { //TODO : more error checking
			std::cout<<"Invalid task."<<std::endl;
		}
	}

	taskWorker.join();	
}
