#include <bits/stdc++.h>

using namespace std;

const int N = 50, flip = 10;
const int M = 10000000;
double p[N][2];
int z[N], perm[N];
double w[2];
const double pi = acos(-1);

pair<double, double> Gaussian() {
    double u1 = (double)(rand() % 100000) / 99999;
    double u2 = (double)(rand() % 100000) / 99999;
    double x = sqrt(-2 * log(u1)) * cos(2 * pi * u2);
    double y = sqrt(-2 * log(u1)) * sin(2 * pi * u2);
    return make_pair(x, y);
}

int main(int argc, char **argv) {
    srand(233333);
    int testcnt = atoi(argv[1]);
    for (int test = 1; test <= testcnt; test ++) {
        ofstream out("classifier" + to_string(test) + ".in");
        for (int i = 0; i < N; i ++) {
            auto point = Gaussian();
            p[i][0] = point.first; p[i][1] = point.second;
        }
        auto point = Gaussian();
        w[0] = point.first; w[1] = point.second;
        for (int i = 0; i < N; i ++) {
            if (p[i][0] * w[0] + p[i][1] * w[1] >= 0)
                z[i] = 1;
            else
                z[i] = -1;
        }
        for (int i = 0; i < N; i ++) perm[i] = i;
        random_shuffle(perm, perm + N);
        for (int i = 0; i < flip; i ++)
            z[i] = -z[i];
        out << N + 2 << endl;
        
        out << "target: min ";
        for (int i = 0; i < N; i ++) {
            if (i != 0) out << " + ";
            out << "x" << i;
        }
        out << " ;" << endl;
        for (int i = 0; i < N; i ++) {
            out << "constr: " << z[i] * p[i][0] << " * x" << N << " + " << z[i] * p[i][1] << " * x" << N + 1 << " + " << M << " * x" << i << " >= 0.0001 ;" << endl;
        }
        out << "bound: -1 <= x" << N << " <= 1 ;" << endl;
        out << "bound: -1 <= x" << N + 1 << " <= 1 ;" << endl;
        for (int i = 0; i < N; i ++) {
            out << "bound: 0 <= x" << i << " <= 1 ;" << endl;
            out << "int: x" << i << " ;" << endl;
        }
        
        out.close();
    }
    return 0;
}
