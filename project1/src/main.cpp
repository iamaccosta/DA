#include "Courier.h"
#include "CourierList.h"
#include "Order.h"
#include "OrderList.h"
#include "App.h"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int main(){
    App myApp;
    char option;
    do {
        myApp.printScenarioOptions();
        cin >> option;
        cout << endl;

        switch (option) {
            case '1':
            case '2':
            case '3':
            case '4':
                myApp.dealWithTests(option);
                break;
            case 'q':
                cout << "Thank you for using our system!" << endl;
                break;
            default:
                cout << "invalid input" << endl;
                break;
        }
        cout << endl;
    }while(option != 'q');
    return 0;
};
