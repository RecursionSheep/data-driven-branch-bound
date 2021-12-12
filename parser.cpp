#include "parser.h"

#include <string>

using namespace std;

MilpParser::MilpParser() {}
MilpParser::~MilpParser() {}

MilpInstance* MilpParser::parse(istream& in) {
    int varCnt;
    in >> varCnt;
    
    MilpInstance *milp = new MilpInstance(varCnt);
    string op;
    while (in >> op) {
        string s;
        if (op == "target:") {
            int sign = 1;
            double weight = 1.;
            int var = 0;
            bool minOrMax = MIN;
            in >> op;
            if (op == "max") minOrMax = MAX;
            vector<pair<int, double>> cost;
            while (in >> s) {
                if (s == ";") break;
                if (s == "+")
                    sign = 1;
                else if (s == "-")
                    sign = -1;
                else if (s[0] == 'x') {
                    var = atoi(s.substr(1).c_str());
                    cost.push_back(make_pair(var, sign * weight));
                    weight = 1.; sign = 1;
                } else if (s == "*") {
                    continue;
                } else {
                    weight = atof(s.c_str());
                }
            }
            milp->setTarget(cost, minOrMax);
        } else if (op == "constr:") {
            int sign = 1;
            double weight = 1.;
            int var = 0;
            int rel = EQ;
            double b;
            vector<pair<int, double>> w;
            while (in >> s) {
                if (s == "+")
                    sign = 1;
                else if (s == "-")
                    sign = -1;
                else if (s == "==") {
                    rel = EQ; break;
                } else if (s == "<=") {
                    rel = LE; break;
                } else if (s == ">=") {
                    rel = GE; break;
                } else if (s[0] == 'x') {
                    var = atoi(s.substr(1).c_str());
                    w.push_back(make_pair(var, sign * weight));
                    weight = 1.; sign = 1;
                } else if (s == "*") {
                    continue;
                } else {
                    weight = atof(s.c_str());
                }
            }
            in >> b;
            milp->addConstr(w, rel, b);
            in >> op;
        } else if (op == "bound:") {
            int weight;
            int lower = -inf, upper = inf;
            int var;
            bool bound = false;
            while (in >> s) {
                if (s == ";") break;
                if (s[0] == 'x') {
                    var = atoi(s.substr(1).c_str());
                    if (bound) lower = weight;
                    weight = 0; bound = false;
                } else if (s == "<=") {
                    continue;
                } else {
                    weight = atof(s.c_str());
                    bound = true;
                }
            }
            if (bound) upper = weight;
            milp->setVarBound(var, lower, upper);
        } else if (op == "int:" ) {
            while (in >> s) {
                if (s == ";") break;
                if (s[0] == 'x') {
                    int var = atoi(s.substr(1).c_str());
                    milp->addIntVar(var);
                }
            }
        }
    }
    return milp;
}
