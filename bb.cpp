#include <bits/stdc++.h>

#include "lp.h"
#include "parser.h"
#include "milp.h"
#include "treenode.h"

using namespace std;

void branch_and_bound(MilpInstance *milp) {
    Node *root = new Node(milp);
    LPSolver *lpsolver = new LPSolver();
    //cout << "new solver" << endl;
    lpsolver->init(milp->varCnt);
    //cout << "init" << endl;
    for (int i = 0; i < milp->varCnt; i ++)
        lpsolver->addVar(i, milp->cost[i], milp->lower[i], milp->upper[i]);
    //cout << "added var" << endl;
    for (auto constr: milp->constr)
        lpsolver->addConstr(constr);
    //cout << "added constraint" << endl;
    lpsolver->setObj();
    cout << "set objective" << endl;
    root->solveRelaxed(lpsolver);
    cout << "root" << endl;
    
    if (root->infeasible) {
        cout << "Infeasible" << endl;
        return;
    } else if (root->unbounded) {
        cout << "Unbounded relaxation" << endl;
        return;
    }
    
    double bestCost = dinf;
    vector<double> bestSol;
    bestSol.resize(milp->varCnt);
    
    priority_queue<Node*, vector<Node*>, cmp> Q;
    Q.push(root);
    while (!Q.empty()) {
        Node *node = Q.top(); Q.pop();
        cout << node->priority << endl;
        if (node->checkInt()) {
            if (node->dualCost < bestCost) {
                bestCost = node->dualCost;
                for (int i = 0; i < milp->varCnt; i ++)
                    bestSol[i] = node->relaxedSol[i];
            }
            delete node;
            continue;
        }
        
        node->computeScore(lpsolver);
        node->chooseBranchVar();
        int newupper = Node::branchLeftBound(node->relaxedSol[milp->intVar[node->branchVar]]);
        int newlower = Node::branchRightBound(node->relaxedSol[milp->intVar[node->branchVar]]);
        for (int i = 0; i < 2; i ++) {
            Node *child = new Node(node);
            if (i == 0)
                child->upper[node->branchVar] = newupper;
            else
                child->lower[node->branchVar] = newlower;
            child->solveRelaxed(lpsolver);
            if (child->infeasible || child->dualCost > bestCost) {
                delete child;
                continue;
            }
            Q.push(child);
        }
        delete node;
    }
    
    if (bestCost == dinf)
        cout << "Infeasible" << endl;
    else {
        cout << "Target: " << ((milp->minOrMax == MAX) ? -bestCost : bestCost) << endl;
        for (int i = 0; i < milp->varCnt; i ++)
            cout << "x" << i << ": " << bestSol[i] << endl;
    }
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
