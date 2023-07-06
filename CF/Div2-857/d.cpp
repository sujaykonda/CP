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
    vector<pi> d(n);
    for(int i = 0; i < n; i++) cin >> d[i];
    sort(d.begin(), d.end(), [&] (pi a, pi b) { return a.first < b.first; });
    vi mx(n);
    mx[n - 1] = 0;
    for(int i = n - 2; i >= 0; i--) 
        mx[i] = max(mx[i + 1], d[i + 1].second);
    
    ll best = LONG_LONG_MAX;
    set<ll> bp;
    for(ll i = 0; i < n; i++) {
        if(i < n - 1)
            best = min(best, abs(d[i].first - mx[i]));
        if(d[i].first > mx[i] || i == n - 1) {
            auto lb = bp.lower_bound(d[i].first);
            if(lb != bp.end())
                best = min(best, *lb - d[i].first);
            if(lb != bp.begin()) 
                best = min(best, d[i].first - *(--lb));
        }
        bp.insert(d[i].second);
    }
    cout << best << endl;
} 

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}