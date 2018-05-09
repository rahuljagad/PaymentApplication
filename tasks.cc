#include "tasks.h"

GetBalance::GetBalance(uint32_t userid):
        fUserId(userid),
        Tasks(QUEUE)
{ 
}

void GetBalance::doTasks()
{
    gUsers[userId].GetBalance();
}
