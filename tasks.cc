/*  
 *  Tasks : Defines all types of tasks associated to payment application
  		This is added through the branch Fix-1
 *
*/

#include "tasks.h"
#include <unistd.h>

std::queue<<#class _Tp#>>
std::map<unsigned long, User *> gUsers;
std::mutex gMutex;

//		PerformTasks()
//Runs as a seperate threads, pulling out tasks out of the queue and
//calling the doTasks, which does the actual work of performing the operation
//
void PerformTasks()
{
	  //Break when all the tasks are done.
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

	if ( !found ) throw EINVAL;
}

/* 
 *		GetBalance::doTask
 * Performs the task of looking up the balance of the user.
*/
void GetBalance::doTask()
{
	std::cout<<std::endl<<gUsers[fUserId]->Username()<<" Balance "<<gUsers[fUserId]->GetBalance()<<std::endl;;
}

/* 
 *		Task::MakePayment
*/

/* 
 *		Constructor
*/
MakePayment::MakePayment(std::string userFrom, std::string userTo, unsigned balance):
		Task(TaskStatus::QUEUED),
		fBalance(balance)
{
	bool foundF = false;
	bool foundT = false;
	for ( auto item : gUsers ) {
		std::string userName = item.second->Username();
		if ( userName == userFrom || userName == userTo ) {
			if ( userName == userFrom ) { 
				fUserFrom = item.first;
				foundF = true;
			}
			else {
				fUserTo = item.first;
				foundT = true;
			}
		}
	}

	if ( !foundF || !foundT ) throw EINVAL;
}


void MakePayment::doTask()
{
	//TODO : way to acquire locks on users( locks sorted in some order so as to avoid deadlock )
	//		so that we can achieve accuracy for transactions
	gUsers[fUserFrom]->Credit(fBalance); //throws exception if not enough balance
	gUsers[fUserTo]->Debit(fBalance);
}

/*
        ** GenericTask **
 */
// Constructor
template<typename TaskType>
GenericTask<TaskType>::GenericTask(TaskType &task):
    fTask(task)
{}

// Destructor
template<typename TaskType>
GenericTask<TaskType>::~GenericTask()
{}

// Functor to call the specific task
template<typename TaskType>
void GenericTask<TaskType>::operator()()
{
    //call the functor of the class?
    fTask();
}


/*
        ** DoPayment **
 */
DoPayment::DoPayment(std::string userFrom, std::string userTo, unsigned balance):
    fUserFrom(userFrom),
    fUserTo(userTo),
    fBalance(balance)
{
    //TODO: more initialization if needed.
}

DoPayment::~DoPayment()
{

}

void DoPayment::operator()()
{
}

/*
       ** CheckBalance **
 */
// Constructor
CheckBalance::CheckBalance(std::string user):
            fUser(user)
{}

// Functor.
void CheckBalance::operator()()
{
}
