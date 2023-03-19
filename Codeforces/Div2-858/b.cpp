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
        vi cnt(2);
        for(int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if(a < 2)
                cnt[a]++;
        }
        if(cnt[0] > n - cnt[0] + 1) {
            if(cnt[1] == 0 || n - cnt[0] - cnt[1] > 0) {
                cout << 1 << endl;
            } else {
                cout << 2 << endl;
            }
        } else {
            cout << 0 << endl;
        }
    }
}