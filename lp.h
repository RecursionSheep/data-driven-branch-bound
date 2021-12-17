#pragma once

#include "milp.h"

#include <vector>
#include "gurobi_c++.h"

class LPSolver {
public:
    int varCnt, constrCnt;
    GRBEnv *env = nullptr;
    GRBModel *model = nullptr;
    GRBLinExpr obj;
    std::vector<GRBVar> var;
    LPSolver();
    ~LPSolver();
    void init(int varCnt);
    void addVar(int id, double cost, int lower, int upper);
    void addConstr(const Constraint &constr);
    void modifyBound(int id, int lower, int upper);
    void modifyInt(int id);
    void setObj();
    void solve();
    bool isInfeasible();
    bool isUnbounded();
    double getObj();
    double getVar(int id);
};
