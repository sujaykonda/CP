#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
using ll = long long;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;

void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& v) { for(ll& i : v) is >> i; return is; }
ostream& operator<<(ostream& os, vi& v) { for(ll i : v) os << i << " "; return os; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

const array<ll, 3> M = {1000000007, 998919917, 1000000009};
const ll B = 999;

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : (fe((a * a) % m, b / 2, m) * ((b % 2 ? a : 1) % m) % m); }
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

int n;
vi labels;

array<ll, 3> hsh(vi& dists) {
    array<ll, 3> hshv = {0, 0, 0};
    for(int i = 0; i < 3; i++)
        for(ll d : dists)
            hshv[i] = (hshv[i] + fe(B, d, M[i])) % M[i];
    return hshv;
}

vector<vector<int>> adj;
vector<array<ll, 3>> subhshs;
vector<array<ll, 3>> hshs;

void dfs(int s, int e) {
    subhshs[s] = {1, 1, 1};
    for(int u : adj[s]) {
        if(u != e) {
            dfs(u, s);
            for(int i = 0; i < 3; i++)
                subhshs[s][i] = (subhshs[s][i] + B * subhshs[u][i]) % M[i];
        }
    }
}

void dfs2(int s, int e) {
    for(int u : adj[s]) {
        if(u != e) {
            for(int i = 0; i < 3; i++)
                hshs[u][i] = (B * ((hshs[s][i] + B * (M[i] - subhshs[u][i])) % M[i]) % M[i] + subhshs[u][i]) % M[i];
            dfs2(u, s);
        }
    }
}

int main() {
    fastio();
    cin >> n;
    labels.resize(n - 1);
    cin >> labels;
    adj.resize(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }

    subhshs.resize(n + 1);
    dfs(1, 0);
    hshs.resize(n + 1);
    hshs[1] = subhshs[1];
    dfs2(1, 0);
    map<array<ll, 3>, vector<int>> mp;
    for(int i = 1; i <= n; i++)
        mp[hshs[i]].pb(i);
    vi good;
    array<ll, 3> labelhsh = hsh(labels);
    for(int i = 0; i < n; i++) {
        array<ll, 3> hshv = labelhsh;
        for(int j = 0; j < 3; j++) {
            hshv[j] = (hshv[j] + fe(B, i, M[j])) % M[j];
        }
        for(int j : mp[hshv])
            good.pb(j);
    }
    sort(good.begin(), good.end());
    cout << good.size() << endl;
    cout << good << endl;
}