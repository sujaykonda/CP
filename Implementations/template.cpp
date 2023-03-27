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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int MOD = 1000000007;
#include "rurq.h"

ll sgmax(ll a, ll b) { return max(a, b); }
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    node<10>* seg = new node<10>();
    cout << "created" << endl;
    seg->upd(5, 0, 5);
    cout << "first upd" << endl;
    seg->upd(5, 3, 9);
    cout << "second upd" << endl;
    cout << seg->query(0, 9) << endl;
}