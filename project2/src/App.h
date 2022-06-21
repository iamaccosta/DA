#ifndef DA_P2_APP_H
#define DA_P2_APP_H

#include <string>
#include "Graph.h"
#include "Scenarios.h"

using namespace std;

class App{
public:
    /**
     * @brief Construct a new App object
     *
     */
    App();


    /**
     * @brief print the 2 scenarios that can happen
     * 
     */
    void printScenarioOptions();

    /**
     * @brief present the options that can be tested, when group stay together
     * 
     */
    void printTests_GroupTogether();

    /**
     * @brief present the options that can be testes, when the group split
     * 
     */
    void printTests_GroupSplit();

    /**
     * @brief deal with options that were chosen by the user
     * 
     */
    void dealWithOptions(char scenario);

    /**
     * @brief asks user what input file he wants to use
     *
     * @return file name
     */
    string choose_inputs();

    /**
     * @brief calls the functions from scenario 1, depending on option
     *
     * @param option
     * @param input
     */
    void callFunctions_1( char option, string input);

    /**
     * @brief calls the functions from scenario 1, depending on option
     *
     * @param option
     * @param g
     * @param scena
     */
    void callFunctions_2( char option, Graph<int> *g, Scenario scena);
private:
};

#endif //DA_P2_APP_H