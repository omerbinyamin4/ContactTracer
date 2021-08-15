
#include "../include/Graph.h"
#include <vector>
#include <queue>

//default constructor
Graph::Graph():edges(), infected(), occupied(){}
//constructor
Graph::Graph(std::vector<std::vector<int>> matrix): edges(matrix), infected(), occupied(){
    infected.resize(matrix.size()); //initialize all nodes as 'not infected'
    occupied.resize(matrix.size()); //initialize all nodes as 'not occupied'
}
//----------------------getters--------------------------
std::vector<std::vector<int>> Graph::getEdges(){return edges;}
std::vector<int> Graph::getInfected(){return infected;}
std::vector<int> Graph::getNeighbors(int node){
    std::vector<int> neighbors;
    for (unsigned i=0; i<edges[node].size(); i++){
        if (edges[node][i]==1)
            neighbors.push_back(i);
    }
    return neighbors;
}
//----------------------methods--------------------------
void Graph::infectNode(int nodeInd){infected[nodeInd] = 1;} //turn the node status to 'infected'
bool Graph::isInfected(int nodeInd){return (infected[nodeInd] == 1);}
void Graph::occupyNode(int nodeInd) {occupied[nodeInd] = 1;} //turn the node status to 'occupied'
bool Graph::isOccupied(int nodeInd){return (occupied[nodeInd] == 1);}
void Graph::generateBFS(Tree &BFSTree, Session &session){
    std::vector<int> usedNodes;
    std::queue <Tree*> nodeQueue;
    usedNodes.resize(edges.size());
    usedNodes[BFSTree.getNode()]=1;
    nodeQueue.push(&BFSTree);

    while (!nodeQueue.empty()){
        int currNode = nodeQueue.front()->getNode();
        for (unsigned i=0; i<edges[currNode].size(); i++){
            if ((edges[currNode][i] == 1) & (usedNodes[i] == 0)){
                Tree *newChild = Tree::createTree(session, i);
                nodeQueue.front()->addChild(*newChild);
                nodeQueue.push(nodeQueue.front()->getChildren().back());
                usedNodes[i] = 1;
                if (newChild){
                    delete newChild;
                    newChild = nullptr;
                }
            }
        }
        nodeQueue.pop();
    }

}
void Graph::disconnectNode(int node){

    for (unsigned i=0; i<edges[node].size(); i++){
        edges[node][i]=0;
    }
    for (unsigned i=0; i<edges.size(); i++){
        edges[i][node]=0;
    }
}
int Graph::numOfInfected() {
    int counter=0;
    for (int node : infected){
        if (node==1){counter++;}
    }
    return counter;
}


