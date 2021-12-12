#include <bits/stdc++.h>

#include "lp.h"
#include "parser.h"
#include "milp.h"
#include "treenode.h"

using namespace std;

void branch_and_bound(MilpInstance *milp) {
    Node *root = new Node(milp);
    LPSolver *lpsolver = new LPSolver();
    cout << "new solver" << endl;
    lpsolver->init(milp->varCnt);
    cout << "init" << endl;
    for (int i = 0; i < milp->varCnt; i ++)
        lpsolver->addVar(i, milp->cost[i], milp->lower[i], milp->upper[i]);
    cout << "added var" << endl;
    for (auto constr: milp->constr)
        lpsolver->addConstr(constr);
    cout << "added constraint" << endl;
    lpsolver->setObj();
    lpsolver->solve();
}

int main(int argc, char **argv) {
    ifstream in(argv[1]);
    MilpParser parser;
    MilpInstance *milp = parser.parse(in);
    in.close();
    
    cout << *milp;
    branch_and_bound(milp);
    
    return 0;
}
