#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = long long;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;

void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
void one_ind(vi& a) { a.insert(a.begin(), 0); }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }


void testcase() {
    int n;
    cin >> n;
    vi b(n);
    cin >> b;
    int mx = 0;
    int gpc = 0;
    int added = 0;
    for(int i = 0; i < n; i++) {
        if(b[i] == 1) added++, mx = max(mx, ((gpc == 0) ? 0 : gpc / 2 + 1) + added);
        if(b[i] == 2) gpc += added, added = 0;
    }
    cout << mx << endl;
}

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}