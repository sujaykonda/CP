#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;
struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
};

struct BITrange {
	vector<BIT> bit;
    BITrange(int n) : bit(2, BIT(n)) { }
	void upd(int hi, ll val) {
		bit[1].add(1,val), bit[1].add(hi+1,-val); 
		bit[0].add(hi+1,hi*val); 
	}
	void upd(ll val, int lo, int hi){ upd(lo,-val), upd(hi + 1,val);}
	ll sum(int x) { return bit[1].sum(x)*x+bit[0].sum(x); } 
	ll query(int x, int y) { return sum(y + 1)-sum(x); }
}; 

int main() {
    int n, q; rd(n, q);
    vector<int> a(n); rd(a);
    vector<int> prev(n), last(n + 1, -1);
    for(int i = 0; i < n; i++) {
        prev[i] = last[a[i]];
        last[a[i]] = i;
    }
    vector<pair<int, int>> queries(q);
    vector<ll> ans(q);
    vector<vector<int>> add(n), sub(n);
    for(int i = 0; i < q; i++) {
        int l, r, x, y;
        rd(l, r, x, y);
        queries[i] = {l - 1, r - 1};
        if(x > 1) sub[x - 2].pb(i);
        add[y - 1].pb(i); 
    }
    BITrange bit(n), hbit(n);
    vector<pair<int, int>> lst(n); 
    for(int i = 0; i < n; i++) {
        lst[i].first = i - 1;
        bit.upd(i + 1, i, i);
        hbit.upd((ll)(n - i) * (i + 1), i, i);
        if(i > 0)
            lst[i - 1].second = i;
        if(prev[i] != -1) {
            int bck = lst[prev[i]].first;
            int frnt = lst[prev[i]].second;
            bit.upd(frnt - prev[i], bck + 1, prev[i]);
            hbit.upd((ll)(n - i) * (frnt - prev[i]), bck + 1, prev[i]);
            if(bck != -1)
                lst[bck].second = frnt;
            lst[frnt].first = bck;
        }
        for(int qi : add[i])
            ans[qi] += hbit.query(queries[qi].first, queries[qi].second) - (ll)(n - 1 - i) * bit.query(queries[qi].first, queries[qi].second);
        for(int qi : sub[i])
            ans[qi] -= hbit.query(queries[qi].first, queries[qi].second) - (ll)(n - 1 - i) * bit.query(queries[qi].first, queries[qi].second);
    }
    for(ll ansi : ans) cout << ansi << '\n';
}
