#include <cmath>
#include <cassert>

#include "treenode.h"

using namespace std;

int Node::branchLeftBound(double x, int lower, int upper) {
    if (fabs(x - upper) < eps) return upper - 1;
    int b = round(x);
    if (b <= x) return b; else return b - 1;
}
int Node::branchRightBound(double x, int lower, int upper) {
    return branchLeftBound(x, lower, upper) + 1;
}
double Node::fractional(double x) {
    int b = round(x);
    if (b < x)
        return min(x - b, b + 1 - x);
    else
        return min(b - x, x + 1 - b);
}

Node::Node(MilpInstance *_milp) {
    milp = _milp;
    for (int i = 0; i < milp->intVarCnt; i ++) {
        lower.push_back(milp->lower[milp->intVar[i]]);
        upper.push_back(milp->upper[milp->intVar[i]]);
    }
    infeasible = unbounded = false;
}
Node::Node(Node *fa) {
    milp = fa->milp;
    for (int i = 0; i < milp->intVarCnt; i ++) {
        lower.push_back(fa->lower[i]);
        upper.push_back(fa->upper[i]);
    }
    infeasible = unbounded = false;
}
Node::~Node() {}
void Node::solveRelaxed(LPSolver *solver) {
    for (int i = 0; i < milp->intVarCnt; i ++) {
        int id = milp->intVar[i];
        solver->modifyBound(id, lower[i], upper[i]);
    }
    solver->solve();
    if (solver->isInfeasible()) {
        infeasible = true; dualCost = dinf;
        return;
    }
    if (solver->isUnbounded()) {
        unbounded = true; dualCost = -dinf;
        return;
    }
    
    dualCost = solver->getObj();
    for (int i = 0; i < milp->varCnt; i ++)
        relaxedSol.push_back(solver->getVar(i));
    priority = -dualCost;
}
bool Node::checkInt() {
    for (auto i: milp->intVar) {
        double xi = relaxedSol[i];
        int xiround = round(xi);
        if (fabs(xi - xiround) > eps)
            return false;
    }
    return true;
}
void Node::computeScore(LPSolver *solver) {
    for (int i = 0; i < milp->intVarCnt; i ++) {
        int id = milp->intVar[i];
        solver->modifyBound(id, lower[i], upper[i]);
    }
    for (int i = 0; i < milp->intVarCnt; i ++) {
        int id = milp->intVar[i];
        score.push_back(vector<double>());
        if (upper[i] == lower[i]) {
            score[i].push_back(0); score[i].push_back(0); score[i].push_back(0);
            continue;
        }
        
        double leftImprove, rightImprove;
        int newupper = branchLeftBound(relaxedSol[id], lower[i], upper[i]);
        int newlower = branchRightBound(relaxedSol[id], lower[i], upper[i]);
        solver->modifyBound(id, lower[i], newupper);
        //cout << lower[i] << ' ' << newupper << endl;
        solver->solve();
        if (solver->isInfeasible())
            leftImprove = dinf;
        else
            leftImprove = solver->getObj() - dualCost;
        solver->modifyBound(id, newlower, upper[i]);
        //cout << newlower << ' ' << upper[i] << endl;
        solver->solve();
        if (solver->isInfeasible())
            rightImprove = dinf;
        else
            rightImprove = solver->getObj() - dualCost;
        score[i].push_back(min(leftImprove, rightImprove));
        score[i].push_back(max(leftImprove, rightImprove));
        score[i].push_back(fractional(relaxedSol[id]));
        //cout << score[i][0] << ' ' << score[i][1] << ' ' << score[i][2] << endl;
        assert(leftImprove >= -eps);
        assert(rightImprove >= -eps);
        
        solver->modifyBound(id, lower[i], upper[i]);
    }
}
void Node::outputRelaxedSol() {
    cout << "Relaxed solution:" << endl;
    for (auto x: relaxedSol)
        cout << x << " ";
    cout << endl;
}
void Node::chooseBranchVar() {
    double branchScore = 0;
    for (int i = 0; i < milp->intVarCnt; i ++) {
        if (score[i][0] + score[i][1] + score[i][2] > branchScore) {
            branchVar = i;
            branchScore = score[i][0] + score[i][1] + score[i][2];
        }
    }
}
