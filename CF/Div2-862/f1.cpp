#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }
ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }

const int M = 1e9 + 7;

int solve(vector<ll>& a) {
    //cout << str(a) << endl;
    if(a.size() == 1) return a[0];
    vector<ll> na(a.size() - 1);
    priority_queue<pair<ll, pair<ll, ll>>> pq;
    for(int i = 1; i < a.size(); i++)
        pq.push({-a[i] - a[i - 1], {i, i - 1}});
    for(int i = 0; i < na.size(); i++) {
        pair<ll, ll> p = pq.top().second;
        na[i] = (-pq.top().first), pq.pop();
        if(p.first + 1 < a.size())
            pq.push({-a[p.first + 1] - a[p.second], {p.first + 1, p.second}});
    }
    ll a0 = a[0];
    for(int i = 0; i < na.size(); i++) na[i] -= a0;
    return (solve(na) + a0 * fe(2, na.size() - 1, M)) % M;;
}

int main() {
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    cout << solve(a) << endl;
}