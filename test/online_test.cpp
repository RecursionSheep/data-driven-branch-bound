#include <bits/stdc++.h>
#include <random>

using namespace std;

const int testcnt = 100;
const double epsilon = 0.01;
const int maxnode = 10000;
const double eta = 0.01;
const double bestArm = 1.0;
int armCnt = 0;
string testname = "knapsack";
double arm[10000];
double loss[10000], p[10000];
default_random_engine e;
uniform_real_distribution<double> u(0.0, 1.0);

int main() {
    srand(23333);
    ofstream out(testname + "_test.log");
    for (double a = 0; a < 1. + epsilon; a += epsilon)
        arm[armCnt ++] = a;
    for (int iter = 1; iter <= testcnt; iter ++) {
        double sum = 0.;
        for (int i = 0; i < armCnt; i ++) {
            p[i] = exp(-eta * loss[i]);
            sum += p[i];
        }
        for (int i = 0; i < armCnt; i ++) p[i] /= sum;
        double prob = u(e);
        int armChoose = armCnt - 1;
        for (int i = 0; i < armCnt; i ++) {
            if (prob < p[i]) {
                armChoose = i; break;
            }
            prob -= p[i];
        }
        cout << arm[armChoose] << endl;
        
        system(("./bb testgen/" + testname + to_string(iter) + ".in bb.log " + to_string(arm[armChoose]) + " " + to_string(maxnode)).c_str());
        ifstream in1("bb.log");
        int realCnt = 0;
        string s;
        in1 >> s >> realCnt;
        in1.close();
        
        loss[armChoose] += ((double)realCnt / maxnode) / p[armChoose];
        
        system(("./bb testgen/" + testname + to_string(iter) + ".in bb.log " + to_string(bestArm) + " " + to_string(maxnode)).c_str());
        ifstream in2("bb.log");
        int bestCnt = 0;
        in2 >> s >> bestCnt;
        in2.close();
        
        out << iter << ' ' << realCnt - bestCnt << endl;
    }
    out.close();
    return 0;
}
