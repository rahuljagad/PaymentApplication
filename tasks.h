/* 
 *		tasks.h
*/
#pragma once
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <map>
#include "User.h"

void PerformTasks();

// Base class that represents the type of tasks 
enum class TaskStatus { QUEUED, STARTED, DONE };
//Maybe this tasks should be templatized to indicate the 
//type of tasks
struct Task {
    public:
        Task(TaskStatus status):
				fTask(status)
        {}
        ~Task() {}
        virtual void doTask() {
            throw EINVAL;
        }

    protected:
        TaskStatus fTask;
};


// GetBalance Task
struct GetBalance: public Task {
	protected:
		unsigned long fUserId;
    public:
        GetBalance(std::string username);
        virtual void doTask();
};

// MakePayment Task
struct MakePayment : public Task {
	protected: 
		unsigned	fBalance;
		unsigned long fUserFrom;
		unsigned long fUserTo;
	public:
		MakePayment(std::string userFrom, std::string userTo, unsigned balance);
		virtual void doTask();
};

/*
        ** Generic Task **
*/

template<typename TaskType>
class GenericTask {
public:
    GenericTask(TaskType &);
    ~GenericTask();
    void operator()();
    
private:
    using TaskT = TaskType;
    TaskT   fTask;
};

// Do Payment Task
struct DoPayment {
public:
    explicit DoPayment(std::string userFrom, std::string userTo, unsigned balance);
    ~DoPayment();
    void operator()();

private:
    std::string fUserFrom;
    std::string fUserTo;
    unsigned    fBalance;
    
};
