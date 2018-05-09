#include <thread>
#include <iostream>
#include "user.h"
#include "tasks.h"

//These are the globals ( probably can be stored in the database somewhere as well )
std::queue<Tasks> gTasks;
std::map<uint32_t, User> gUsers;

void ParseUserInput(char *input)
{
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
        )
        switch (option) {
            case 'u':
                ParseUserInput(optarg);
                break;
            default:
                throw gUsage;
        }
    argc -= optind, argv += optind;
   
#if 0 
    std::thread taskWorker{ PerformTasks };  
    //Wait for the user input and puts it in the tasks queue
    //Tasks worker then pulls the tasks from the queue and does the tasks
    while ( 1 ) {
        try {

            gTasks.push(AcceptInput()); 

        } catch ( ... )  { //TODO : more error checking
            std::cout<<"Probably invalid tasks"<<std::endl;
        }
    }

#endif
}
