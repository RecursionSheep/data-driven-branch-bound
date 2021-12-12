#include "lp.h"

#include <string>

using namespace std;

LPSolver::LPSolver() {
    try {
        env = new GRBEnv(true);
        env->set("LogFile", "lp.log");
        env->start();
        model = new GRBModel(*env);
    } catch (GRBException e) {
        cout << e.getMessage() << endl;
    }
}
LPSolver::~LPSolver() {
    delete model;
    delete env;
}
void LPSolver::init(int _varCnt) {
    var.clear();
    varCnt = _varCnt;
    constrCnt = 0;
    obj = 0.;
}
void LPSolver::addVar(int id, double cost, int lower, int upper) {
    GRBVar v = model->addVar((double)lower, (double)upper, 0., GRB_CONTINUOUS, "x_" + to_string(id));
    //cout << "x_" + to_string(id) << endl;
    var.push_back(v);
    obj += cost * v;
}
void LPSolver::addConstr(const Constraint &constr) {
    GRBLinExpr c = 0.;
    for (auto term: constr.w) {
        try {
            c += term.second * var[term.first];
        } catch (GRBException e) {
            cout << e.getMessage() << endl;
        }
    }
    if (constr.rel == EQ)
        model->addConstr(c == constr.b, "c_" + to_string(constrCnt ++));
    else if (constr.rel == LE)
        model->addConstr(c <= constr.b, "c_" + to_string(constrCnt ++));
    else if (constr.rel == GE)
        model->addConstr(c >= constr.b, "c_" + to_string(constrCnt ++));
}
void LPSolver::modifyBound(int id, int lower, int upper) {
    GRBVar v = model->getVarByName("x_" + to_string(id));
    v.set(GRB_DoubleAttr_LB, (double)lower);
    v.set(GRB_DoubleAttr_UB, (double)upper);
}
void LPSolver::setObj() {
    model->setObjective(obj, GRB_MINIMIZE);
}
void LPSolver::solve() {
    //model->update();
    try {
        model->optimize();
    } catch (GRBException e) {
        cout << e.getMessage() << endl;
    }
}
bool LPSolver::isInfeasible() {
    int status = model->get(GRB_IntAttr_Status);
    return status == GRB_INFEASIBLE;
}
bool LPSolver::isUnbounded() {
    int status = model->get(GRB_IntAttr_Status);
    return status == GRB_UNBOUNDED;
}
double LPSolver::getObj() {
    return model->get(GRB_DoubleAttr_ObjVal);
}
double LPSolver::getVar(int id) {
    GRBVar v = var[id];
    return v.get(GRB_DoubleAttr_X);
}
