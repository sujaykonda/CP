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
    sort(b.begin(), b.end());
    int likes = 0;
    for(int i = 0; i < n; i++) {
        if(b[i] > 0) { 
            likes = n - i; 
            break;
        }
    }
    for(int i = 0; i < n; i++) {
        if(i < likes) {
            cout << i + 1 << " ";
        } else {
            cout << 2 * likes - i - 1 << " ";
        }
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        if(i < 2 * (n - likes)) {
            cout << (i + 1) % 2 << " ";
        } else {
            cout << i + 1 - 2 * (n - likes) << " ";
        }
    }
    cout << endl;
}

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i =0 ; i < t; i++) testcase();
}