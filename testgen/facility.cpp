#include <bits/stdc++.h>

using namespace std;

const int N = 70;
int y[N][N], x[N];
int d[N][N], f[N];
int main(int argc, char **argv) {
    srand(233);
    int testcnt = atoi(argv[1]);
    for (int test = 1; test <= testcnt; test ++) {
        ofstream out("facility" + to_string(test) + ".in");
        for (int i = 0; i < N; i ++)
            for (int j = 0; j < N; j ++)
                d[i][j] = rand() % 10000;
        for (int i = 0; i < N; i ++)
            f[i] = rand() % 3000;
        int varcnt = 0;
        for (int i = 0; i < N; i ++)
            x[i] = varcnt ++;
        for (int i = 0; i < N; i ++)
            for (int j = 0; j < N; j ++)
                y[i][j] = varcnt ++;
        
        out << varcnt << endl;
        out << "target: min ";
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                if (!(i == 0 && j == 0)) out << " + ";
                out << d[i][j] << " * x" << y[i][j];
            }
        }
        for (int i = 0; i < N; i ++) {
            out << " + " << f[i] << " * x" << x[i];
        }
        out << " ;" << endl;
        for (int i = 0; i < N; i ++) {
            out << "constr: ";
            for (int j = 0; j < N; j ++) {
                if (j > 0) out << " + ";
                out << " x" << y[i][j];
            }
            out << " == " << 1 << " ;" << endl;
            for (int j = 0; j < N; j ++) {
                out << "constr: x" << y[i][j] << " - x" << x[j] << " <= 0 ;" << endl;
            }
        }
        for (int i = 0; i < N; i ++) {
            out << "int: x" << x[i] << " ;" << endl;
            out << "bound: " << "0 <= x" << x[i] << " <= 1 ;" << endl;
        }
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                out << "bound: " << "0 <= x" << y[i][j] << " <= 1 ;" << endl;
            }
        }
        
        out.close();
    }
    return 0;
}
