#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(char& c) { return string(1, c); } string str(_Bit_reference& b) { return b ? "T" : "F"; }
string str(int& x) { return to_string(x); } string str(ll& x) { return to_string(x); }
template<class T> string str(T& a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U>& p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S>& a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T& a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T& a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }
int n, m;
vector<vector<bool>> grid;
vector<vector<bool>> done;
vector<int> xs, xe, ys, ye;
void fill() {
    for(int p = 0; p < n + m; p++) {
        for(int i = 0; i < n; i++) {
            int l = m, r = 0;
            for(int j = 0; j < m; j++)
                if(grid[i][j]) l = min(l, j), r = max(r, j);
            for(int j = 0; j < m; j++)
                if(l <= j && j <= r)
                    grid[i][j] = true;
        }
        for(int j = 0; j < m; j++) {
            int l = n, r = 0;
            for(int i = 0; i < n; i++)
                if(grid[i][j]) l = min(l, i), r = max(r, i);
            for(int i = 0; i < n; i++)
                if(l <= i && i <= r)
                    grid[i][j] = true;
        }
    }
}

void ff(int i, int j) {
    if(i < 0 || j < 0 || i >= n || j >= m || !grid[i][j] || done[i][j]) return;
    done[i][j] = true;
    xs.back() = min(i, xs.back()), xe.back() = max(i, xe.back());
    ys.back() = min(j, ys.back()), ye.back() = max(j, ye.back());
    ff(i - 1, j), ff(i + 1, j), ff(i, j - 1), ff(i, j + 1);
}

void make_path(int x1, int y1, int x2, int y2) {
    if(y1 < y2) {
        for(int y = y1; y <= y2; y++) {
            grid[x2][y] = true;
        }
    } else {
        for(int y = y2; y >= y1; y--) {
            grid[x2][y] = true;
        }
    }
    if(x1 < x2) {
        for(int x = x1; x <= x2; x++) {
            grid[x][y1] = true;
        }
    } else {
        for(int x = x1; x >= x2; x--) {
            grid[x][y1] = true;
        }
    }
}

void testcase() {
    cin >> n >> m;
    grid = vector<vector<bool>>(n, vector<bool>(m));
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++)
            grid[i][j] = s[j] == '#';
    }
    // apply filling
    fill();
    // find bounding box of cities
    done = vector<vector<bool>>(n, vector<bool>(m));
    xs.clear(), xe.clear(), ys.clear(), ye.clear();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(grid[i][j] && !done[i][j]) {
                xs.pb(i), xe.pb(i), ys.pb(j), ye.pb(j);
                ff(i, j);
            }
    if(xs.size() == 2) {
        // connect cities
        if(xe[0] < xs[1]) {
            if(ye[0] < ys[1]) {
                make_path(xe[0], ye[0], xs[1], ys[1]);
            } else {
                make_path(xe[0], ys[0], xs[1], ye[1]);
            }
        } else {
            if(ye[0] < ys[1]) {
                make_path(xs[0], ye[0], xe[1], ys[1]);
            } else {
                make_path(xs[0], ys[0], xe[1], ye[1]);
            }
        }
        // apply filling
        fill();
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            if(grid[i][j]) cout << "#";
            else cout << ".";
        cout << endl;
    }
    cout << endl;
}

int main() {
    int t; cin >> t;
    while(t--) testcase();
}