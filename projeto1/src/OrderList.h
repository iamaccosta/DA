#ifndef DA_P1_ORDERLIST_H
#define DA_P1_ORDERLIST_H


#include <string>
#include <vector>
#include "Order.h"

using namespace std;

class OrderList {
public:
    /**
     * @brief Construct a new Order List object.
     * It creates a vector of Orders, that will help with their distribution.
     * 
     * @param filename string argument with a name of a file with the Orders to be read
     */
    OrderList(std::string filename);
    
    //Getters
    vector<Order> getOrders() const;

    //Setters
    void setOldOrders(vector<Order> oldOrders);

private:
    vector<Order> orders;
};


#endif //DA_P1_ORDERLIST_H