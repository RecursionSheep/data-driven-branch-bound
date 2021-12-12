#include "treenode.h"

Node::Node(MilpInstance *_milp) {
    milp = _milp;
    for (int i = 0; i < milp->intVarCnt; i ++) {
        lower.push_back(milp->lower[milp->intVar[i]]);
        upper.push_back(milp->upper[milp->intVar[i]]);
    }
}
Node::~Node() {}
void Node::computeDualCost() {
    
}
