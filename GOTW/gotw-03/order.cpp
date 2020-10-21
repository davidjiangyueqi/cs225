#include "order.h"


Order::Order() {
    food_ = "Grub";
    name_ = "Customer";
    completed_ = false;
    next_order_ = nullptr;
}


Order::Order(std::string n, std::string f) {
    name_ = n;
    food_ = f;
    completed_ = false;
    next_order_ = NULL;
}


void Order::printOrder() {
    std::cout << name_ << " -- " << food_;
}


bool Order::completeOrder() {
    return completed_ = true;
}


bool Order::isComplete() {
    return completed_;
}

Order* Order::getNextOrder() {
    return next_order_;
}

void Order::setNextOrder(Order* new_next) {
    next_order_ = new_next;
}
