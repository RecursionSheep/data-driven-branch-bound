#pragma once

#include "milp.h"

class Node {
public:
    std::vector<int> upper, lower;
    std::vector<double> relaxedSol;
    double dualCost, priority;
    int branchVar;
    
    MilpInstance *milp;
    
    Node(MilpInstance *milp);
    ~Node();
    void computeDualCost();
};
