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
    int n;
    cin >> n;
    vi a(n);
    cin >> a;

    vector<pi> opr;
    for(int i = 0; i <= 30 * n; i++) {
        if(i == 30 * n) {
            cout << -1 << endl;
            return;
        }
        int mj = 0;
        for(int j = 0; j < n; j++)
            if(a[j] < a[mj])
                mj = j;
        bool cont = false;
        for(int j = 0; j < n; j++) {
            if(a[mj] != a[j]) {
                cont = true;
                a[j] = a[j] / a[mj] + (a[j] % a[mj] != 0);
                opr.pb({j + 1, mj + 1});
                break;
            }
        }
        if(!cont) break;
    }
    cout << opr.size() << endl;
    for(int i = 0; i < opr.size(); i++)
        cout << opr[i] << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}