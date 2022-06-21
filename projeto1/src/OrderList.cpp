#include "OrderList.h"
#include "Order.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

OrderList::OrderList(string filename) {
    ifstream file(filename);
    string line;
    stringstream lineStream;
    int vol, weight, reward, duration;

    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            lineStream << line;
            lineStream >> vol >> weight >> reward >> duration;
            //cout << vol << "\n";
            Order order = Order(vol, weight, reward, duration);
            orders.push_back(order);
            lineStream.str("");
            lineStream.clear();
        }
        file.close();
    }
    else { cout << "Unable to open Order file." << endl; }
}

vector<Order> OrderList::getOrders() const{
    return this->orders;
}
