#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;

void pf(int x, map<int, int>& pf) {
    bool iscomp = true;
    while(iscomp) {
        iscomp = false;
        for(int i = 2; i * i <= x; i++) {
            if(x % i == 0) {
                pf[i]++; x /= i;
                iscomp = true;
                break;
            }
        }
    }
    if(x > 1)
        pf[x]++;
}

void tc() {
    int n, m1, m2; rd(n, m1, m2);
    map<int, int> mppf; pf(m1, mppf), pf(m2, mppf);
    vector<pair<int, int>> mpf;
    int fcnt = 1;
    vector<vector<ll>> pw;
    for(auto [u, v] : mppf) {
        mpf.pb({u, v}), fcnt *= (v + 1);
        pw.pb(vector<ll>(v + 1, 1));
        for(int i = 1; i <= v; i++) pw.back()[i] = pw.back()[i - 1] * u;
    }
    vector<ll> mxfact(fcnt);
    ll xans = 0, cntans = 0;
    for(int i = 0; i < fcnt; i++) {
        int k = i, l = 1; ll fact = 1;
        for(int j = 0; j < mpf.size(); j++) {
            fact *= pw[j][k % (mpf[j].second + 1)];
            if(k % (mpf[j].second + 1) > 0)
                mxfact[i] = max(mxfact[i], mxfact[i - l]);
            k /= mpf[j].second + 1;
            l *= mpf[j].second + 1;
        }
        if(fact <= n)
            mxfact[i] = max(mxfact[i], fact);
        if(mxfact[i] > 0 && fact / mxfact[i] <= n) {
            xans ^= fact / mxfact[i];
            cntans++;
        }
    }
    cout << cntans << " " << xans << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}