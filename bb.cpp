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
    //cout << "set objective" << endl;
    root->solveRelaxed(lpsolver);
    //cout << "root" << endl;
    
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
    int iterCnt = 0;
    while (!Q.empty()) {
        iterCnt ++;
        Node *node = Q.top(); Q.pop();
        //cout << node->dualCost << endl;
        if (node->checkInt()) {
            if (node->dualCost < bestCost) {
                bestCost = node->dualCost;
                for (int i = 0; i < milp->varCnt; i ++)
                    bestSol[i] = node->relaxedSol[i];
            }
            delete node;
            continue;
        }
        if (node->rounding(lpsolver)) {
            if (node->roundingCost < bestCost) {
                bestCost = node->roundingCost;
                for (int i = 0; i < milp->varCnt; i ++)
                    bestSol[i] = node->roundingSol[i];
            }
        }
        
        //node->outputRelaxedSol();
        node->computeScore(lpsolver);
        //cout << "score" << endl;
        node->chooseBranchVar();
        //cout << "branch: " << node->branchVar << endl;
        int newupper = Node::branchLeftBound(node->relaxedSol[milp->intVar[node->branchVar]], node->lower[node->branchVar], node->upper[node->branchVar]);
        int newlower = Node::branchRightBound(node->relaxedSol[milp->intVar[node->branchVar]], node->lower[node->branchVar], node->upper[node->branchVar]);
        //cout << node->relaxedSol[milp->intVar[node->branchVar]] << ' ' << newlower << ' ' << newupper << endl;
        for (int i = 0; i < 2; i ++) {
            //cout << "child " << i << endl;
            Node *child = new Node(node);
            if (i == 0)
                child->upper[node->branchVar] = newupper;
            else
                child->lower[node->branchVar] = newlower;
            //cout << "set new bound" << endl;
            child->solveRelaxed(lpsolver);
            if (child->infeasible || child->dualCost > bestCost) {
                delete child;
                continue;
            }
            Q.push(child);
        }
        delete node;
    }
    
    cout << "Visit " << iterCnt << " nodes" << endl;
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
    
    //cout << *milp;
    branch_and_bound(milp);
    
    return 0;
}
