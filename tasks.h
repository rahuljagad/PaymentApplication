#include <iostream>
#include <queue>

// Base class that represents the type of tasks 
enum class TaskStatus { QUEUED, STARTED, DONE };
struct Task {
    protected:
        TaskStatus fTask;
    public:
        Task(TaskStatus status):
            fTask(status)
        {}
        ~Tasks() {}
        virtual bool doTasks() {
            throw EINVAL;
        }
};

struct GetBalance: public Task {
    protected:
        uint32_t fUserId;
    protected:
        GetBalance(uint32_t userid);
        virtual bool doTasks();
};


