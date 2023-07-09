#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/ds/srq.h>
#include <cplib/bs.h>
using namespace std;

int _lcm(int a, int b) {
    ll caplcm = (ll) a * b / gcd(a, b);
    if(caplcm > 1e7) caplcm = 1e7 + 1;
    return caplcm;
}
void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    SRQ<int, _lcm> srq(a);
    vector<bool> s(n * 100 + 1);
    for(int i = 0; i < n; i++) {
        auto dc = [&] (int l, int r, int lv, int rv, auto&& dc) {
            if(lv > n * 100) return;
            if(lv == rv) {
                s[lv] = true;
                return;
            }
            if(l == r - 1) {
                s[lv] = true;
                dc(r, r, rv, rv, dc);
                return;
            }
            int m = (l + r) / 2;
            int mv = srq.query(i, m);
            dc(l, m, lv, mv, dc);
            dc(m, r, mv, rv, dc);
        };
        dc(i, n - 1, srq.query(i, i), srq.query(i, n - 1), dc);
    }
    int i = 1;
    while(s[i]) i++;
    cout << i << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}