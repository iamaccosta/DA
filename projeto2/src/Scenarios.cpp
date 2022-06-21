#include "Graph.h"
#include "Scenarios.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

Scenario::Scenario()= default;

Scenario::Scenario(const string& input, Graph<int> *g){
    int nr_locais, nr_veiculos, orig, dest, capac, duracao;

    ifstream file(input);
    string line;
    stringstream lineStream;
    if(file.is_open()){
        getline(file, line);
        lineStream << line;
        lineStream >> nr_locais >> nr_veiculos;
        lineStream.str("");
        lineStream.clear();

        for(int i = 1; i <= nr_locais; i++){
            (*g).addVertex(i);
        }

        while(getline(file, line)){
            lineStream << line;
            lineStream >> orig >> dest >> capac >> duracao;

            (*g).addEdge(orig, dest, capac, duracao, 0);

            lineStream.str("");
            lineStream.clear();
        }
    }
}


void Scenario::printGraph(Graph<int> g) {
    vector<Vertex<int> *> vertSet = g.getVertexSet();

    for(Vertex<int> *v: vertSet){
        int i = 1;
        cout << "Vértice: " << v->getInfo() << endl;
        cout << "Arestas:" << endl;
        for(Edge<int> e: v->getAdj()){
            cout << "[" << i << "] " << e.getOrig()->getInfo() << "  " << e.getDest()->getInfo() << "  " << e.getCapacidade() << "  " << e.getDuracao() << endl;
            i++;
        }
    }
}

class compareCap{ // with < instead of <= we get better results, however on in07.txt we get 0 capacity with < and the path it is equal to <= (need to check this)
    public:
    bool operator()(Vertex<int>* lhs, Vertex<int>* rhs){
        return lhs->getCap() < rhs->getCap();
    }
};


/***************************** 1.1 *******************************/
void Scenario::maxDimensaoGrp(Vertex<int>* orig, Vertex<int>* dest, Graph<int> g){
    vector<Vertex<int>*> vertSet = g.getVertexSet();
    //set capacity of all v to 0 and the path node to nullptr
    g.unweightedShortestPath(orig->getInfo());


    // our queue, based on our function to compare capacities
    priority_queue<Vertex<int>*, vector<Vertex<int>*>, compareCap> heapMax(vertSet.begin(),vertSet.end());

    int i = 0;
    while(!heapMax.empty()){ // enquanto não estiver vazia
        Vertex<int>* v = heapMax.top();
        heapMax.pop();
        i++;

        // adaptação do Algoritmo de Dijkstra
        for(Edge<int> e : v->getAdj()){
            Vertex<int>* destVert = g.findVertex(e.getDest()->getInfo());
            if(min(v->getCap(), e.getCapacidade()) > destVert->getCap()){
                destVert->setCap(min(v->getCap(), e.getCapacidade()));
                destVert->setPath(v);
                
                //increase key part
                //queremos criar uma heap nova ordenada com as novas capacidades
                priority_queue<Vertex<int>*,vector<Vertex<int>*>,compareCap> newHeap(vertSet.begin() + i, vertSet.end());
                heapMax = newHeap;
            }
        }
    }

    // imprime a capacidade máxima do grupo
    cout << endl << "Max capacity of the group is -> " << dest->getCap() << endl;

    // imprime o path
    vector<int> path = g.getPath(orig->getInfo(), dest->getInfo());
    cout << endl << "Path: ";
    for(auto p : path){
        cout << " -> Vertex "  << p;
    }
    cout << endl;
}

