#include <iostream>
#include "Order.h"
using namespace std;

Order::Order(int vol, int weight, int reward, int duration){
    this->vol = vol;
    this->weight = weight;
    this->reward = reward;
    this->duration = duration;
    this->delivered = false;
}

int Order::getVol() const{
    return this->vol;
}

int Order::getWeight() const{
    return this->weight;
}

bool Order::isDelivered() const{
    return this->delivered;
}

void Order::setDelivered(){
    this->delivered = true;
}

int Order::getReward() const{
    return this->reward;
}

int Order::getDuration() const{
    return this->duration;
}

bool sortOrdersByMin(const Order &o1, const Order &o2){
    return o1.getVol() + o1.getWeight() < o2.getVol() + o2.getWeight();
}

bool sortOrdersByProfit(const Order &o1, const Order &o2){
    return ((o1.getReward() / (o1.getVol() + o1.getWeight())) > (o2.getReward() / (o2.getVol() + o2.getWeight())));
}

bool sortOrdersByReward(const Order &o1, const Order &o2){
    return o1.getReward() > o2.getReward();
}


bool sortOrdersByTime(const Order &o1, const Order &o2){
    return o1.getDuration() < o2.getDuration();
}

void Order::printInfo() {
    cout << this->vol << " " << this->weight << " " << this->reward << " " << this->duration;
}
