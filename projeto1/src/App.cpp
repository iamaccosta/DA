#include "App.h"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

App::App(){}

void App::printScenarioOptions(){
    cout << endl << "Welcome to the Urban Logistic Orders Deliver system manager" << endl << endl;

    cout << "[1] Staff number Optimization" << endl;
    cout << "[2] Profit Optimization using Greedy" << endl;
    cout << "[3] Profit Optimization using Bin Packing" << endl;
    cout << "[4] Express Delivery Optimization" << endl;
    cout << "[q] Exit" << endl;
    cout << "Choose one of the following Scenarios:  ";
}

void App::firstScenarioGreedy(string CourierFile, string OrderFile){
    CourierList couriers = CourierList(CourierFile);
    OrderList orders = OrderList(OrderFile);
    //getting the couriers and sorting them from max to min
    vector<Courier> sortedCouriers = couriers.getCouriers();
    sort(sortedCouriers.begin(), sortedCouriers.end(), sortCouriersByMax);

    //getting the orders and sorting them from min to max
    vector<Order> sortedOrders = orders.getOrders();
    sort(sortedOrders.begin(), sortedOrders.end(), sortOrdersByMin);

    //result
    int result = 0, oldResult = 0;

    //deliver old Orders first
    sort(oldOrders.begin(), oldOrders.end(), sortOrdersByMin);
    int deliveredOrders = 0;
    if(oldOrders.size() != 0){ //se oldOrders não estiver vazio
        for(auto couriersIt = sortedCouriers.begin(); couriersIt != sortedCouriers.end(); couriersIt++){
            if(deliveredOrders == oldOrders.size())
                break;
            for(auto ordersIt = oldOrders.begin() /*+ deliveredOrders*/; ordersIt != oldOrders.end(); ordersIt++){
                if((!(ordersIt->isDelivered())) && couriersIt->getCurrentVol() + ordersIt->getVol() <= couriersIt->getVolMax() && couriersIt->getCurrentWeight() + ordersIt->getWeight() <= couriersIt->getWeightMax()){
                    if(couriersIt->getCurrentVol() == 0 && couriersIt->getCurrentWeight() == 0)
                        result += 1;
                    couriersIt->setCurrentVol(ordersIt->getVol());
                    couriersIt->setCurrentWeight(ordersIt->getWeight());
                    ordersIt->setDelivered();
                    deliveredOrders++;
                }
                /*else
                    break;
                */
            }
          
        }
    }
    else
        cout << "No old Orders to be delivered!" << endl;

    oldResult = result;
    if(deliveredOrders != 0 && deliveredOrders == oldOrders.size()){ // se chegou ao fim das encomendas antigas, limpa-as
        cout << endl << "Old Orders were all delivered!" << endl;
        oldOrders.clear();
    }
    else if(deliveredOrders != 0){ // se não limpa apenas as que entregou
        cout << "A total of " << deliveredOrders << "(" << 100 * ((float)deliveredOrders / (float)oldOrders.size()) << "%) old orders were delivered" << endl;
        reverse(oldOrders.begin(), oldOrders.end());
        for(int i = 0; i < deliveredOrders; i++)
            oldOrders.pop_back();
    }

    //deliver new Orders
    int i = 0;
    deliveredOrders = 0;
    for (auto couriersIt = sortedCouriers.begin() + result; couriersIt != sortedCouriers.end(); couriersIt++){
        if(deliveredOrders == sortedOrders.size())
            break;
        for (auto ordersIt = sortedOrders.begin() /*+ deliveredOrders*/; ordersIt != sortedOrders.end(); ordersIt++){
            if((!(ordersIt->isDelivered())) && couriersIt->getCurrentVol() + ordersIt->getVol() <= couriersIt->getVolMax() && couriersIt->getCurrentWeight() + ordersIt->getWeight() <= couriersIt->getWeightMax()){
                if(couriersIt->getCurrentVol() == 0 && couriersIt->getCurrentWeight() == 0)
                    result += 1;
                couriersIt->setCurrentVol(ordersIt->getVol());
                couriersIt->setCurrentWeight(ordersIt->getWeight());
                ordersIt->setDelivered();
                deliveredOrders++;
            }
            /*else
                break;
            */
        }
    }

    //mete as encomendas restantes para o dia 
    if(deliveredOrders < sortedOrders.size()){
        for(auto ordersIt = sortedOrders.begin() + deliveredOrders; ordersIt != sortedOrders.end(); ordersIt++){
            oldOrders.push_back(*ordersIt);
        }
    }
    cout << endl << "There were used " << result << " couriers (" << 100 * ((float)result / (float)sortedCouriers.size()) << "%) " << oldResult << " for old orders and " << result - oldResult << " for new orders" << endl;
    cout << "A total of " << deliveredOrders << " (" << 100 * ((float)deliveredOrders / (float)sortedOrders.size()) << "%) orders were delivered!" << endl;
    cout << oldOrders.size() << " orders were passed to the next day!" << endl;
}

