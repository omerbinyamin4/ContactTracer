
#include "../include/Agent.h"
//----------------------Agents------------------------
//constructor
Agent::Agent()=default;
//destructor
Agent::~Agent() =default;
//----------------------ContactTracer------------------------
//constructor
ContactTracer::ContactTracer():Agent(){}
//destructor
ContactTracer::~ContactTracer()= default;
//methods
void ContactTracer::act(Session& session){
    int root = session.dequeueInfected();
    if (root != -1) {
        Tree *BFSTree = Tree::createTree(session, root);
        Graph currGraph = session.getGraph();
        currGraph.generateBFS(*BFSTree, session);
        int toDisconnect = BFSTree->traceTree();
        session.getGraph().disconnectNode(toDisconnect);
        delete BFSTree;
    }
}
Agent* ContactTracer::clone() const{return new ContactTracer(*this);}
//-------------------------Virus-----------------------------
//constructor
Virus::Virus(int nodeInd):Agent::Agent(), nodeInd(nodeInd){}
//destructor
Virus::~Virus()= default;
//-------------------------getters-----------------------------
int Virus::getNodeInd() const {return nodeInd;}
//-------------------------methods-----------------------------
void Virus::act(Session &session) {
    if (!(session.getGraph().isInfected(this->nodeInd))){ //checks is host node is infected
        session.getGraph().infectNode(this->nodeInd);//infects host node
        session.enqueueInfected(this->nodeInd);
    }
    std::vector<int> neighbors = session.getGraph().getNeighbors(this->nodeInd);
    for (int neighbor : neighbors){ //finds the first non "virus- hosting" neighbor, and spreads there
        if (!session.getGraph().isOccupied(neighbor)) {
            session.addVirus(Virus(neighbor));
            break;
        }
    }
}
Agent* Virus::clone() const{return new Virus(*this);}
