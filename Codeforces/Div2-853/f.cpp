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

void upd(int& x, int y) { x = max(x, y); }

int lcs2(string s1, string s2) {
    vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1));
    for(int i = 1; i <= s1.size(); i++)
        for(int j = 1; j <= s2.size(); j++) {
            if(s1[i - 1] == s2[j - 1])
                upd(dp[i][j], dp[i - 1][j - 1] + 1);
            upd(dp[i][j], dp[i - 1][j]);
            upd(dp[i][j], dp[i][j - 1]);
        }
    return 2 * dp[s1.size()][s2.size()];
}

int lcs3(string s1, string s2, string s3) {
    vector<vector<vector<int>>> dp(s1.size() + 1, vector<vector<int>>(s2.size() + 1, vector<int>(s3.size() + 1)));
    for(int i = 1; i <= s1.size(); i++)
        for(int j = 1; j <= s2.size(); j++) 
            for(int k = 1; k <= s3.size(); k++){
                if(s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1])
                    upd(dp[i][j][k], dp[i - 1][j - 1][k - 1] + 1);
                upd(dp[i][j][k], dp[i - 1][j][k]);
                upd(dp[i][j][k], dp[i][j - 1][k]);
                upd(dp[i][j][k], dp[i][j][k - 1]);
            }
    return 3 * dp[s1.size()][s2.size()][s3.size()];
}


void add(string s, vector<string>& possT) {
    for(int i = 1; i < 1 << (s.size()); i++) {
        string nw = "";
        for(int j = 0; j < s.size(); j++)
            if(getbit(i, j))
                nw += s[j];
        possT.emplace_back(nw);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    string s; cin >> s;
    
    int best = 0;

    // k = 2
    for(int i = 0; i < s.size(); i++)
        upd(best, lcs2(s.substr(0, i), s.substr(i, s.size() - i)));
    
    // k = 3
    for(int i = 0; i < s.size(); i++)
        for(int j = i + 1; j < s.size(); j++)
            upd(best, lcs3(s.substr(0, i), s.substr(i, j - i), s.substr(j, s.size() - j)));

    // k >= 5
    vector<string> possT;
    for(int i = 0; i < s.size(); i += 16) {
        add(s.substr(i, min(16, (int)s.size() - i)), possT);
    }
    for(string& T : possT) {
        int cnt = 0;
        int j = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == T[j])
                j = (j + 1) % T.size(), cnt += j == 0;
        }
        if(cnt >= 2)
            upd(best, T.size() * cnt);
    }
    cout << best << endl;
}