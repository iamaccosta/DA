#ifndef DA_P1_COURIER_H
#define DA_P1_COURIER_H

#include <string>
using namespace std;

class Courier {
public:
    /**
     * @brief Construct a new Courier object.
     * 
     * @param volMax volume máximo - integer parameter
     * @param weightMax peso máximo - integer parameter
     * @param cost custo - integer parameter
     */
    Courier(int volMax, int weightMax, int cost);

    //Getters
    int getVolMax() const;
    int getWeightMax() const;
    int getCost() const;
    int getCurrentVol() const;
    int getCurrentWeight() const;

    //Setters
    void setVolMax(int vol);
    void setWeightMax(int weight);
    void setCost(int cost);
    /**
     * @brief Set the Current Vol object.
     * Update the current occupied weight. 
     * 
     * @param vol volume - integer parameter
     */
    void setCurrentVol(int vol);
    /**
     * @brief Set the Current Weight object.
     * Update the current occupied weight.
     *  
     * @param weight peso - integer parameter
     */
    void setCurrentWeight(int weight);

    void printInfo();
private:
    string licensePlate;
    int volMax, weightMax, cost, currentVol, currentWeight;
};

/**
 * @brief Compares 2 Couriers.
 * Compares the sum of the volume max and weight max of the 2 Couriers, returning true if the first is bigger than the second.
 * 
 * @param e1 first Courier
 * @param e2 second Courier
 * @return true 
 * @return false 
 */
bool sortCouriersByMax(const Courier &e1, const Courier &e2);

/**
 * @brief Compares 2 Couriers.
 * Compares the cost of using the Courier divided by the sum of their weight and volume, returns true if the second is bigger than
 * the first
 * 
 * @param e1 first Courier
 * @param e2 second Courier
 * @return true 
 * @return false 
 */
bool sortCouriersByProfit(const Courier &e1, const Courier &e2);

/**
 * @brief Compares 2 Couriers.
 * Returns true if Courier e1 has a lower cost than Courier e2
 * 
 * @param e1 first Courier
 * @param e2 second Courier
 * @return true 
 * @return false 
 */
bool sortCouriersByCost(const Courier &e1, const Courier &e2);

#endif //DA_P1_COURIER_H
