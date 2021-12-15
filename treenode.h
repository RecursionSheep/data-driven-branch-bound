#pragma once

#include "milp.h"
#include "lp.h"

class Node {
public:
    std::vector<int> upper, lower;
    std::vector<std::vector<double>> score; // score[i][j]: the j-th score of the i-th integer variable
    std::vector<double> relaxedSol;
    double dualCost, priority;
    bool infeasible, unbounded;
    int branchVar;
    
    MilpInstance *milp;
    
    static int branchLeftBound(double x);
    static int branchRightBound(double x);
    static double fractional(double x);
    
    Node(MilpInstance *milp);
    Node(Node *fa);
    ~Node();
    void solveRelaxed(LPSolver *solver);
    bool checkInt();
    void computeScore(LPSolver *solver);
    void chooseBranchVar();
};

struct cmp {
    bool operator ()(const Node *a, const Node *b) {
        return a->priority > b->priority;
    }
};
