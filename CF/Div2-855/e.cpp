#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = long long;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;


void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& v) { for(ll& i : v) is >> i; return is; }
ostream& operator<<(ostream& os, vi& v) { for(ll i : v) os << i << " "; return os; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

struct DSU
{
    vector<int> e;
    DSU(int N) { e = vector<int>(N, -1); }
    int get(int x) { return e[x] < 0 ? x : x = get(e[x]); }
    int size(int x) { return -e[x]; }
    bool unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return false;
        if (e[x] > e[y])
            swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};

void testcase() {
    int n, k;
    cin >> n >> k;
    DSU dsu(n);
    for(int i = 0; i < n; i++) {
        if(i + k < n)
            dsu.unite(i, i + k);
        if(i + k + 1 < n)
            dsu.unite(i, i + k + 1);
    }
    
    string s;
    cin >> s;
    vector<array<int, 26>> comps(n);
    for(int i = 0; i < n; i++)
        comps[dsu.get(i)][s[i] - 'a']++;
    string t;
    cin >> t;
    for(int i = 0; i < n; i++) {
        if(comps[dsu.get(i)][t[i] - 'a'] == 0) {
            cout << "NO\n";
            return;
        }
        comps[dsu.get(i)][t[i] - 'a']--;
    }
    cout << "YES\n";
}

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) 
        testcase();
}