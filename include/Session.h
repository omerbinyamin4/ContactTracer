#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include "json.hpp"


class Agent;
class Virus;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
//rule of 5
    virtual ~Session();
    Session(const Session &other);
    Session(Session &&other);
    const Session& operator=(const Session &other);
    const Session& operator=(Session &&other);
//getters
    TreeType getTreeType() const;
    Graph& getGraph() ;
    int getCycle() const;
//setters
    void setGraph(const Graph& graph);
//methods
    void move(const Session &other);
    void copy(const Session &other);
    void clear();
    void simulate();
    void loadSession(const std::string &configFilePath);
    void addVirus(const Virus& virus);
    void enqueueInfected(int node);
    int dequeueInfected();
    bool terminate();
    void output();
private:
    //fields
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infectedNodes;
    int cycle;
    unsigned numOfCT;
};

#endif
