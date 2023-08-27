#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int TRIAL_LIM = 1e7;

// multi dimensional prefix sums
void calcp(vector<ll>& p, vector<int>& dim) {
    int m = 1;
    for(int d : dim) {
        for(int i = 0; i < p.size() - m; i++) {
            if(i % (m * d) < m * (d - 1)) {
                p[i + m] += p[i];
            }
        }
        m *= d;
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int N;
	cin >> N;
	vector<ll> p(N + 1);
	for(int i = 0; i < N; i++)
        cin >> p[i + 1], p[i + 1] += p[i];
	int Q;
	cin >> Q;
    vector<ll> q(Q);
    for(int i = 0; i < Q; i++) cin >> q[i];
    
    vector<ll> pfs;
    ll pn = p[N];
    for(ll i = 2; i * i <= pn && i < TRIAL_LIM; i++) {
        while(pn % i == 0) {
            pfs.push_back(i);
            pn /= i;
        }
    }
    for(int i = 0; i < Q; i++) {
        ll g = __gcd(pn, q[i]);
        if(g != 1 && g != pn) {
            pfs.push_back(g);
            pn /= g;
        }
    }
    for(int i = 1; i < N; i++) {
        ll g = __gcd(pn, p[i]);
        if(g != 1 && g != pn) {
            pfs.push_back(g);
            pn /= g;
        }
    }
    if(pn > 1)
        pfs.push_back(pn);
    map<ll, int> pfmp; for(ll pf : pfs) pfmp[pf]++;
    vector<int> dim; int sz = 1;
    for(auto [u, v] : pfmp) dim.push_back(v + 1), sz *= v + 1;
    vector<ll> b(sz); 
    for(int i = 1; i < N; i++) {
        ll x = p[N] / gcd(p[i], p[N]);
        int j = 0, d = 1;
        for(auto [u, v] : pfmp) {
            while(x % u == 0) j += d, x /= u;
            d *= (v + 1);
        }
        b[j]++;
    }
    vector<ll> pb = b;
    calcp(pb, dim);
    for(int i = 0; i < Q; i++) {
        if(p[N] % q[i] == 0) {
            ll x = p[N] / q[i];
            int j = 0, d = 1;
            for(auto [u, v] : pfmp) {
                while(x % u == 0) j += d, x /= u;
                d *= (v + 1);
            }
            cout << p[N] / q[i] + N - 2 * pb[j] - 2 << endl;
        } else {
            cout << -1 << endl;
        }
    }
}
