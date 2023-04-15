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
// sparse table (works on operations where a * a * b = b)
template<class T, T comb(T, T)>
struct SPT : vector<vector<T>> {
    SPT(vector<T>& v) : vector<vector<T>>(lg(v.size()) + 1, vector<T>(v.size())) {
        (*this)[0] = v;
        for (int i = 0; i < lg(v.size()); i++)
            for (int j = 0; j <= v.size() - (1 << (i + 1)); j++)
                (*this)[i + 1][j] = comb((*this)[i][j], (*this)[i][j + (1 << i)]);
    }
    T query(int L, int R) {
        int i = lg(R - L + 1);
        return comb((*this)[i][L], (*this)[i][R - (1 << i) + 1]);
    }
};

pair<int, int> sptmax(pair<int, int> x, pair<int, int> y) { return max(x, y); }

void testcase(SPT<pair<int, int>, sptmax>& spt) {
    int l, r; cin >> l >> r;
    cout << spt.query(l, r).second << endl;
}


int main() {
    vector<pair<int, int>> luck(1e6 + 1);
    for(int i = 1; i <= 1e6; i++) {
        int mn = 9, mx = 0;
        for(char c : str(i)) {
            mn = min(mn, c - '0');
            mx = max(mx, c - '0');
        }
        luck[i] = {mx - mn, i};
    }
    SPT<pair<int, int>, sptmax> spt(luck);
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase(spt);
}