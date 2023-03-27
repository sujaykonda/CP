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


int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;
        vector<int> pos;
        while(k > 0) {
            for(int i = n; i >= 1; i--) {
                if((i * (i + 1)) / 2 <= k) {
                    pos.push_back(i);
                    k -= (i * (i + 1)) / 2;
                    break;
                }
            }
        }
        vector<int> a(n, -1000);
        int j = 0;
        for(int s : pos) {
            for(int i = 0; i < s; i++, j++)
                a[j] = 1;
            j++;
        }
        for(int i : a)
            cout << i << " ";
        cout << endl;
    }
}