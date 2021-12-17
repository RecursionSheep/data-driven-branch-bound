#include <bits/stdc++.h>

using namespace std;

const int N = 30;
double d[N][N];
int x[N], y[N][N];
int main(int argc, char **argv) {
    srand(2333);
    int testcnt = atoi(argv[1]);
    for (int test = 1; test <= testcnt; test ++) {
        ofstream out("cluster" + to_string(test) + ".in");
        int k = 5;
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                d[i][j] = (double)(rand() % 100000) / 100000;
            }
            d[i][i] = 0;
        }
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
        out << " ;" << endl;
        out << "constr: ";
        for (int i = 0; i < N; i ++) {
            if (i > 0) out << " + ";
            out << " x" << x[i];
        }
        out << " == " << k << " ;" << endl;
        for (int i = 0; i < N; i ++) {
            out << "constr: ";
            for (int j = 0; j < N; j ++) {
                if (j > 0) out << " + ";
                out << " x" << y[i][j];
            }
            out << " == " << 1 << " ;" << endl;
        }
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                out << "constr: ";
                out << "x" << y[i][j] << " - x" << x[j] << " <= 0 ;" << endl;
            }
        }
        for (int i = 0; i < N; i ++) {
            out << "int: x" << x[i] << " ;" << endl;
            out << "bound: " << "0 <= x" << x[i] << " <= 1 ;" << endl;
        }
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                out << "int: x" << y[i][j] << " ;" << endl;
                out << "bound: " << "0 <= x" << y[i][j] << " <= 1 ;" << endl;
            }
        }
        
        out.close();
    }
    return 0;
}
