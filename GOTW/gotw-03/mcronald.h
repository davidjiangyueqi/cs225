#pragma once

#include "restaurant.h"
#include "queue"


class McRonald : public Restaurant {
    public:
        McRonald();
        McRonald(std::string n, int m);
        ~McRonald();

        bool placeOrder(std::string n, std::string f);
        bool placeDeluxeOrder(std::string n, std::string f); // Add a deluxe, high-priority order
        bool pickUpOrder();
        bool completeOrder(); // Completes the next available order; return false if there were no new orders
        void displayMenu();
        void printOrders();

        int getDeluxeOrderCount();
        
    private:
        int deluxe_order_count_;
        Order* deluxe_orders_front_; // List of orders
        Order* deluxe_orders_end_; // List of orders
};
