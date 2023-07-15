#include <cplib/general.h>
using namespace std;

int MOD = 0;
struct mint {
    int v;
    mint(int _v) : v(_v) {};
    friend mint operator*(mint a, mint b) { a.v = (a.v * b.v) % MOD; return a; }
};

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    for(int i = 0; i < n; i++) a[i]--;
    vector<vector<int>> cyc(n + 1);
    vector<bool> done(n);
    for(int i = 0; i < n; i++) {
        if(!done[i]) {
            int sz = 0;
            int j = i;
            do {
                done[j] = true;
                j = a[j]; sz++;
            } while(j != i);
            cyc[sz].pb(i);
        }
    }
    for(int i = 2; i <= n; i += 2) {
        if(cyc[i].size() > 0 && (k > 30 || cyc[i].size() % bpow(2, k) != 0)) {
            cout << "NO" << endl;
            return;
        }
    }
    vector<int> ans(n);
    cout << "YES" << endl;
    for(int sz = 1; sz <= n; sz++) {
        MOD = sz;
        sort(cyc[sz].begin(), cyc[sz].end());
        while(cyc[sz].size() > 0) {
            int msz, lgsz; for(msz = 1, lgsz = 0; 2 * msz <= cyc[sz].size() && lgsz < k; msz *= 2, lgsz++);
            vector<int> m;
            for(int i = 0; i < msz; i++) {
                m.pb(cyc[sz].back()); cyc[sz].pop_back();
            }
            if(sz > 1) {
                int d = bpow(mint((sz + 1) / 2), k - lgsz).v;
                vector<int> c(sz);
                for(int i : m) {
                    int p1 = i;
                    for(int j = 0; j < sz; j++) 
                        c[j] = p1, p1 = a[p1];
                    for(int j = 0; j < sz; j++)
                        a[c[j]] = c[(j + d) % sz];
                }
            }
            if(msz > 1) {
                // merge
                for(int j = 0; j < sz; j++) {
                    vector<int> nm(msz);
                    for(int i = 0; i < msz; i++) nm[i] = a[m[i]];
                    for(int i = 0; i < msz - 1; i++) {
                        a[m[i]] = m[i + 1];
                    }
                    a[m.back()] = nm[0];
                    m = nm;
                }
            }
        }
    }
    for(int ai : a) cout << ai + 1 << ' ';
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();    
}