#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = int;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;

void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& v) { for(ll& i : v) is >> i; return is; }
ostream& operator<<(ostream& os, vi& v) { for(ll i : v) os << i << " "; return os; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

void testcase() {
    int n, m;
    cin >> n >> m;
    vi p(m);
    cin >> p;
    queue<ll> r;
    for(int i = n; i > 0; i--) r.push(i);
    vi t(n, -1);
    set<int> done;
    for(int i = 0; i < m; i++) {
        if(!done.count(p[i]))
            done.insert(p[i]), r.push(p[i]);
        if(r.size() > n) {
            if(r.front() <= n)
                t[r.front() - 1] = i + 1;
            r.pop();
        }
    }
    cout << t << endl;
}

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}