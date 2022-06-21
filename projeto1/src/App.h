#ifndef DA_P1_APP_H
#define DA_P1_APP_H

#include "CourierList.h"
#include "OrderList.h"
#include "Courier.h"
#include "Order.h"
#include <string>
#include <vector>
using namespace std;

class App{
public:
    /**
     * @brief Construct a new App object (our App)
     * 
     */
    App();

    /**
     * @brief Prints all the options of scenarios that are supposed to be tested.
     * 
     */
    void printScenarioOptions();

    /**
     * @brief First Scenario.
     * A greedy algorithm that starts by organizing the Couriers and the Orders.
     * Organize in a descending order the Couriers by the amount of weight and volume available.
     * Organize in an ascending order the Orders by the sum of the volume and the weight.
     * Upon that, starts to fill the Couriers checking their currentWeight and currentVol occupied.
     * Prints the result of the algorithm.
     * 
     * @param CourierFile string argument - a file with the Couriers
     * @param OrderFIle string argument - a file with the Orders
     */
    void firstScenarioGreedy(string CourierFile, string OrderFile);

    /**
     * @brief Second Scenario.
     * A greedy algorithm that organizes the Couriers and the Orders.
     * Organizes in an ascending order the Couriers by their cost
     * Organizes in a descending order the Orders by their reward
     * Upon that, starts to fill the Couriers checking their currentWeight and currentVol occupied.
     * Prints the result of the algorithm.
     * 
     * @param CourierFile 
     * @param OrderFile 
     */
    void secondScenarioGreedy(string CourierFile, string OrderFile);

    /**
     * @brief Second Scenario.
     * A bin packing algorithm that organizes the Couriers and the Orders using a simple heuristic that measures how efficient
     * it is to deliver certain Orders using certain Couriers, by measuring and utilizing the profit metric, taking into account
     * the weight and volume and not only the cost/reward.
     * Organizes in an ascending order the Couriers by the profit metric (cost divided by weight and volume, so lower is better)
     * Organizes in a descending order the Orders by the profit metric (reward divided by weight and volume, so bigger is better)
     * Upon that, starts to fill the Couriers checking their currentWeight and currentVol occupied.
     * Prints the result of the algorithm.
     * 
     * @param CourierFile 
     * @param OrderFile 
     */

    void secondScenarioBinPacking(string CourierFile, string OrderFile);

    /**
     * @brief Third Scenario.
     * A greedy algorithm that sorts orders in a growing way based on their duration
     * Each order is delivered from the fastest to the slowest, being this delivered controlled by the time we have avaliable.
     * Avaliable time decreases with each order we deliver
     * @param OrderFile string argument - a file with the Orders
     */
    void thirdScenarioGreedy(string OrderFile);

    /**
     * @brief 
     * 
     * @param CourierFile string argument - a file with the Couriers
     * @param OrderFile string argument - a file with the Orders
     * @param option char argument - which scenario was chosen
     */
    void controlScenarios(string CourierFile, string OrderFile, char option);

    /**
     * @brief Prints all the tests' options.
     * 
     * @param test1 pointer to a value that will have the choice of the variable that will determinate the Couriers' file
     * @param test2 pointer to a value that will have the choice of the variable that will determinate the Orders' file
     * @param option char argument - which scenario was chosen
     * @return true 
     * @return false 
     */
    bool printTestsOptions(char *test1, char *test2, char option);

    /**
     * @brief According the option, will call the functions explicits of each Scenario
     * 
     * @param option char argument - which scenario was chosen
     */
    void dealWithTests(char option);

private:   
    vector<Order> oldOrders;
};

#endif //DA_P1_APP_H