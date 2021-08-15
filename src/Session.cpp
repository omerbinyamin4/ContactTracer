
#include "../include/Session.h"
#include "../include/Agent.h"
#include <fstream>
#include <vector>
#include <string>

//constructor
Session::Session(const std::string &configPath): g(), treeType(), agents(),infectedNodes(), cycle(0), numOfCT(0){
    Session::loadSession(configPath);
}

//--------------------------rule of 5-------------------------------
//destructor
Session::~Session(){
    this->clear();
}
//copy- constructor
Session::Session(const Session &other):g(), treeType(), agents(),infectedNodes(), cycle(), numOfCT(){
    this->copy(other);
}
//copy assignment operator
const Session& Session::operator=(const Session &other){
    this->clear();
    this->copy(other);
    return *this;
}
//move constructor
Session::Session(Session &&other):g(), treeType(),agents(),infectedNodes(), cycle(), numOfCT(){
    this->move(other);
    other.agents.resize(0);
}
//move assignment operator
const Session& Session::operator=(Session &&other){
    if (this != &other) {
        this->clear();
        this->move(other);
        other.agents.resize(0);
    }
    return *this;
}
//help methods
void Session::move(const Session &other){
    g = other.g;
    treeType = other.treeType;
    cycle = other.cycle;
    numOfCT = other.numOfCT;
    infectedNodes = other.infectedNodes;
    for (unsigned i=0; i<other.agents.size(); i++){ //'steal' other agents vector
        agents.push_back(other.agents[i]);
    }
}
void Session::copy(const Session &other){
    g = other.g;
    treeType = other.treeType;
    cycle = other.cycle;
    numOfCT = other.numOfCT;
    infectedNodes = other.infectedNodes;
    for (auto agent : other.agents) {
        agents.push_back(agent->clone()); //copy all other agents vector
    }
}
void Session::clear(){
    for (auto & agent : agents){
        if (agent){
            delete agent;
            agent = nullptr;
        }
    }
    agents.resize(0);
}

//--------------------------getters-------------------------------
//const Graph Session::getGraph() const{return g;}
Graph& Session::getGraph() {return g;}

TreeType Session::getTreeType() const {return treeType;}

int Session::getCycle() const {return cycle;}

//--------------------------setters-------------------------------
void Session::setGraph(const Graph &graph) {g = graph;}
//--------------------------methods-------------------------------

void Session::simulate(){
    while (!(this->terminate())){
        int currNumOfAgent = agents.size(); //determine the number of agent who will act on the coming session
        for (int i=0; i<currNumOfAgent; i++){
            agents[i]->act(*this);
        }
    cycle++;
    }
    this->output();

}

void Session::loadSession(const std::string &configFilePath) {
    std::fstream ifs(configFilePath);
    nlohmann::json buffer;
    ifs>>buffer;
    nlohmann::json input_agents = buffer["agents"];
    nlohmann::json input_graph = buffer["graph"];
    nlohmann::json input_treeType = buffer["tree"];

    //set g field
    //creat graph matrix out of json file
    std::vector<std::vector<int>> matrix;
    for(auto &x : input_graph.items()){
        nlohmann::json row = x.value();
        std::vector<int> currRow;
        for(auto &y : row.items()){
            int edge = y.value();
            currRow.push_back(edge);
        }
        matrix.push_back(currRow);
    }
    //construct new Graph out the matrix and assign it to the field g
    g = Graph(matrix);

    //add all agents to 'agents' field
    for (auto &item : input_agents.items()){
        nlohmann::json agent = item.value();
        std::string agentType = agent[0];
        int nodeIn = agent[1];
        if (agentType == "V"){
            Virus *newVirus = new Virus(nodeIn);
            addVirus(*newVirus);
            if (newVirus){delete newVirus;}
        }
        else{
            Agent *newContactTracer = new ContactTracer();
            agents.push_back(newContactTracer->clone());
            if (newContactTracer){delete newContactTracer;}
            numOfCT++;
        }
    }
    //set treeType field
    if (input_treeType=="M")
        treeType = MaxRank;
    else if(input_treeType=="C")
        treeType = Cycle;
    else
        treeType = Root;
}

void Session::addVirus(const Virus &virus) {
    agents.push_back(virus.clone());
    g.occupyNode(virus.getNodeInd()); //indicates the node is now 'virus- hosting'
}

int Session::dequeueInfected() {
    int first= -1;
    if (!infectedNodes.empty()){ first = infectedNodes.front(); infectedNodes.pop();}
    return first; //if empty, returns -1
}

void Session::enqueueInfected(int node) {
    infectedNodes.push(node);
}

bool Session::terminate() {
    unsigned numOfInfected1 = agents.size()-numOfCT;
    unsigned numOfInfected2 = g.numOfInfected();
    return (numOfInfected1 == numOfInfected2);
}

void Session::output(){
    std::vector<std::vector<int>> outputGraph = g.getEdges();
    std::vector<int> outputInfectedNodes;
    for (unsigned i=0; i<(g.getInfected()).size(); i++){
        if (g.getInfected()[i]==1){outputInfectedNodes.push_back(i);}
    }
    nlohmann::json output;
    output["graph"] = outputGraph;
    output["infected"] = outputInfectedNodes;
    std::ofstream o("./output.json");
    o<<output;
}