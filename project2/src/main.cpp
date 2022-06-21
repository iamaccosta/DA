#include <iostream>
#include "App.h"

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
                myApp.dealWithOptions('1');
                break;
            case '2':
                myApp.dealWithOptions('2');
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
}