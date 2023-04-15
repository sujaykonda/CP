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

const string nullstr = "-";
void testcase() {
    string l, r; cin >> l >> r;
    if(l.size() < r.size()) {
        string ans = "";
        for(int i = 0; i < l.size(); i++) ans.push_back('9');
        cout << ans << endl;
        return;
    }
    array<array<array<string, 4>, 10>, 10> olddp;
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            for(int k = 0; k < 4; k++)
                olddp[i][j][k] = nullstr;
    olddp[9][0][0] = "";
    array<array<array<string, 4>, 10>, 10> dp;
    for(int d = 0; d < l.size(); d++) {
        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 10; j++)
                for(int k = 0; k < 4; k++)
                    dp[i][j][k] = nullstr;
        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 10; j++)
                for(int k = 0; k < 4; k++)
                    if(olddp[i][j][k] != nullstr)
                        for(char c = '0'; c <= '9'; c++) {
                            int needs = (c > r[d]) * 2 + (c < l[d]);
                            if((k | needs) == k) {
                                int nk = (c < r[d]) * 2 + (c > l[d]);
                                dp[min(i, c - '0')][max(j, c - '0')][k | nk] = olddp[i][j][k] + c;
                            }
                        }
        olddp = dp;
    }
    int diff = 10;
    string best;
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            for(int k = 0; k < 4; k++)
                if(olddp[i][j][k] != nullstr)
                    if(j - i < diff)
                        best = olddp[i][j][k], diff = j - i;
    cout << best << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}