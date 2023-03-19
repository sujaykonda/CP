#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
using ll = long long;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;


void setio(string name = "") {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    if(name.length()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
vi range(int s, int e) { vi r(e - s); for(int i = s; i < e; i++) r[i - s] = i; return r; }
vi range(int e) { return range(0, e); }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

int N, M;
const ll inf = 1e18;
vi m;
vector<vector<ll>> dist;

void upd(ll& v, ll nv) {
    v = max(v, nv);
}

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
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
    setio();
    cin >> N >> M;
    m.resize(N);
    cin >> m;
    dist.resize(N, vector<ll>(N, inf));
    for(int i = 0; i < M; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--, b--;
        dist[a][b] = t;
    }
    for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
    
    
    // calculate all the slopes
    vi slope(1 << N);
    for(int mask = 1; mask < (1 << N); mask++)
        for(int i = 0; i < N; i++)
            if(getbit(mask, i))
                slope[mask] = slope[mask ^ (1 << i)] + m[i];
    
    vector<vector<ll>> yinter(1 << N, vector<ll>(N, -inf));
    for(int i = 0; i < N; i++)
        yinter[1 << i][i] = 0;
    for(int mask = 1; mask < (1 << N); mask++)
        for(int i = 0; i < N; i++)
            if(yinter[mask][i] > -inf)
                for(int j = 0; j < N; j++)
                    if(!getbit(mask, j) && dist[i][j] < inf)
                        upd(yinter[mask | (1 << j)][j], yinter[mask][i] - slope[mask] * dist[i][j]);
    
    
    vector<LineContainer> lines(N);
    for(int i = 0; i < N; i++) {
        for(int mask = 0; mask < (1 << N); mask++)
            lines[i].add(slope[mask], yinter[mask][i]);
    }

    int Q;
    cin >> Q;
    for(int q = 0; q < Q; q++) {
        int s, e;
        cin >> s >> e;
        e--;
        cout << lines[e].query(s) << endl;;
    }
}