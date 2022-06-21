#ifndef DA_P1_ORDER_H
#define DA_P1_ORDER_H


#include <string>

class Order {
public:
    /**
     * @brief Construct a new Order object.
     * 
     * @param vol volume - integer parameter
     * @param weight peso - integer parameter
     * @param reward recompensa - integer parameter
     * @param duration duração - integer parameter (s)
     */
    Order(int vol, int weight, int reward, int duration);

    //Getters
    int getVol() const;
    int getWeight() const;
    int getReward() const;
    int getDuration() const;

    //Setters
    void setDelivered();
    
    /**
     * @brief checks if the Order is delivered or not, returning true if it is.
     * 
     * @return true 
     * @return false 
     */
    bool isDelivered() const;

    void printInfo();
private:
    int vol, weight, reward, duration;
    bool delivered;
};

/**
 * @brief Compares 2 Orders.
 * Compares the sum of the volume and the weight of 2 Orders, returning true if the first is bigger than the second.
 * 
 * @param o1 first Order
 * @param o2 second Order
 * @return true 
 * @return false 
 */
bool sortOrdersByMin(const Order &o1, const Order &o2);

/**
 * @brief Compares the duration of 2 Orders, returning true if the first's duration is smaller than the second
 * 
 * @param o1 first Order
 * @param o2 second Order
 * @return true 
 * @return false 
 */
bool sortOrdersByTime(const Order &o1, const Order &o2);

/**
 * @brief Compares the duration of 2 Orders, returning true if the first's profit metric (reward divided by weight plus volume)
 * is smaller than the second
 * 
 * @param o1 first Order
 * @param o2 second Order
 * @return true 
 * @return false 
 */

bool sortOrdersByProfit(const Order &o1, const Order &o2);

/**
 * @brief Compares the duration of 2 Orders, returning true if the first's reward is bigger than the second
 * 
 * @param o1 first Order
 * @param o2 second Order
 * @return true 
 * @return false 
 */

bool sortOrdersByReward(const Order &o1, const Order &o2);

#endif //DA_P1_ORDER_H