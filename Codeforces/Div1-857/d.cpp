#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }

const ll inf = 1e17;

void upd(pair<ll, ll>& x, pair<ll, ll> y) { x = min(x, y); }
void testcase() {
    int n, m, p; cin >> n >> m >> p;
    vector<ll> w(n);
    for(int i = 0; i < n; i++) cin >> w[i];

    vector<vector<ll>> dist(n, vector<ll>(n, inf));
    for(int i = 0; i < m; i++) {
        ll a, b, s; cin >> a >> b >> s;
        a--, b--;
        dist[a][b] = min(dist[a][b], s);
    }
    for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];

    if(dist[0][n - 1] == inf) {
        cout << "-1" << endl;
        return;
    }
    vector<int> o(n - 1);
    for(int i = 0; i < n - 1; i++) o[i] = i;
    sort(o.begin(), o.end(), [&] (int a, int b) { return w[a] < w[b]; });
    vector<int> ro = o; 
    reverse(ro.begin(), ro.end());
    ro.insert(ro.begin(), n - 1);
    vector<pair<ll, ll>> dp(n, {inf, inf});
    dp[0] = {0, -p};
    bool started = false;
    for(int i : o) {
        if(i == 0) started = true;
        if(!started) continue;
        for(int j : ro) {
            if(i == j) break;
            if(dist[i][j] < inf) {
                ll cost = dist[i][j] + dp[i].second;
                if(cost < 0) cost = 0;
                ll perf = cost / w[i] + (cost % w[i] != 0);
                upd(dp[j], {dp[i].first + perf, dist[i][j] + dp[i].second - perf * w[i]});
            }
        }
    }
    cout << dp[n - 1].first << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}