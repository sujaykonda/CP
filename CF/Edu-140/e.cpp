#include <cplib/general.h>
using namespace std;

int main() {
    int n, m; rd(n, m);
    vector<int> c(n); rd(c);
    vector<int> x(m); rd(x);
    vector<ll> adj(m);
    for(int i = 0; i < n - 1; i++) {
        adj[c[i] - 1] |= 1LL << (c[i + 1] - 1);
        adj[c[i + 1] - 1] |= 1LL << (c[i] - 1);
    }
    int m1 = (m + 1) / 2;
    int adjmask = (1 << m1) - 1;
    int xsm = 0;
    for(int i = 0; i < m1; i++) xsm += x[i];
    vector<int> dp(1 << m1, xsm);
    for(int mask = 0; mask < 1 << m1; mask++) {
        bool good = true;
        for(int i = 0; i < m1; i++)
            if(getbit(mask, i)) {
                if((mask & (adj[i] & adjmask)) != 0) {
                    good = false;
                    break;
                }
            }
        if(good) {
            for(int i = 0; i < m1; i++)
                if(getbit(mask, i)) 
                    dp[mask] -= x[i];
        } else {
            for(int i = 0; i < m1; i++)
                if(getbit(mask, i)) 
                    dp[mask] = min(dp[mask], dp[mask ^ (1 << i)]);
        }
    }
    int m2 = m - m1;
    int best = 1e9;
    for(int mask = 0; mask < (1 << m2); mask++) {
        bool good = true;
        for(int i = 0; i < m2; i++)
            if(getbit(mask, i)) {
                if((mask & ((adj[i + m1] & ~adjmask) >> m1)) != 0) {
                    good = false;
                    break;
                }
            }
        if(c[0] > m1) good &= !getbit(mask, c[0] - 1 - m1);
        if(c[n - 1] > m1) good &= !getbit(mask, c[n - 1] - 1 - m1);
        if(good) {
            int v = 0;
            for(int i = 0; i < m2; i++)
                if(!getbit(mask, i))
                    v += x[i + m1];
            int omask = adjmask;
            if(c[0] <= m1) omask &= ~(1 << (c[0] - 1));
            if(c[n - 1] <= m1) omask &= ~(1 << (c[n - 1] - 1));
            for(int i = 0; i < m2; i++)
                if(getbit(mask, i))
                    omask &= ~(adj[i + m1] & adjmask);
            v += dp[omask];
            best = min(best, v);
        }
    }
    cout << best << endl;
}