#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

vector<ll> f;
vector<ll> invf;


void factorials(ll mx, ll m)
{
    f.resize(mx);
    invf.resize(mx);
    f[0] = 1, invf[0] = 1;
    for (int i = 1; i < mx; i++)
        f[i] = (f[i - 1] * i) % m;
    invf[mx - 1] = minv(f[mx - 1], m);
    for (int i = mx - 1; i >= 1; i--)
        invf[i - 1] = (invf[i] * i) % m;
}

int main() {
    int n; cin >> n;
    factorials(n / 3 + 1, 998244353);
    ll cnt = 1;
    for(int i = 0; i < n / 3; i++) {
        int a, b, c; cin >> a >> b >> c;
        int mn = min({a, b, c});
        int mncnt = (a == mn) + (b == mn) + (c == mn);
        cnt *= mncnt;
        cnt %= 998244353;
    }

    cout << ((f[n / 3] * invf[n / 6] % 998244353) * invf[n / 6] % 998244353) * cnt % 998244353 << endl;
}