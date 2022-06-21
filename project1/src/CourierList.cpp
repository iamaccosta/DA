#include "CourierList.h"
#include "Courier.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

CourierList::CourierList(string filename) {
    ifstream file(filename);
    string line;
    stringstream lineStream;
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            lineStream << line;
            int volMax, weightMax, cost;
            lineStream >> volMax >> weightMax >> cost;
            Courier courier = Courier(volMax, weightMax, cost);
            couriers.push_back(courier);
            lineStream.str("");
            lineStream.clear();
        }
        file.close();
    }
    else { cout << "Unable to open Courier file." << endl; }
}

vector<Courier> CourierList::getCouriers() const {
    return this->couriers;
}