/***************************** 1.2 *******************************/
/*
void Scenario::testAndVisit(queue< Vertex<int>*> &q, Edge<int> *e, Vertex<int> *w, double residual) {
    if( ! w->getVisited() && residual > 0 && e->getCapacidade() == 0) {
        w->setVisited(true);
        w->setEdgePath(e);
        q.push(w);
    }
}

bool Scenario::findAugmentationPath(Vertex<int>* orig, Vertex<int>* dest, vector<Vertex<int>*> vertSet) {
    for (Vertex<int>* v : vertSet) {
        v->setVisited(false);
    }

    orig->setVisited(true);
    queue< Vertex <int>* > q;
    q.push(orig);
    while( ! q.empty() && ! dest->getVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, &e, e.getDest(), e.getCapacidade() - e.getFlux());
            
        }
    }

    return dest->getVisited();
}

int Scenario::findMinResidualAlongPath(Vertex<int>* orig, Vertex<int>* dest){
    int f = numeric_limits<int>::max();
    for (auto v = dest; v != orig; ) {
        auto e = v->getEdgePath();
        if (e->getDest() == v) {
            f = min(f, e->getCapacidade() - e->getFlux());
            v = e->getOrig();
        }
        else {
            f = min(f, e->getFlux());
            v = e->getDest();
        }
    }
    return f;
}


void Scenario::augmentFlowAlongPath(Vertex<int>* orig, Vertex<int>* dest, int f) {
    for (auto v = dest; v != orig; ) {
        auto e = v->getEdgePath();
        if (e->getDest() == v) {
            e->setFlux(e->getFlux() + f);
            v = e->getOrig();
        }
    }
}

void Scenario::bellmanFordShortestPath(Vertex<int> *orig, vector<Vertex<int>*> vertSet) {
    for(auto v : vertSet) {
        v->setDist(numeric_limits<int>::max());
    }

    orig->setDist(0);

    for (unsigned i = 1; i < vertSet.size(); i++)
        for (auto v: vertSet) {
            for (auto e : v->getAdj())
                relax(v, e.getDest(), &e, e.getCapacidade() - e.getFlux(), e.getCost());
        }
}

bool Scenario::relax(Vertex<int> *v, Vertex<int> *w, Edge<int> *e, int residual, int cost) {
    if (residual > 0 && v->getDist() + cost < w->getDist()) {
        w->setDist(v->getDist() + cost);
        w->setEdgePath(e);
        return true;
    }
    else
        return false;
}

void Scenario::dijkstraShortestPath(Vertex<int> *orig,  vector<Vertex<int>*> vertSet) {
    for(auto v : vertSet) {
        v->setDist(numeric_limits<int>::max());
    }

    orig->setDist(0);

    MutablePriorityQueue<Vertex<int>> q;

    q.insert(orig);
    
    while( ! q.empty() ) {
        auto v = q.extractMin();
        for (auto e : v->getAdj()) {
            auto oldDist = e.getDest()->getDist();
            if (relax(v, e.getDest(), &e, e.getCapacidade() - e.getFlux(), e.getCost())){
                if (oldDist == numeric_limits<int>::max())
                    q.insert(e.getDest());
                else
                    q.decreaseKey(e.getDest());
            }
        }
    }
}

void Scenario::reduceCosts(vector<Vertex<int>*> *vertSet) {
    for (auto v : *vertSet)
        for (auto e: v->getAdj())
            if (e.getOrig()->getDist() != numeric_limits<int>::max() && e.getDest()->getDist() != numeric_limits<int>::max())
                e.setCost(e.getCost() + e.getOrig()->getDist() - e.getDest()->getDist());
}

void Scenario::maxDimMinTrans(Vertex<int>* orig, Vertex<int>* dest, Graph<int> g, int flow){
    
    
    /* Calculate max dimension                                  
    vector<Vertex<int>*> vertSet = g.getVertexSet();
    //set capacity of all v to 0 and the path node to nullptr
    g.unweightedShortestPath(orig->getInfo());


    // our queue, based on our function to compare capacities
    priority_queue<Vertex<int>*, vector<Vertex<int>*>, compareCap> heapMax(vertSet.begin(),vertSet.end());

    int i = 0;
    while(!heapMax.empty()){ // enquanto não estiver vazia
        Vertex<int>* v = heapMax.top();
        heapMax.pop();
        i++;

        // adaptação do Algoritmo de Dijkstra
        for(Edge<int> e : v->getAdj()){
            Vertex<int>* destVert = g.findVertex(e.getDest()->getInfo());
            if(min(v->getCap(), e.getCapacidade()) > destVert->getCap()){
                destVert->setCap(min(v->getCap(), e.getCapacidade()));
                destVert->setPath(v);
                
                //increase key part
                //queremos criar uma heap nova ordenada com as novas capacidades
                priority_queue<Vertex<int>*,vector<Vertex<int>*>,compareCap> newHeap(vertSet.begin() + i, vertSet.end());
                heapMax = newHeap;
            }
        }
    }

    // imprime a capacidade máxima do grupo
    cout << endl << "Max capacity of the group is -> " << dest->getCap() << endl;

    // imprime o path
    vector<int> path = g.getPath(orig->getInfo(), dest->getInfo());

    cout << "Number of transhipments is ->" << path.size() << endl;
    cout << endl << "Path: ";
    for(auto p : path){
        cout << " -> Vertex "  << p;
    }
    
    cout << endl;

    vertSet = g.getVertexSet();

    for (auto v : vertSet) {
        for (auto e : v->getAdj()) {
            e.setFlux(0);
        }
    }

    int cur_cost = 0;
    int cur_flow = 0;
    int unit_cost = 0;

    bool firstIt = true;
    while (cur_flow < flow) {
        if (firstIt) {
            bellmanFordShortestPath(orig, vertSet);
            firstIt = false;
        }
        else {
            dijkstraShortestPath(orig, vertSet);
        }
        if (dest->getDist() == numeric_limits<int>::max()) {
            break;
        }
        unit_cost += dest->getDist();
        reduceCosts(&vertSet);
        while(cur_flow < flow && findAugmentationPath(orig, dest, vertSet)) {
            int f = min(findMinResidualAlongPath(orig, dest), flow - cur_flow);
            augmentFlowAlongPath(orig, dest, f);
            cur_flow += f;
            cur_cost += f * unit_cost; 
        }
    }

    cout << endl << "Max capacity of the group is -> " << dest->getCap() << endl;
    cout << endl << "Number of transhipments is: -> " << cur_cost << endl;



}*/


