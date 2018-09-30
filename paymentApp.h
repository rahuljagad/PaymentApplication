//
//  paymentApp.h
//  PaymentApplication
//
//  Created by Rahul Jagad on 9/29/18.
//
#pragma once
#include <iostream>

namespace Framework
{
    
    //Acts like the Execution Framework for any long-running application.
    template<typename App>
    class Executor {
    public:
        Executor();
        ~Executor();
    private:
        std::unique_ptr<App> fApp;
        std::thread fThread;
    }; //Executor
    
    
} //App
