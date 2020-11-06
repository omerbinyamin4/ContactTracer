//
// Created by spl211 on 03/11/2020.
//

#include "../include/Session.h"
#include <iostream>
//#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>

//constructor
Session::Session(const std::string &configPath): g(), treeType(), agents(){
    loadContent(configPath);
}
//copy- constructor
//move copy constructor
//copy assignment operator
//move assignment operator
//destructor

//methods
void Session::simulate(){

}

// help function
void Session::loadContent(const std::string &configFilePath) {
    // config the jason parser
    std::fstream ifs(configFilePath);
    nlohmann::json buffer = nlohmann::json::parse(ifs);
    nlohmann::json agents = buffer["agents"];
    nlohmann::json graph = buffer["graph"];
    nlohmann::json treeType = buffer["tree"];

    //add all agents to 'agents' field
    for (auto &x : agents.items()){
        nlohmann::json agent = x.value();
        std::string agentType = agent[0];
        int nodeIn = agent[0];
        if (agentType == "V"){
            Agent.Virus *newVirus = new Agent.Virus(nodeIn, sess);
            this->agents.push_back(newVirus);
        }
        else{
            Agent *newContactTracer = new Agent(sess);
            this->agents.push_back(newContactTracer); //??
        }
    }
    //set treeType field
    if (treeType[0]=="M")
        treeType = MaxRank;
    else if(treeType[0]=="C")
        treeType = Cycle;
    else
        treeType = Root;

    //set g field
    //creat graph matrix out of json file
    std::vector<std::vector<int>> matrix;
    int rowCount = 0;
    int columnCount = 0;
    for(auto &x : graph.items()){
        nlohmann::json row = x.value();
        for(auto &y : row.items()){
            int edge = y.value();
            matrix[rowCount][columnCount] = edge;
            columnCount++;
        }
        rowCount++;
        //construct new Graph out the matrix and assign it to the field g
        Graph *toAdd = new Graph(matrix);
        g = *toAdd;
    }

}
