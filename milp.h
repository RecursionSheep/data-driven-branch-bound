#pragma once

#include <iostream>
#include <vector>

const int inf = 1000000000;
const double dinf = 1e10;
const double eps = 1e-6;

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
    std::vector<int> lower, upper; // lower/upper[i]: the bound of x_{intvar[i]}
    std::vector<int> intVar; // record all indices of integer variables
    std::vector<bool> isIntVar; // isIntVar[i]: if x_i is an integer variable
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
