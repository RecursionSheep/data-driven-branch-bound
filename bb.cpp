#include <bits/stdc++.h>

#include "parser.h"
#include "milp.h"

using namespace std;

int main(int argc, char **argv) {
    ifstream in(argv[1]);
    MilpParser parser;
    MilpInstance *milp = parser.parse(in);
    in.close();
    
    cout << *milp;
    
    return 0;
}
