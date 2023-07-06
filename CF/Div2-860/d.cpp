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
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }

void testcase() {
    int n; cin >> n;
    stack<int> pos, neg;
    vector<int> a;
    for(int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if(ai == 0) a.push_back(0);
        else if(ai > 0) pos.push(ai);
        else neg.push(ai);
    }
    
    ll psum = 0;
    while(a.size() < n) {
        if(psum > 0)
            psum += neg.top(), a.push_back(neg.top()), neg.pop();
        else
            psum += pos.top(), a.push_back(pos.top()), pos.pop();
    }
    int mx = a[0], mn = a[0];
    for(int ai : a) mx = max(mx, ai), mn = min(mn, ai);

    ll mxsum = 0;
    ll mnpsum = 0, mxpsum = 0;
    psum = 0;
    for(int i = 0; i < n; i++) {
        psum += a[i];
        mxsum = max({mxsum, abs(mnpsum - psum), abs(mxpsum - psum)});
        mnpsum = min(mnpsum, psum);
        mxpsum = min(mxpsum, psum);
    }
    if(mxsum < mx - mn) {
        cout << "YES" << endl;
        for(int ai : a) cout << ai << " ";
        cout << endl;
        return;
    }
    cout << "NO" << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}