#include <iostream>

#include "mcronald.h"
#include "restaurant.h"
#include "order.h"


McRonald::McRonald():Restaurant("Happy Place", 10) {
   deluxe_order_count_ = 0;
   deluxe_orders_front_ = nullptr;
   deluxe_orders_end_ = nullptr; 
}


McRonald::McRonald(std::string n, int m):Restaurant(n, m) {
    deluxe_order_count_ = 0;
    deluxe_orders_front_ = nullptr;
    deluxe_orders_end_ = nullptr;
}


void McRonald::displayMenu() {
    std::cout << "Welcome to McRonald!" << std::endl;
    std::cout << "---------------------" << std:: endl;
    std::cout << "On today's menu: " << std::endl;
    std::cout << "-Hamburger" << std::endl;
    std::cout << "-Fries" << std::endl;
    std::cout << "-Kale-icious Greens" << std::endl;
    std::cout << "---------------------" << std:: endl;
    std::cout << "The special of the day is: Gordan-Hamsey Burger" << std::endl;
    std::cout << " -- It takes a bite out of you too!" << std::endl;
    std::cout << "We've also got the Peas and Thank You Burger, I Heartichoke You Burger,\nHit Me With Your Best Shallot Burger! - courtesy of Bob's Burgers" << std::endl; 
}


bool McRonald::placeOrder(std::string n, std::string f) {
    return Restaurant::placeOrder(n, f);
}


bool McRonald::placeDeluxeOrder(std::string n, std::string f) {
    if (!isOpen() || total_order_count_ == getMaxCounterSpace()) return false;
    Order* new_order = new Order(n, f);
    if (deluxe_orders_end_ == nullptr) {
        deluxe_orders_front_ = new_order;
    } else {
        deluxe_orders_end_->setNextOrder(new_order);
    }
    deluxe_orders_end_ = new_order;
    deluxe_order_count_++;
    total_order_count_++;
    return true;
}

bool McRonald::pickUpOrder() {
    if (!isOpen()) return false;
    if (deluxe_order_count_ > 0) {
        Order *curr_front = deluxe_orders_front_;
        if (curr_front->isComplete()) {
            deluxe_orders_front_ = deluxe_orders_front_->getNextOrder();
            delete curr_front;
            deluxe_order_count_--;
            total_order_count_--;
            return true;   
        }

        return false;
    } else {
        return Restaurant::pickUpOrder();
    }
}


void McRonald::printOrders() {
    Restaurant::printOrders();
    Order *currOrder = deluxe_orders_front_;
    for (int i = 0; i < deluxe_order_count_; i++) {
        std::cout << "\nOrder #" << i << " : ";
        currOrder->printOrder();
    }

    std::cout << "\n--Total number of deluxe orders: " << deluxe_order_count_ << std::endl;
}


bool McRonald::completeOrder() {
// Returns true if a new order was completed and is ready for a customer, false if there were no orders to complete
    Order* incomplete_order = deluxe_orders_front_;
    if (!isOpen() || incomplete_order == nullptr) return Restaurant::completeOrder();
    while (incomplete_order != nullptr && incomplete_order->isComplete()) {
        incomplete_order = incomplete_order->getNextOrder();
    }

    if (incomplete_order != NULL) {
        return incomplete_order->completeOrder();
    }

    return Restaurant::completeOrder();
}


int McRonald::getDeluxeOrderCount() {
	return deluxe_order_count_;
}


McRonald::~McRonald() {
    Order* curr_order = deluxe_orders_front_;
    while (curr_order) {
        Order *temp = curr_order;
        curr_order = curr_order->getNextOrder();
        delete temp;
    }
}
