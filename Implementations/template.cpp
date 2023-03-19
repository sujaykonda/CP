#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include "mat.h"
#include "modint.h"
using namespace __gnu_pbds;
using namespace std;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; s.pop_back(), s.pop_back(), s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }


const int MOD = 1000000007;

int main() {
    Mat<mint<MOD>> mat({{mint<MOD>(2), mint<MOD>(5)}, {mint<MOD>(1), mint<MOD>(4)}});
    map<Mat<mint<MOD>>, int> mp;
    mp[mat]++;
    mat = pow(mat, 1000000000000000000);
    mp[mat]++;
    cout << strnl(mp) << endl;
}