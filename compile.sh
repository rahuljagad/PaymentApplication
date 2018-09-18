g++ -c -std=c++11 User.cc
g++  --std=c++11 -c tasks.cc
g++ -o venmo --std=c++11 -lpthread User.o tasks.o main.cc
#Where is the end marker ?
