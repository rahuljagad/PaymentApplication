//
//  paymentApp.cc
//  PaymentApplication
//
//  Created by Rahul Jagad on 9/29/18.
//
#include <thread>

#include "paymentApp.h"

template<typename App>
Framework::Executor<App>::Executor():
   fApp { new App() }
{
    fThread = std::thread { fApp() };
}

template<typename App>
Framework::Executor<App>::~Executor()
{
    fThread.join();
}
