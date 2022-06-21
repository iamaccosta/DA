#ifndef DA_P2_SCENARIOS_H
#define DA_P2_SCENARIOS_H

#include "Graph.h"

class Scenario{
private:
    
public:
    /**
     *
     */
    Scenario();

    /**
     *
     * @param input
     * @param g
     */
    Scenario(const string& input, Graph<int> * g);

    /**
     *
     * @param g
     */
    void printGraph(Graph<int> g);

    /*** 1 - Grupos não se separam ***/
    /**
     * @brief Determines the max dimension of a group and indicates the path the group took to go from orig to dest
     *
     * @param orig vertex of origin
     * @param dest vertex of destination
     * @param g graph to be modified
     */
     void maxDimensaoGrp(Vertex<int>* orig, Vertex<int>* dest, Graph<int> g);

    /** 1.2 **/
    /**
     * @brief Maximizar a dimensão do grupo e minimizar os transbordos (mostrando para as duas, as soluções ótimas)
     * 
     */


    /*** 2 - Grupos podem-se separar ***/
    /**
     * @brief creates a residual graph that holds the edges (paths/vehicles) that can take people still
     *
     * @param g
     * @return residual graph
     */
    Graph<int> rede_residual(Graph<int> * g);

    /**
     * @brief receives a path and checks the minimum flow possible to go from orig to dest, updates the flow on the graph and recreates the residual graph aswell as the path (checks if till has another path)
     *
     * @param rede reference to the residual graph
     * @param path reference to the path
     * @param orig vertex of origin
     * @param dest vertex of destination
     * @param resCap difference between capacity and flow
     * @param g graph to be updated
     */
    void ford_fulkerson_algorithm(Graph<int> *rede, vector<int> *path, Vertex<int> *orig, Vertex<int> *dest, int *resCap, Graph<int> * g);


    /** 2.1 **/
    /**
     * @brief determinates the path for a group with dimension "dimensao"
     *
     * @param orig vertex of origin
     * @param dest vertex of destination
     * @param dimensao dimension
     * @param g graph to be updated
     */
     void determinatePath(Vertex<int> * orig, Vertex<int> * dest, int dimensao, Graph<int> * g);

    /** 2.2 **/
    /**
     * @brief given a graph with flow, increases the flow by an increment "incre"
     *
     * @param orig vertex of origin
     * @param dest vertex of destination
     * @param incre increment
     * @param g graph to be updated
     */
     void increaseGrpSize(Vertex<int> * orig, Vertex<int> * dest, int incre, Graph<int> * g);

    /** 2.3 **/
    /**
     * @brief determinates the max flow from origin to destination
     *
     * @param orig vertex of origin
     * @param dest vertex of destination
     * @param g graph to be updated
     */
     void maxDim_determinatePath(Vertex<int> * orig, Vertex<int> * dest, Graph<int> * g);

    /** 2.4 **/
    /**
     * @brief prints the longest path in terms of duration
     *
     * @param dest vertex of destination
     * @param g graph
     */
    void timeOfReunion(Vertex<int>* dest, Graph<int> *g);

    /**
     *
     * @param g
     * @return
     */
    int shortestPathAux(Graph<int> *g);

    /** 2.5 **/
    /**
     * @brief
     * 
     */
    void maxTime(Vertex<int>* orig, Vertex<int>* dest, Graph<int>* g);

    /**
     * @brief prints the path of the flow of the graph
     *
     * @param g graph
     * @param dest vertex of destination
     * @return longest duration
     */
    int printPath(Graph<int> g, Vertex<int> *dest);

    /**
     * @brief recursive function that helps printing the path
     *
     * @param v current vertex of path
     * @param dest vertex of destination
     */
    void restOfThePath(Vertex<int> *v, Vertex<int> *dest, int * pathFlux);
};

#endif //DA_P2_SCENARIOS_H
