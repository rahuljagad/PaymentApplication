//
//  paymentApp.h
//  PaymentApplication
//
//  Created by Rahul Jagad on 9/29/18.
//
#pragma once
#include <iostream>

namespace App
{
    
    template<typename App>
    class Executor {
    public:
        Executor();
    private:
        std::unique_ptr<App> fApp;
    }; //Executor
    
} //App