/***************************** 2 *******************************/
/*** rede residual ***/
Graph<int> Scenario::rede_residual(Graph<int> * g) {
    Graph<int> residualGrid;

    for(Vertex<int> * v: (*g).getVertexSet()){
        residualGrid.addVertex(v->getInfo());
    }
    for(Vertex<int> * v: (*g).getVertexSet()){
        for(Edge<int> e: v->getAdj()){
            if((e.getCapacidade() - e.getFlux()) > 0){
                residualGrid.addEdge(v->getInfo(), e.getDest()->getInfo(), e.getCapacidade(), e.getDuracao(), e.getCapacidade() - e.getFlux());
            }
        }
    }

    for(Vertex<int> * v: (*g).getVertexSet()){
        for(Edge<int> e: v->getAdj()){
            if(e.getFlux() > 0){
                residualGrid.addEdge(e.getDest()->getInfo(), v->getInfo(), e.getCapacidade(), e.getDuracao(), e.getFlux());
            }
        }
    }

    return residualGrid;
}

/*** ford_fulkerson_algorithm to Scenario 2 ***/
void Scenario::ford_fulkerson_algorithm(Graph<int> *rede, vector<int> *path, Vertex<int> *orig, Vertex<int> *dest, int *resCap, Graph<int> * g) {
    for(int i = 0; i < (*path).size() - 1; i++){
        for(Edge<int> e: (*rede).findVertex((*path)[i])->getAdj()){
            if(e.getDest()->getInfo() == (*rede).findVertex((*path)[i+1])->getInfo()){
                *resCap = min(e.getResidCap(), *resCap);
            }
        }
    }

    for(int i = 0; i < (*path).size() - 1; i++){ // setting the newflux in the correct edge
        auto v = (*g).findVertex((*path)[i]);
        for(int j = 0; j < v->getAdj().size(); j++){
            if(v->adj[j].getDest()->getInfo() == (*g).findVertex((*path)[i+1])->getInfo()){
                v->adj[j].setFlux((*resCap) + v->adj[j].getFlux());
            }
        }
    }

    *rede = rede_residual(g);
    (*rede).unweightedShortestPath(orig->getInfo());
    *path = (*rede).getPath(orig->getInfo(), dest->getInfo());
}

/*** imprime a capacidade máxima do grupo ***/
void imprimeCapacMax(Vertex<int> * orig){
    int maxFlux = 0;
    for(Edge<int> e: orig->getAdj()){
        maxFlux += e.getFlux();
    }

    cout << endl << "Max capacity of the group is -> " << maxFlux << endl;
}


/***************************** 2.1 *******************************/
void Scenario::determinatePath(Vertex<int> *orig, Vertex<int> *dest, int dimensao, Graph<int> * g) {
    int resCap = INT32_MAX;
    Graph<int> rede = rede_residual(g);
    rede.unweightedShortestPath(orig->getInfo());
    vector<int> path = rede.getPath(orig->getInfo(), dest->getInfo());

    while(dimensao != 0){
        if(path.empty()){
            cout << endl << "Dimenssion was too big!!!" << endl << "After this, you must reset the testing by pressing 'n' on the following questions!" << endl;
            return;
        }
        ford_fulkerson_algorithm(&rede, &path, orig, dest, &resCap, g);

        dimensao -= resCap;
    }
}


/***************************** 2.2 *******************************/
void Scenario::increaseGrpSize(Vertex<int> *orig, Vertex<int> *dest, int incre, Graph<int> * g) {
    int resCap = INT32_MAX, initFlux = 0;

    for(Edge<int> e: orig->getAdj()){
        initFlux += e.getFlux();
    }
    int newFlux = initFlux;

    Graph<int> rede = rede_residual(g);
    rede.unweightedShortestPath(orig->getInfo());
    vector<int> path = rede.getPath(orig->getInfo(), dest->getInfo());

    while(newFlux - initFlux < incre){
        if(path.empty()){
            cout << endl << "Increment too big!!!" << endl << "After this, you must reset the testing by pressing 'n' on the following questions!" << endl;
            return;
        }
        ford_fulkerson_algorithm(&rede, &path, orig, dest, &resCap, g);

        newFlux = 0;
        for(Edge<int> e: orig->getAdj()){
            newFlux += e.getFlux();
        }
    }

    cout << endl << "Diferença é:  " << newFlux - initFlux << endl;

    imprimeCapacMax(orig);
}


