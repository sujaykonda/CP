#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = long long;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

void setio(string name = "") { 
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    if(name != "") {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
vi range(int s, int e) { vi r(e - s); for(int i = s; i < e; i++) r[i - s] = i; return r; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

struct node {
    ll val, lb, rb;
    node *left, *right;
    node(ll lb, ll rb) : lb(lb), rb(rb), val(0) { left = right = NULL; }
    void upd(ll k, ll v) {
        val = min(val, v);
        if(lb == k && rb == k) return;
        ll m = (lb + rb) / 2;
        if(k <= m) {
            if(!left) left = new node(lb, m);
            left->upd(k, v);
        } else {
            if(!right) right = new node(m + 1, rb);
            right->upd(k, v);
        }
    }
    ll query(ll l, ll r) {
        if(r < lb || rb < l) return 0;
        if(l <= lb && rb <= r) return val;
        ll m = (lb + rb) / 2;
        ll re = 0;
        if(left) re = min(re, left->query(l, r));
        if(right) re = min(re, right->query(l, r));
        return re;
    }
};

int main() {
    setio("boards");
    int N, P;
    cin >> N >> P;
    vpi s(P), e(P);
    for(int i = 0; i < P; i++)
        cin >> s[i] >> e[i];
    vi dp(P);
    node* segtree = new node(0, N);
    vi o1 = range(0, P), o2 = range(0, P);
    sort(o1.begin(), o1.end(), [&] (int a, int b) { return s[a] < s[b]; });
    sort(o2.begin(), o2.end(), [&] (int a, int b) { return e[a] < e[b]; });
    int j = 0;
    for(int i : o1) {
        while(e[o2[j]] < s[i]) segtree->upd(e[o2[j]].second, dp[o2[j]]), j++;
        dp[i] = s[i].first + s[i].second - e[i].first - e[i].second + segtree->query(0, s[i].second);
    }
    ll mn = 0;
    for(ll i : dp) mn = min(mn, i);
    cout << 2 * N + mn << endl;
}