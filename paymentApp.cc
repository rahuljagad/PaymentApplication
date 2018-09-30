//
//  paymentApp.cc
//  PaymentApplication
//
//  Created by Rahul Jagad on 9/29/18.
//
#include <thread>

#include "paymentApp.h"

template<typename App>
App::Executor<App>::Executor()
fApp { new App ( args ) }
{
    std::thread thread { fApp() };
}
