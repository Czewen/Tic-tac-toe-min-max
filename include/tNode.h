#ifndef TNODE_H
#define TNODE_H
#include <list>

class tNode
{
    public:
        tNode parent;
        GameBoard board;
        std::list<tNode> children;
        tNode();
        virtual ~tNode();
        void setParent(tNode node);
        void insertChild(tNode node);
        GameBoard getBoard():
    protected:
    private:
};

tNode::tNode(){
    board = GameBoard();
}


tNode::~tNode()
{
    //dtor
}

void tNode::setParent(tNode node){
    parent = node;
}

void tNode::insertChild(tNode node){
    children.push_back(node);
}

GameBoard tNode::getBoard(){
    return board;
}
#endif // TNODE_H
