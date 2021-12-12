#include "milp.h"

using namespace std;

MilpInstance::MilpInstance() {}
MilpInstance::MilpInstance(int _varCnt) { setVarCnt(_varCnt); }
MilpInstance::~MilpInstance() {}

void MilpInstance::setVarCnt(int _varCnt) {
    varCnt = _varCnt; intVarCnt = 0;
    cost.resize(varCnt);
    lower.resize(varCnt);
    upper.resize(varCnt);
    isIntVar.resize(varCnt);
    fill(lower.begin(), lower.end(), -inf);
    fill(upper.begin(), upper.end(), inf);
    fill(isIntVar.begin(), isIntVar.end(), false);
}
void MilpInstance::setTarget(vector<pair<int, double>> _cost, bool _minOrMax) {
    minOrMax = _minOrMax;
    cost.resize(varCnt);
    for (auto var: _cost)
        cost[var.first] = var.second * (minOrMax == MAX ? -1. : 1.);
}
void MilpInstance::addConstr(vector<pair<int, double>> w, int rel, double b) {
    constr.push_back(Constraint(w, rel, b));
}
void MilpInstance::setVarBound(int _var, int _lower, int _upper) {
    lower[_var] = _lower; upper[_var] = _upper;
}
void MilpInstance::addIntVar(int _var) {
    intVar.push_back(_var); intVarCnt ++;
    isIntVar[_var] = true;
}

ostream& operator <<(ostream& out, const MilpInstance &milp) {
    out << "minimize ";
    for (int i = 0; i < milp.varCnt; i ++) {
        if (milp.cost[i] == 0.) continue;
        if (milp.cost[i] >= 0. && i > 0) out << "+ ";
        out << milp.cost[i] << " x" << i << " ";
    }
    out << endl;
    for (auto constr: milp.constr) {
        for (auto weight: constr.w) {
            if (weight.second >= 0.) out << "+ ";
            out << weight.second << " x" << weight.first << " ";
        }
        if (constr.rel == LE) out << "<= ";
        else if (constr.rel == EQ) out << "== ";
        else if (constr.rel == GE) out << ">= ";
        out << constr.b << endl;
    }
    for (int i = 0; i < milp.varCnt; i ++) {
        if (milp.upper[i] == inf && milp.lower[i] == -inf) continue;
        if (milp.lower[i] > -inf) out << milp.lower[i] << " <= ";
        out << "x" << i;
        if (milp.upper[i] < inf) out << " <= " << milp.upper[i];
        out << endl;
    }
    out << "integer vars: ";
    for (auto v: milp.intVar)
        out << "x" << v << " ";
    out << endl;
    
    return out;
}
