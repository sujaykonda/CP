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

int main() {
    setio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        int n;
        cin >> n;
        vi p(2 * n);
        cin >> p;
        sort(p.begin(), p.end());
        ll zv = 0;
        for(ll i : p) zv += llabs(i);
        if(n == 1) {
            ll v = 0;
            ll med = (p[n - 1] + p[n]) / 2;
            for(ll i : p) v += llabs(i - med);
            cout << v << endl;
        } else {
            if(n % 2 == 0) {
                ll ov = 0;
                for(ll i : p) ov += llabs(i + 1);
                ll md = 1e18;
                for(ll i : p) md = min(md, llabs(i - n) - llabs(i + 1));
                if(n == 2) {
                    ll tv = 0;
                    for(ll i : p) tv += llabs(2 - i);
                    zv = min(tv, zv);
                }
                cout << min(zv, ov + md) << endl;
            } else {
                cout << zv << endl;
            }
        }
    }
}