
#include "../include/Tree.h"
#include "../include/Session.h"

//------------------------Tree---------------------------
//constructor
Tree::Tree(int root):children(),node(root){}
//---------------------rule of 5-------------------------
//destructor
Tree::~Tree(){this->clear();}
//copy- constructor
Tree::Tree(const Tree &other):children(), node(){this->copy(other);}
//copy assignment operator
const Tree& Tree::operator=(const Tree &other){
    this->clear();
    this->copy(other);
    return *this;
}
//move constructor
Tree::Tree(Tree &&other):children(), node(){
    this->move(other);
    other.children.resize(0);
}
//move assignment operator
const Tree& Tree::operator=(Tree &&other){
    if (this != &other) {
        this->clear();
        this->move(other);

        other.children.resize(0);
    }
    return *this;
}
//help methods
void Tree::move(const Tree &other){
    node = other.node;
    for (unsigned i=0; i<other.children.size(); i++){
        children.push_back(other.children[i]);
    }

}
void Tree::copy(const Tree &other){
    node = other.node;
    for (auto child:other.children){
        children.push_back(child->clone());
    }
}
void Tree::clear(){
    for (auto &child : children){
        if (child){
            delete child;
            child = nullptr;
        }
    }
    children.resize(0);
}
//----------------------getters--------------------------
int Tree::getNode() const {return this->node;}
std::vector<Tree*> Tree::getChildren() const {
    return children;
}
//----------------------methods--------------------------
void Tree::addChild(const Tree& child){
    children.push_back(child.clone());
}

Tree* Tree::createTree(const Session& session, int rootLabel){
    TreeType treeType = session.getTreeType();
    switch(treeType) {
        case (Cycle):
            return new CycleTree(rootLabel, session.getCycle());
        case (MaxRank):
            return new MaxRankTree(rootLabel);
        case (Root):
            return new RootTree(rootLabel);
    }
	return nullptr;
}

bool Tree::hasChild() {return !this->children.empty();}

//------------------------CycleTree---------------------------
//constructor
CycleTree::CycleTree(int root, int cycle): Tree::Tree(root), currCycle(cycle){}
//methods
int CycleTree::traceTree(){
    unsigned counter = this->currCycle;
    Tree *currTree = this;
    while ((counter>0) & (currTree->hasChild())){ //goes down-left through the tree branches (if possible) "cycle" number of times.
        currTree = (currTree->getChildren()[0]); //casting Tree->CycleTree
        counter--;
    }
    return currTree->getNode();
}

Tree* CycleTree::clone() const {return new CycleTree(*this);}
//-----------------------MaxRankTree--------------------------
//constructor
MaxRankTree::MaxRankTree(int root): Tree::Tree(root){}
//methods
int MaxRankTree::traceTree(){
    std::queue<Tree*> nodes;
    unsigned maxRank=this->children.size(); //initialize the max rank to the root's rank.
    Tree *output = this; //consider the root as the max- rank node.
    nodes.push(this);
    while (!nodes.empty()){
        Tree *poped = nodes.front();
        nodes.pop();
        if (poped != output && poped->getChildren().size() > maxRank){ //find nodes with higher rank
            maxRank = poped->getChildren().size();
            output = poped;
        }
        for (auto &child:poped->getChildren()){ //inserts all children to queue, so their rank will be checked next
            nodes.push(child);
        }
    }
    return output->getNode();
}
Tree* MaxRankTree::clone() const {return new MaxRankTree(*this);}
//-------------------------RootTree---------------------------
//constructor
RootTree::RootTree(int root): Tree::Tree(root){}
//methods
int RootTree::traceTree(){return this->getNode();}
Tree* RootTree::clone() const {return new RootTree(*this);}
