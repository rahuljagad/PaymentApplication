/*  
 *  Tasks : Defines all types of tasks associated to payment application
 *
*/

#include "tasks.h"
#include <unistd.h>

std::queue<Task*> gTasks;
std::map<unsigned long, User *> gUsers;
std::mutex gMutex;

//		PerformTasks()
//Runs as a seperate threads, pulling out tasks out of the queue and
//calling the doTasks, which does the actual work of performing the operation
//
void PerformTasks()
{
	while ( 1 ) {
		try {
			std::unique_lock<std::mutex> lck{gMutex};
			if ( gTasks.size() ) {
				Task *task = gTasks.front();
				task->doTask();
				gTasks.pop();
			}
		} catch ( ... ) {
			std::cout<<"Invalid tasks .. "<<std::endl;
		}
		usleep(50); //randomly waiting for few microseconds
	}
}


/* 
 *		Task::GetBalance
*/

/* 
 *		Constructor
*/
GetBalance::GetBalance(std::string username):
        Task(TaskStatus::QUEUED)
{
	bool found = false;
	for ( auto item : gUsers ) {
		if ( item.second->Username() == username ) {
			fUserId = item.first;
			found = true;
			break;
		}
	}
	if ( !found ) EINVAL;
}

/* 
 *		GetBalance::doTask
 * Performs the task of looking up the balance of the user.
*/
void GetBalance::doTask()
{
	std::cout<<std::endl<<gUsers[fUserId]->Username()<<" Balance "<<gUsers[fUserId]->GetBalance()<<std::endl;;
}
