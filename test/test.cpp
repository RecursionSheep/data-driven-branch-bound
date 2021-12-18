#include <bits/stdc++.h>

using namespace std;

const int testcnt = 100;
const double epsilon = 0.01;
const double lower = 0., upper = 1.;
const int maxnode = 10000;
string testname = "knapsack";
int main() {
    ofstream out(testname + "_test.log");
    double mu = lower;
    while (mu <= upper) {
        int ave = 0;
        for (int iter = 1; iter <= testcnt; iter ++) {
            system(("./bb testgen/" + testname + to_string(iter) + ".in bb.log " + to_string(mu) + " " + to_string(maxnode)).c_str());
            ifstream in("bb.log");
            int cnt = 0;
            string s;
            in >> s >> cnt;
            in.close();
            ave += cnt;
        }
        out << setprecision(4) << mu << " " << (double)ave / testcnt << endl;
        mu += epsilon;
    }
    out.close();
    return 0;
}
