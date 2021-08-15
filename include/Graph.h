#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "../include/Tree.h"
#include "../include/Graph.h"

class Graph{
public:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);
    //getters
    std::vector<std::vector<int>> getEdges();
    std::vector<int> getInfected();
    std::vector<int> getNeighbors(int node);
    //methods
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void occupyNode(int nodeInd);
    bool isOccupied(int nodeInd);
    void generateBFS(Tree &BFSTree, Session &session);
    void disconnectNode(int node);
    int numOfInfected();
    //fields
private:
    std::vector<std::vector<int>> edges;
    std::vector <int> infected;
    std::vector<int> occupied;
};

#endif
