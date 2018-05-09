#include "tasks.h"

std::queue<Task*> gTasks;
std::mutex gMutex;

void PerformTasks()
{
	while ( 1 ) {
		try {
			std::unique_lock<std::mutex> lck{gMutex};
			if ( gTasks.size() ) {
				Task *task = gTasks.front();
				task->doTask();
			}
		} catch ( ... ) {
			std::cout<<"Invalid tasks .. "<<std::endl;
		}
	}
}

GetBalance::GetBalance():
        Task(TaskStatus::QUEUED)
{ 
}

bool GetBalance::doTask()
{
	//TODO:
}
