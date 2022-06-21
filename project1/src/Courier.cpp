#include <iostream>
#include "Courier.h"
using namespace std;

Courier::Courier(int volMax, int weightMax, int cost) {
    this->volMax = volMax;
    this->weightMax = weightMax;
    this->cost = cost;
    this->currentVol = 0;
    this->currentWeight = 0;
}

int Courier::getVolMax() const{
    return this->volMax;
}

int Courier::getWeightMax() const{
    return this->weightMax;
}

int Courier::getCurrentVol() const{
    return this->currentVol;
}

int Courier::getCurrentWeight() const{
    return this->currentWeight;
}

int Courier::getCost() const{
    return this->cost;
}

void Courier::setCurrentVol(int vol){
    this->currentVol+=vol;
}

void Courier::setCurrentWeight(int weight){
    this->currentWeight+=weight;
}

void Courier::setVolMax(int vol) {
    this->volMax = vol;
}

void Courier::setWeightMax(int weight) {
    this->weightMax = weight;
}

void Courier::setCost(int cost) {
    this->cost = cost;
}

bool sortCouriersByMax(const Courier &e1, const Courier &e2){
    return e1.getVolMax() + e1.getWeightMax() > e2.getVolMax() + e2.getWeightMax();
}

bool sortCouriersByProfit(const Courier &e1, const Courier &e2){
    return ((e1.getCost() / (e1.getVolMax() + e1.getWeightMax())) < (e2.getCost() / (e2.getVolMax() + e2.getWeightMax())));
}

bool sortCouriersByCost(const Courier &e1, const Courier &e2){
    return e1.getCost() < e2.getCost();
}

// void Courier::printInfo() {
//     cout << this->volMax << " " << this->weightMax << " " << this->cost;
// }
