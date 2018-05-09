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
struct Task {
    protected:
        TaskStatus fTask;
    public:
        Task(TaskStatus status):
				fTask(status)
        {}
        ~Task() {}
        virtual void doTask() {
            throw EINVAL;
        }
};

struct GetBalance: public Task {
	protected:
		unsigned long fUserId;
    public:
        GetBalance(std::string username);
        virtual void doTask();
};


