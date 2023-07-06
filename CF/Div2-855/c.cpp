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

void testcase() {
    int n;
    cin >> n;
    vi s(n);
    cin >> s;
    priority_queue<ll> pq;
    ll power = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 0) {
            if(!pq.empty())
                power += pq.top(), pq.pop();
        }
        else
            pq.push(s[i]);
    }
    cout << power << endl;
}

int main() {
    fastio();

    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}