/***************************** 2.3 *******************************/
void Scenario::maxDim_determinatePath(Vertex<int> *orig, Vertex<int> *dest, Graph<int> * g) {
    int resCap = INT32_MAX;
    Graph<int> rede = rede_residual(g);
    rede.unweightedShortestPath(orig->getInfo());
    vector<int> path = rede.getPath(orig->getInfo(), dest->getInfo());
    Vertex<int> * last_vert = rede.findVertex(dest->getInfo());

    while(last_vert->getVisited()){
        ford_fulkerson_algorithm(&rede, &path, orig, dest, &resCap, g);

        last_vert = rede.findVertex(dest->getInfo());
    }

    imprimeCapacMax(orig);
}


/***************************** 2.4 *******************************/
void Scenario::timeOfReunion(Vertex<int>* dest, Graph<int> *g){
    int reunion_time = printPath(*g, dest);

    cout << endl << "O grupo irá reunir-se novamente no final após " << reunion_time << " min" << endl;
}


/*** another aproach to 2.4 ***/
int Scenario::shortestPathAux(Graph<int> *g){
    int minDur = -1;
    for(auto node : g->getVertexSet()){
        node->setES(0);
        node->setPath(nullptr);
        node->setDegree(0);
        for(auto edge : node->adj){
            edge.getDest()->setDegree(edge.getDest()->getDegree() + 1);
        }
    }
    queue<Vertex<int>*> q;
    for(auto node : g->getVertexSet()){
        if(node->getDegree() == 0){
            q.push(node);
        }
    }

    while(!q.empty()){
        auto node = q.front();
        q.pop();
        if(minDur < node->getES()){
            minDur = node->getES();
        }
        for(auto edge : node->getAdj()){
            if(edge.getDest()->getES() < node->getES() + edge.getCapacidade()){
                edge.getDest()->setES(node->getES() + edge.getCapacidade());
                edge.getDest()->setPath(node);
            }

            edge.getDest()->setDegree(edge.getDest()->getDegree() - 1);

            if(edge.getDest()->getDegree() == 0)
                q.push(edge.getDest());
        }

    }
    return minDur;
}
/*** ***/

/***************************** 2.5 *******************************/
void Scenario::maxTime(Vertex<int>* orig, Vertex<int>* dest, Graph<int>* g){
    shortestPathAux(g);
    vector<int> waitingTime(g->getVertexSet().size() + 1,0);
    for(auto node : g->getVertexSet()){
        for(auto edge : node->getAdj()){
            int maxDur = edge.getDest()->getES() - edge.getOrig()->getES() - edge.getDuracao();
            if(waitingTime[edge.getDest()->getInfo()] < maxDur)
                waitingTime[edge.getDest()->getInfo()] = maxDur;
        }
    }

    int maxWait = -9999;
    for(auto p : waitingTime){
        if(p > maxWait){
            maxWait = p;
        }
    }

    cout << "maxWait : " << maxWait << endl;
    cout << "in the following nodes : " << endl << " - ";
    for(int i = 0; i < waitingTime.size(); i++){
        if(waitingTime[i] == maxWait){
            cout << i << " - ";
        }
    }
    cout << endl;
}

/*** print the path ***/
void Scenario::restOfThePath(Vertex<int> *v, Vertex<int> *dest, int * pathDura) {
    if(v->getInfo() == dest->getInfo()){
        cout << "   Duração: " << (*pathDura) << endl;
        return;
    }

    for(auto e: v->getAdj()){
        if(e.getFlux() > 0){
            cout << " -> Vertex " << e.getDest()->getInfo();
            (*pathDura) += e.getDuracao();
            e.setFlux(0);
            restOfThePath(e.getDest(), dest, pathDura);
            break;
        }
    }
}

int Scenario::printPath(Graph<int> g, Vertex<int> *dest) {
    Vertex<int> *orig = g.findVertex(1);

    int sumFlux = 0, pathDura = 0, longestPath = 0;
    for(auto e: orig->getAdj()){
        sumFlux += e.getFlux();
    }

    while(sumFlux > 0){
        for(auto e: orig->getAdj()){
            if(e.getFlux() != 0){
                cout << endl << e.getFlux() << " pessoas foram por este caminho: " << endl;
                cout << "-> Vertex " << orig->getInfo() << " -> Vertex " << e.getDest()->getInfo();
                sumFlux -= e.getFlux();
                pathDura += e.getDuracao();
                e.setFlux(0);
                restOfThePath(e.getDest(), dest, &pathDura);
            }
            if(longestPath < pathDura){
                longestPath = pathDura;
            }
            pathDura = 0;
        }
    }

    return longestPath;
}