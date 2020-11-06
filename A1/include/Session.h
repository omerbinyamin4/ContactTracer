#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "json.hpp"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    
    void simulate();
    void loadContent(const std::string &configFilePath);
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
}

#endif
