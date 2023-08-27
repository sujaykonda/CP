#include <cplib/general.h>
using namespace std;

template<class T, T comb(T, T)> 
struct ItSegT {
    int n;
    vector<T> tr;
    ItSegT(int n) : n(n), tr(2 * n + 1) {}
    void add(int k, T u) {
        k += n, tr[k] += u;
        for(k /= 2; k >= 1; k /= 2)
            tr[k] = comb(tr[2 * k], tr[2 * k + 1]);
    }
    ll query(int a, int b) {
        a += n, b += n;
        T r(0);
        while(a <= b) {
            if(a % 2 == 1) r = comb(tr[a++], r);
            if(b % 2 == 0) r = comb(r, tr[b--]);
            a /= 2, b /= 2;
        }
        return r;
    }
};


int _max(int a, int b) { return max(a, b); }
int _add(int a, int b) { return a + b; }

int main() {
    int n, q; rd(n, q);
    vector<int> a(n); rd(a);
    vector<vector<pair<int, int>>> qr(n + 1);
    for(int i = 0; i < q; i++) {
        int l, r; rd(l, r);
        qr[r].pb({l, i});
    }
    vector<vector<int>> loc(n + 1);
    for(int i = 0; i < n; i++) loc[a[i]].pb(i);

    ItSegT<int, _max> mxsegt((1 << 20));
    ItSegT<int, _add> smsegt((1 << 20));
    vector<int> ans(q);
    for(int i = 1; i <= n; i++) {
        smsegt.add(0, loc[i].size());
        int prev = -1;
        for(int u : loc[i]) {
            int mx;
            if(prev != -1) mx = mxsegt.query(prev + 1, u);
            else mx = i;
            smsegt.add(mx + 1, -1);
            mxsegt.add(u, i);
            prev = u;
        }
        for(auto [u, v] : qr[i]) {
            ans[v] = smsegt.query(0, u);
        }
    }

    for(int ai : ans) cout << ai << '\n';
}

