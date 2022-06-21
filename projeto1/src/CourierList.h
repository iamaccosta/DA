#ifndef DA_P1_COURIERLIST_H
#define DA_P1_COURIERLIST_H

#include <string>
#include <vector>
#include "Courier.h"

using namespace std;

class CourierList {
public:
    /**
     * @brief Construct a new Courier List object.
     * It creates a vector of Couriers, that will be helpfull with the organization of their work.
     * 
     * @param filename string argument with a name of a file with the Couriers to be read
     */
    CourierList(std::string filename);

    //Getters
    vector<Courier> getCouriers() const;
private:
    vector<Courier> couriers;
};


#endif //DA_P1_COURIERLIST_H
