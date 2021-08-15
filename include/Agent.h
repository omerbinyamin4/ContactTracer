#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "../include/Session.h"

class Agent{
public:
    Agent();
    virtual void act(Session& session)=0;
    virtual Agent* clone() const=0;
    virtual ~Agent();
};
class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session& session);
    virtual Agent* clone() const;
    virtual ~ContactTracer();

};
class Virus: public Agent{
public:
    Virus(int nodeInd);
    int getNodeInd() const;
    virtual void act(Session& session);
    virtual Agent* clone() const;
    virtual ~Virus();

private:
    const int nodeInd;
};

#endif