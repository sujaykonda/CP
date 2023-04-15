#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }
const ll MOD = 998244353;

map<ll, ll> sm, cnt;

void get(ll x) {
    if(sm.count(x)) return;
    if(x % 2) {
        get((x - 1) / 2);
        sm[x] = (2 * sm[(x - 1) / 2] + cnt[(x - 1) / 2]) % MOD;
        cnt[x] = cnt[(x - 1) / 2];
    } else {
        get(x / 2), get(x / 2 - 1);
        sm[x] = (2 * (sm[x / 2] + sm[x / 2 - 1])) % MOD;
        cnt[x] = (cnt[x / 2] + cnt[x / 2 - 1]) % MOD;
    }
}

int main() {
    sm[0] = 0, cnt[0] = 1;
    int t; cin >> t;
    for(int i = 0; i < t; i++) {
        ll n, m;
        cin >> n >> m;
        if(m == 1) {
            cout << n % MOD << endl;
        } else if(m == 2) {
            get(n);
            cout << sm[n] << endl;
        } else {
            if(n % 2)
                cout << ((((n + 1) % MOD) * ((n + 1) % MOD) % MOD) * 748683265) % MOD << endl;
            else
                cout << (((n % MOD) * ((n + 2) % MOD) % MOD) * 748683265) % MOD << endl;
        }
    }

}