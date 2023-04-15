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

void apply(int a, int b, int& c, int d, int v) {
    int m;
    if(v < 0)
        m = min({-v, d, a - c});
    else
        m = -min({v, c, b - d});
    c += m;
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    vector<vector<int>> ans(a + 1, vector<int>(b + 1));
    for(int cd = 0; cd <= a + b; cd++) {
        int sm = 0;
        int mnc = max(0, cd - b), mxc = min(a, cd);
        int l = mnc, r = mxc;
        for(int vi : v) {
            sm += vi;
            l = max(l, mnc + sm);
            r = min(r, mxc + sm);
        }
        int resmn = mnc, resmx = mxc;
        for(int vi : v) {
            apply(a, b, resmn, cd - resmn, vi);
            apply(a, b, resmx, cd - resmx, vi);
        }

        for(int c = mnc; c <= l && c <= mxc; c++)
            ans[c][cd - c] = resmn;
        for(int c = l + 1; c < r; c++)
            ans[c][cd - c] = c - sm;
        for(int c = mxc; c >= r && c >= mnc; c--)
            ans[c][cd - c] = resmx;
    }
    for(int i = 0; i <= a; i++) {
        for(int j = 0; j <= b; j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }
}