void App::secondScenarioGreedy(string CourierFile, string OrderFile) {
    CourierList couriers = CourierList(CourierFile);
    OrderList orders = OrderList(OrderFile);

    vector<Courier> sortedCouriers = couriers.getCouriers();
    sort(sortedCouriers.begin(), sortedCouriers.end(), sortCouriersByCost);

    vector<Order> sortedOrders = orders.getOrders();
    sort(sortedOrders.begin(), sortedOrders.end(), sortOrdersByReward);
    auto ordersIt = sortedOrders.begin();

    int result = 0;
    int deliveredOrders = 0;
    int profit = 0;

    for (auto couriersIt = sortedCouriers.begin(); couriersIt != sortedCouriers.end(); couriersIt++){
        if (deliveredOrders == sortedOrders.size())  {
            break;
        }
        
        profit -= couriersIt->getCost();

        for (; ordersIt != sortedOrders.end(); ordersIt++){
            if((!(ordersIt->isDelivered())) && couriersIt->getCurrentVol() + ordersIt->getVol() <= couriersIt->getVolMax() && couriersIt->getCurrentWeight() + ordersIt->getWeight() <= couriersIt->getWeightMax()){
                profit += ordersIt->getReward();
                couriersIt->setCurrentVol(ordersIt->getVol());
                couriersIt->setCurrentWeight(ordersIt->getWeight());
                ordersIt->setDelivered();
                deliveredOrders++;
            }
        }
        ordersIt = sortedOrders.begin();
    }

    cout << "A total of " << deliveredOrders << " (" << 100 * ((float)deliveredOrders / (float)sortedOrders.size()) << "%) orders were delivered!" << endl;
    cout << "The total profit was " << profit << " !";

}

void App::secondScenarioBinPacking(string CourierFile, string OrderFile) {
    CourierList couriers = CourierList(CourierFile);
    OrderList orders = OrderList(OrderFile);

    vector<Courier> sortedCouriers = couriers.getCouriers();
    sort(sortedCouriers.begin(), sortedCouriers.end(), sortCouriersByProfit);

    vector<Order> sortedOrders = orders.getOrders();
    sort(sortedOrders.begin(), sortedOrders.end(), sortOrdersByProfit);
    auto ordersIt = sortedOrders.begin();

    int result = 0;
    int deliveredOrders = 0;
    int profit = 0;

    for (auto couriersIt = sortedCouriers.begin(); couriersIt != sortedCouriers.end(); couriersIt++){
        if (deliveredOrders == sortedOrders.size())  {
            break;
        }
        
        profit -= couriersIt->getCost();

        for (; ordersIt != sortedOrders.end(); ordersIt++){
            if((!(ordersIt->isDelivered())) && couriersIt->getCurrentVol() + ordersIt->getVol() <= couriersIt->getVolMax() && couriersIt->getCurrentWeight() + ordersIt->getWeight() <= couriersIt->getWeightMax()){
                profit += ordersIt->getReward();
                couriersIt->setCurrentVol(ordersIt->getVol());
                couriersIt->setCurrentWeight(ordersIt->getWeight());
                ordersIt->setDelivered();
                deliveredOrders++;
            }
        }
        ordersIt = sortedOrders.begin();
    }

    cout << "A total of " << deliveredOrders << " (" << 100 * ((float)deliveredOrders / (float)sortedOrders.size()) << "%) orders were delivered!" << endl;
    cout << "The total profit was " << profit << " !";
}

