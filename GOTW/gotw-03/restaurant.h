#pragma once

#include <stdlib.h>
#include <iostream>
#include <string>

#include "order.h"


class Restaurant {
    public:
        Restaurant();
        Restaurant(std::string n, int max);
        virtual ~Restaurant();

        void open();
        void close();
        virtual bool placeOrder(std::string n, std::string f); // Add an order
        virtual bool pickUpOrder(); // Wait for customer to pick up order; remove order from list
        virtual bool completeOrder();
        virtual void displayMenu(); // Print out menu
        virtual void printOrders();
     
        bool isOpen();
        int getMaxCounterSpace();
        int getOrderCount();
        std::string getName();
        Order* getOrdersFront();

        Order* orders_front_; // List of orders - TODO: Add public accessor to front of the list (encapsulate)
        Order* orders_end_; // List of orders
        int total_order_count_;

    private:
        bool is_open_;
        int max_counter_space_; // Limits number of orders that can be picked up
        int order_count_;
        
        std::string name_;
};

// - stack vs. heap errors
// - continuing to master control over gdb

/*
- gdb_3:
      - Memory errors with lists
      - Class w/ list and functions which mod the private list/stack
          -->Function runs an unprotected op (popping from empty stack/queue/vector)
          -->Leaking Base class's restaurant memory
-->Theme: Restaurant Orders in Linked List (Front/Back Order Pointers)
BUGS:
*/
