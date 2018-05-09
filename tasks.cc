#include "tasks.h"
#include <unistd.h>

std::queue<Task*> gTasks;
std::map<unsigned long, User *> gUsers;
std::mutex gMutex;

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

void GetBalance::doTask()
{
	std::cout<<std::endl<<gUsers[fUserId]->Username()<<" Balance "<<gUsers[fUserId]->GetBalance()<<std::endl;;
}
