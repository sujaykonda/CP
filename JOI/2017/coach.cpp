#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) {
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main() {
    ll X, N, M, W, T;
    cin >> X >> N >> M >> W >> T;
    vector<pair<ll, ll>> e;
    for(int i = 0; i < N; i++) {
        ll s; cin >> s;
        e.push_back({s % T, -s});
    }
    e.push_back({X % T, -X});
    ll mndp = (X / T + 1) * W;
    for(int i = 0; i < M; i++) {
        ll d, c; cin >> d >> c;
        mndp += ((X - d) / T + 1) * W;
        e.push_back({d, c});
    }
    sort(e.begin(), e.end());
    ll g = 0;
    ll x = 0;
    LineContainer lc;
    for(int i = e.size() - 1; i >= 0; i--) {
        if(e[i].second < 0) {
            ll m = W * (-e[i].second / T);
            lc.add(-m, -(mndp - g - x * m));
        } else {
            if(!lc.empty()) {
                g += e[i].second - ((X - e[i].first) / T + 1) * W;
                x++;
                mndp = min(mndp, g - lc.query(x));
            }
        }
    }
    cout << mndp << endl;
}