void App::thirdScenarioGreedy(string OrderFile){
    OrderList orders = OrderList(OrderFile);
    int time = 8 * 60 * 60;
    auto sortedOrders = orders.getOrders();
    sort(sortedOrders.begin(), sortedOrders.end(), sortOrdersByTime);
    int i = 0;
    int result = 0;
    while(time > 0){

        if (time - sortedOrders[i].getDuration() < 0)
            break;

        time -= sortedOrders[i].getDuration();
        result += 1;
        i += 1;
    }

    cout << result << " orders (" << 100 * ((float)result / (float)sortedOrders.size()) << "%) were processed with a remaining time of " << time << " seconds" << endl;
    if(i + 1 < sortedOrders.size())
        cout << "The fastest non delivered order had a total time of " << sortedOrders[i + 1].getDuration() << endl;
}

void App::controlScenarios(string CourierFile, string OrderFile, char option){
    switch (option){
        case '1':
            this->firstScenarioGreedy(CourierFile, OrderFile);
            break;
        case '2':
            this->secondScenarioGreedy(CourierFile, OrderFile);
            break;
        case '3':
            this->secondScenarioBinPacking(CourierFile, OrderFile);
            break;       
        case '4':
            this->thirdScenarioGreedy(OrderFile);
            break;
        default:
            break;
    }
}


bool App::printTestsOptions(char *test1, char *test2, char option){
    switch (option){
        case '1':
            cout << endl << "Welcome to the 1st Scenario, please choose how do you want to test the variables" << endl << endl;
            break;
        case '2':
            cout << endl << "Welcome to the 2nd Scenario Greedy, please choose how do you want to test the variables" << endl << endl;
            break;
        case '3':
            cout << endl << "Welcome to the 2nd Scenario Bin Packing, please choose how do you want to test the variables" << endl << endl;
            break;           
        case '4':
            cout << endl << "Welcome to the 3rd Scenario, please choose how do you want to test the variables" << endl << endl;
            break;
        default:
            break;
    }

    if(option == '1' || option == '2' || option == '3'){
        cout << "[1] Few Couriers available" << endl;
        cout << "[2] All Couriers available" << endl;
        cout << "Choose one of the following:  ";
        cin >> *test1;
        if(*test1 != '1' && *test1 != '2') return false;
    }
    else
        *test1 = '2';
    
    cout << "[1] Few Orders available" << endl;
    cout << "[2] Some Orders available" << endl;
    cout << "[3] Many Orders available" << endl;
    cout << "Choose one of the following:  ";
    cin >> *test2;
    if(*test2 != '1' && *test2 != '2' && *test2 != '3') return false;

    return true;
}

void App::dealWithTests(char option){
    char test1, test2;
    do{
        if(printTestsOptions(&test1, &test2, option)){
            cout << endl;
            if(test1 == '1'){
                switch (test2){
                    case '1':
                        this->controlScenarios("../input/poucasCarrinhas.txt", "../input/poucasEncomendas.txt", option);
                        break;
                    case '2':
                        this->controlScenarios("../input/poucasCarrinhas.txt", "../input/encomendas.txt", option);
                        break;
                    case '3':
                        this->controlScenarios("../input/poucasCarrinhas.txt", "../input/muitasEncomendas.txt", option);
                        break;
                    default:
                        break;
                    }
            }
            else if(test1 == '2'){
                switch (test2){
                    case '1':
                        this->controlScenarios("../input/carrinhas.txt", "../input/poucasEncomendas.txt", option);
                        break;
                    case '2':
                        this->controlScenarios("../input/carrinhas.txt", "../input/encomendas.txt", option);
                        break;
                    case '3':
                        this->controlScenarios("../input/carrinhas.txt", "../input/muitasEncomendas.txt", option);
                        break;
                    default:
                        break;
                    }
            }
        }
        else
            cout << endl << "invalid input" << endl;
        
        do{
            cout << endl << "Do you want to continue testing? [y/n] ";
            cin >> test1;
        }while(test1 != 'y' && test1 != 'n');
        
    }while(test1 == 'y' && test1 != 'n');
}

