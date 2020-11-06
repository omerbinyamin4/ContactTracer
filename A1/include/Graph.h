#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void setMatrix(std::vector<std::vector<int>>);
private:
    std::vector<std::vector<int>> edges;
};

#endif
