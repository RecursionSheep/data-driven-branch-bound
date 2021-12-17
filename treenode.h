#pragma once

#include "milp.h"
#include "lp.h"

class Node {
public:
    static double parameter;
    std::vector<int> upper, lower;
    std::vector<std::vector<double>> score; // score[i][j]: the j-th score of the i-th integer variable
    std::vector<double> relaxedSol, roundingSol;
    double dualCost, priority, roundingCost;
    bool infeasible, unbounded;
    int branchVar;
    
    MilpInstance *milp;
    
    static int branchLeftBound(double x, int lower, int upper);
    static int branchRightBound(double x, int lower, int upper);
    static double fractional(double x);
    
    Node(MilpInstance *milp);
    Node(Node *fa);
    ~Node();
    void solveRelaxed(LPSolver *solver);
    bool rounding(LPSolver *solver);
    bool checkInt();
    void computeScore(LPSolver *solver);
    void outputRelaxedSol();
    void chooseBranchVar();
};

struct cmp {
    bool operator ()(const Node *a, const Node *b) {
        return a->priority > b->priority;
    }
};
