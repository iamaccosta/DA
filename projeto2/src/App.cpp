#include "App.h"
#include "Scenarios.h"
#include <iostream>
#include <chrono>

using namespace std;

App::App()= default;

void App::printScenarioOptions(){
    cout << endl << "Welcome to the Travel Agency system manager" << endl << endl;

    cout << "[1] I want the group to stay together" << endl;
    cout << "[2] I don't care if the group split, as long we get together at the end ^^" << endl;
    cout << "[q] Exit" << endl;

    cout << "You must choose one of the options presented: ";
}

void App::printTests_GroupTogether(){
    cout << endl << "Welcome to the 1st Scenario, please choose what you want to test" << endl << endl;

    cout << "[1] Dimensão máxima possível de um grupo e qual o caminho que este irá percorrer" << endl;
    cout << "[2] Dimensão máxima possível de um grupo com o menor número de transbordos e qual o caminho que este irá percorrer" << endl;
    cout << "Choose one of the options presented:  ";
}

void App::printTests_GroupSplit(){
    cout << endl << "Welcome to the 2nd Scenario, please choose what you want to test" << endl << endl;

    cout << "[1] Determinar o caminho de um grupo de dimensão fixa" << endl;
    cout << "[2] Escolher um caminho melhor para que o tamanho de um grupo possa aumentar" << endl;
    cout << "[3] Dimensão máxima possível de um grupo e qual o caminho que este irá percorrer" << endl;
    cout << "[4] Dado um caminho e um grupo, determinar quando/onde este se voltará a reunir" << endl;
    cout << "[5] Maximo tempo de espera" << endl;
    cout << "Choose one of the options presented:  ";
}

void App::dealWithOptions(char scenario){
    char option;
    string input;
    Graph<int> g;
    Scenario scena;
    bool first_time = true;

    do{
        if (scenario == '1')
            this->printTests_GroupTogether();
        else if (scenario == '2')
            this->printTests_GroupSplit();

        cin >> option;

        do {
            input = choose_inputs();
        } while (input.empty());

        if(scenario == '1'){
            callFunctions_1(option, input);
        }else if(scenario == '2'){
            if(first_time){
                scena = Scenario(input, &g);
            }
            callFunctions_2(option, &g, scena);
        }

        do {
            cout << endl << "Do you want to continue testing? [y/n]  " << endl;
            cin >> option;
        } while (option != 'n' && option != 'y');

        first_time = false;
    }while(option == 'y');
}

string App::choose_inputs(){
    int input = 0;
    cout << endl << "Choose which input you want to use: " << endl;
    cout << "[1/2] 50 locais e 136 veículos" << endl;
    cout << "[3/4] 300 locais e 1417 veículos" << endl;
    cout << "[5/6] 1000 locais e 7533 veículos" << endl;
    cout << "[7/8] 90 locais e 257 veículos" << endl;
    cout << "[9/10] 5000 locais e 49487 veículos" << endl;
    cout << "[11] Nosso input, grafo dos slides das Aulas Teóricas, 6 locais e 20 veíulos" << endl;

    cout << "/**************************************************************************************/" << endl;
    cout << "/* Note: if you have already run once and you want to change the input for scenario 2 */" << endl;
    cout << "/*       you may need to reset the testing (go back to the first menu painel)         */" << endl;
    cout << "/**************************************************************************************/" << endl;
    cout << endl << "Choose one:  ";

    cin >> input;
    switch(input){
        case 1:
            return "../input/in01.txt";
        case 2:
            return "../input/in02.txt";
        case 3:
            return "../input/in03.txt";
        case 4:
            return "../input/in04.txt";
        case 5:
            return "../input/in05.txt";
        case 6:
            return "../input/in06.txt";
        case 7:
            return "../input/in07.txt";
        case 8:
            return "../input/in08.txt";
        case 9:
            return "../input/in09.txt";
        case 10:
            return "../input/in10.txt";
        case 11:
            return "../input/myIn.txt";
        default:
            cout << endl << "Invalid input! " << endl; 
            return "";
    }
}

void App::callFunctions_1( char option, string input) {
    Graph<int> g;
    Scenario scena = Scenario(input, &g);
    auto start = chrono::high_resolution_clock::now();

    switch (option) {
        case '1':
            scena.maxDimensaoGrp(g.findVertex(1), g.findVertex(g.getVertexSet().size()), g);
            break;
        case '2':
            //call function
            break;
        default:
            break;
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cout << endl << "Duration:   " << duration.count() << "   para Análise Empírica" << endl;

    do{
        cout << endl << "Do you want to print the graph? [y/n]  " << endl;
        cin >> option;
        if(option == 'y'){
            scena.printGraph(g);
        }
    }while(option != 'n' && option != 'y');
}

void App::callFunctions_2( char option, Graph<int> *g, Scenario scena) {
    auto start = chrono::high_resolution_clock::now();

    switch (option)
    {
        case '1':
            int dim;
            cout << endl << "Dimenssion:  ";
            do{
                cin >> dim;
            }while(dim <= 0);
            scena.determinatePath((*g).findVertex(1), (*g).findVertex((*g).getVertexSet().size()), dim, g);
            scena.printPath(*g, (*g).findVertex((*g).getVertexSet().size()));
            break;
        case '2':
            int incre;
            cout << endl << "Increment:  ";
            do{
                cin >> incre;
            }while(incre <= 0);
            scena.increaseGrpSize((*g).findVertex(1), (*g).findVertex((*g).getVertexSet().size()), incre, g);
            scena.printPath(*g, (*g).findVertex((*g).getVertexSet().size()));
            break;
        case '3':
            scena.maxDim_determinatePath((*g).findVertex(1), (*g).findVertex((*g).getVertexSet().size()), g);
            scena.printPath(*g, (*g).findVertex((*g).getVertexSet().size()));
            break;
        case '4':
            scena.timeOfReunion((*g).findVertex((*g).getVertexSet().size()), g);
            break;
        case '5':
            scena.maxTime((*g).findVertex(1), (*g).findVertex((*g).getVertexSet().size()), g);
            break;
        default:
            break;
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Duration:   " << duration.count() << "   para Análise Empírica" << endl;

    do{
        cout << endl << "Do you want to print the graph? [y/n]  ";
        cin >> option;
        if(option == 'y'){
            scena.printGraph(*g);
        }
    }while(option != 'n' && option != 'y');
}

