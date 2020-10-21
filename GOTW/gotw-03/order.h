#pragma once

#include <iostream>
#include <string>


class Order {
    public:
        Order();
        Order(std::string n, std::string f);

        void printOrder();
        bool completeOrder();
        bool isComplete();

        Order* getNextOrder();
        void setNextOrder(Order* new_next);


    private:
        std::string food_;
        std::string name_;
        bool completed_;
        Order* next_order_;
};
