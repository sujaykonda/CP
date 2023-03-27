#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

#define pb push_back

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    int N;
    cin >> N;
    vector<vector<int>> inters(N);
    vector<vector<ll>> vals(N);
    vector<int> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];
    int cnt = 0;
    for(int i = 1; i < N; i++) cnt += a[i] >= a[i - 1];
    if(cnt > N / 2) reverse(a.begin(), a.end());
    for(int i = 0; i < N; i++) inters[i].pb(i + 1), vals[i].pb(a[i]);
    for(int i = N - 1; i >= 0; i--) {
        while(inters[i].back() < N) {
            int ep = inters[i].back();
            ll lastv = vals[i].back();
            int k = lower_bound(vals[ep].begin(), vals[ep].end(), lastv) - vals[ep].begin();
            if(vals[ep].size() == k || (vals[ep][k] > lastv && k > 0)) k--;
            inters[i].pb(inters[ep][k]), vals[i].pb(max(lastv, vals[ep][k]) + 1);
        }
    }

    //cout << strnl(inters) << strnl(vals) << endl;

    ll s = 0;
    for(int i = 0; i < N; i++) {
        s += vals[i][0];
        for(int k = 1; k < inters[i].size(); k++)
            s += (inters[i][k] - inters[i][k - 1]) * vals[i][k];
    }
    cout << s << endl;
}