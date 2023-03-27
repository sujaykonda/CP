// problem is SOOOO CRINGE HOLY revisit 
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int N;
	cin >> N;
	vector<ll> ps(N + 1);
	for(int i = 0; i < N; i++)
        cin >> ps[i + 1], ps[i + 1] += ps[i];
    for(int i = 1; i < N; i++)
        ps[i] = __gcd(ps[i], ps[N]);

    // find prime factorization of total sum
    ll rest = ps[N];
    vector<pair<ll, ll>> pf;
    for(int i = 2; i < 1e6; i++) {
        if(rest % i == 0) pf.push_back({i, 0});
        while(rest % i == 0) pf.back().second++, rest /= i;
    }
    for(int i = 1; i <= N; i++) {
        ll g = __gcd(ps[i], rest);
        if(g != 1 && g != rest) {
            if(g > rest / g) g = rest / g;
            if(g * g == rest)
                pf.push_back({g, 2});
            else
                pf.push_back({g, 1}), pf.push_back({rest / g, 1});
            rest = 1;
        }
    }
    
	int Q;
	cin >> Q;
    vector<ll> queries;
	for(int i = 0; i < Q; i++) {
        cin >> queries[i];
	}
}
