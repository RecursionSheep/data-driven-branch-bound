#include <bits/stdc++.h>

using namespace std;

const int N = 10;
const int MAXVALUE = 1000, MAXSIZE = 1000;

int main(int argc, char **argv) {
    srand(23333);
    int testcnt = atoi(argv[1]);
    for (int test = 1; test <= testcnt; test ++) {
        ofstream out("knapsack" + to_string(test) + ".in");
        
        out << N << endl;
        int W = rand() % MAXSIZE;
        vector<int> value, size;
        for (int i = 0; i < N; i ++) {
            value.push_back(rand() % MAXVALUE);
            size.push_back(rand() % (W / (N / 5)));
        }
        out << "target: max ";
        for (int i = 0; i < N; i ++) {
            if (i > 0) out << " + ";
            out << value[i] << " * x" << i;
        }
        out << " ;" << endl;
        out << "constr: ";
        for (int i = 0; i < N; i ++) {
            if (i > 0) out << " + ";
            out << size[i] << " * x" << i;
        }
        out << " <= " << W << " ;" << endl;
        for (int i = 0; i < N; i ++)
            out << "int: x" << i << " ;" << endl;
        for (int i = 0; i < N; i ++)
            out << "bound: " << "0 <= x" << i << " <= 1 ;" << endl;
        
        out.close();
    }
    return 0;
}
