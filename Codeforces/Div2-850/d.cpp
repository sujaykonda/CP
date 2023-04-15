#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
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
    int m; cin >> m;
    array<array<vector<int>, 3>, 3> adj;
    for(int i = 1; i <= m; i++) {
        string s; cin >> s;
        int st = 0;
        for(char c : s) {
            if(c == 'w') st++;
            else if(c == 'i') st += 4;
            else st += 16;
        }
        st /= 3;
        
        if(st == 1) {
            // www
            adj[0][1].pb(i), adj[0][2].pb(i);
        } else if(st == 2) {
            // wwi
            adj[0][2].pb(i);
        } else if(st == 3) {
            // wii
            adj[1][2].pb(i);
        } else if(st == 4) {
            // iii
            adj[1][0].pb(i), adj[1][2].pb(i);
        } else if(st == 6) {
            // wwn
            adj[0][1].pb(i);
        } else if(st == 8) {
            // iin
            adj[1][0].pb(i);
        } else if(st == 11) {
            // wnn
            adj[2][1].pb(i);
        } else if(st == 12) {
            // inn
            adj[2][0].pb(i);
        } else if(st == 16) {
            // nnn
            adj[2][0].pb(i), adj[2][1].pb(i);
        }
    }
    int cnt = 0;
    stringstream c;
    char win[3] = {'w', 'i', 'n'};
    for(int i = 0; i < 3; i++) {
        for(int j = i + 1; j < 3; j++) {
            while(!adj[i][j].empty() && !adj[j][i].empty()) {
                cnt++;
                c << adj[i][j].back() << " " << win[i] << " " << adj[j][i].back() << " " << win[j] << endl;
                adj[i][j].pop_back(), adj[j][i].pop_back();
            }
        }
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(i == j) continue;
            for(int k = 0; k < 3; k++) {
                if(k == j || k == i) continue;
                while(!adj[i][j].empty() && !adj[j][k].empty() && !adj[k][i].empty()) {
                    cnt++;
                    c << adj[i][j].back() << " " << win[i] << " " << adj[j][k].back() << " " << win[j] << endl;
                    cnt++;
                    c << adj[j][k].back() << " " << win[i] << " " << adj[k][i].back() << " " << win[k] << endl;
                    adj[i][j].pop_back(), adj[j][k].pop_back(), adj[k][i].pop_back();
                }
            }
        }
    }

    cout << cnt << endl;
    cout << c.str() << endl;
    
}

int main() {
    int t; cin >> t;
    while(t--) testcase();
}