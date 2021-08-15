#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
    public:
        Tree(int rootLabel);
    //rule of 5
        virtual ~Tree();
        Tree(const Tree &other);
        const Tree& operator=(const Tree &other);
        Tree(Tree &&other);
        const Tree& operator=(Tree &&other);
    //getters
        int getNode() const;
        std::vector<Tree*> getChildren() const;
    //methods
        void move(const Tree &other);
        void copy(const Tree &other);
        void clear();
        void addChild(const Tree& child);
        static Tree* createTree(const Session& session, int rootLabel);
        bool hasChild();
        virtual int traceTree()=0;
        virtual Tree* clone() const=0;
    //fields
        protected:
            std::vector<Tree*> children;
        private:
            int node;
    };

class CycleTree: public Tree{
    public:
        CycleTree(int rootLabel, int currCycle);
        virtual int traceTree();
        virtual Tree* clone() const;
    private:
        int currCycle;
    };

class MaxRankTree: public Tree{
    public:
        MaxRankTree(int rootLabel);
        virtual int traceTree();
        virtual Tree* clone() const;
};

class RootTree: public Tree{
    public:
        RootTree(int rootLabel);
        virtual int traceTree();
        virtual Tree* clone() const;
};

#endif
