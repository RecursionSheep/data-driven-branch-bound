#pragma once

#include <iostream>
#include <vector>

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
    int varCnt, constrCnt;
    bool minOrMax;
    std::vector<double> cost;
    std::vector<Constraint> constr;
    std::vector<double> lower, upper;
    std::vector<int> intVar;
public:
    MilpInstance();
    MilpInstance(int varCnt);
    ~MilpInstance();
    
    void setVarCnt(int varCnt);
    void setTarget(std::vector<std::pair<int, double>> cost, bool minOrMax = MIN);
    void addConstr(std::vector<std::pair<int, double>> w, int rel = EQ, double b = 0.);
    void setVarBound(int var, double lower = -1e10, double upper = 1e10);
    void addIntVar(int var);
    friend std::ostream& operator <<(std::ostream& out, const MilpInstance &milp);
};
