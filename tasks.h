#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>

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
        virtual bool doTask() {
            throw EINVAL;
        }
};

struct GetBalance: public Task {
    public:
        GetBalance();
        virtual bool doTask();
};


