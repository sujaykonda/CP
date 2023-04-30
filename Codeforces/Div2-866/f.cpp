#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
// debug tools
string str(char c) { return string(1, c); } string str(_Bit_reference b) { return b ? "T" : "F"; }
string str(int x) { return to_string(x); } string str(ll x) { return to_string(x); }
template<class T> string str(T a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

void testcase() {
    int n, m; cin >> n >> m;

    vector<vector<int>> a(n + 1);
    // if i is empty, then next[i] can also be empty
    vector<int> next(n + 1, n + 1);
    int last = 0;
    for(int i = 1; i <= n + 1; i++) {
        int k = 0; 
        if(i <= n) cin >> k;
        if(k == 0) {
            map<int, int> mp;
            for(int j = i - 1; j > last; j--) {
                next[j - 1] = next[j];
                for(int aij : a[j]) {
                    if(mp.count(aij))
                        next[j - 1] = min(next[j - 1], mp[aij]);
                    mp[aij] = j;
                }
            }
            last = i;
        } else {
            a[i].resize(k); cin >> a[i];
        }
    }
    //cout << str(next) << endl;
    // if it is possible to be empty at i (0 ... i)
    vector<bool> dpf(n + 1);
    dpf[0] = true;
    for(int i = 0; i <= n; i++) {
        if(i != 0 && a[i].size() == 0) { 
            dpf[i] = true;
            // calculate the minimum backpack set
            set<int> mns;
            for(int j = i - 1; j > 0; j--) {
                if(dpf[j]) break;
                for(int aij : a[j])
                    mns.insert(aij);
            }

            // everything before and including the index countaining a minimum backpack set item can be cleared
            for(int j = i + 1; j <= n; j++) {
                if(j == next[i] || a[j].size() == 0) break;
                dpf[j] = true;
                bool over = false;
                for(int aij : a[j])
                    if(mns.count(aij)) over = true;
                if(over) break;
            }
        }
        if(dpf[i] && next[i] <= n) dpf[next[i]] = true;
    }
    //cout << str(dpf) << endl;

    // max size if we start empty at i (i ... n)
    vector<int> dpb(n + 1, -1);
    bool zero = false;
    set<int> s;
    for(int i = n; i >= 0; i--) {
        dpb[i] = zero ? m : s.size();
        if(a[i].size() == 0) zero = true;
        int old = s.size();
        for(int aij : a[i])
            s.insert(aij);
        if(a[i].size() + old > s.size()) break;
    }
    int best = 0;
    for(int i = 0; i <= n; i++)
        if(dpf[i])
            best = max(best, dpb[i]);
    cout << best << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    while(t--) testcase();
}