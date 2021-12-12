#pragma once

#include <iostream>
#include <vector>

const int inf = 1000000000;

const bool MIN = true;
const bool MAX = false;

const int LE = -1;
const int EQ = 0;
const int GE = 1;

class Constraint {
public:
    std::vector<std::pair<int, double>> w;
    int rel = EQ;
    double b = 0.;
    
    Constraint(std::vector<std::pair<int, double>> _w, int _rel, double _b): w(_w) {
        rel = _rel; b = _b;
    }
};

class MilpInstance {
public:
    int varCnt, constrCnt, intVarCnt;
    bool minOrMax;
    std::vector<double> cost;
    std::vector<Constraint> constr;
    std::vector<int> lower, upper;
    std::vector<int> intVar;
    std::vector<bool> isIntVar;
    MilpInstance();
    MilpInstance(int varCnt);
    ~MilpInstance();
    
    void setVarCnt(int varCnt);
    void setTarget(std::vector<std::pair<int, double>> cost, bool minOrMax = MIN);
    void addConstr(std::vector<std::pair<int, double>> w, int rel = EQ, double b = 0.);
    void setVarBound(int var, int lower = -inf, int upper = inf);
    void addIntVar(int var);
    friend std::ostream& operator <<(std::ostream& out, const MilpInstance &milp);
};
