#include <cplib/math/mint.h>
using namespace std;

const int MOD = 1e9+7;

void testcase() {
    int n, m, k;
    rd(n, m, k);
    vector<int> a(n); rd(a);
    mint<MOD> ans = 0;
    mint<MOD> choose = 1;
    for(int i = 0; i < n; i++) {
        ans += choose * pow(mint<MOD>(k - 1), m - i);
        choose *= m - i, choose /= (i + 1);
    }
    cout << (pow(mint<MOD>(k), m) - ans).v << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}