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

inline int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }

using mat = array<array<int, 20>, 20>;

const int MOD = 1e9 + 7;

int N, K;
int srq[17][50000][20];
vector<int> A;

int query(int L, int R) {
    if(L == R) return 1; 
    int i = lg(R ^ L);
    int cnt = 0, sum = 0;
    for(int x = 0; x < 20; x++)
        sum = (sum + srq[i][L][x]) % MOD, cnt = (cnt + (ll)sum * (ll)srq[i][R][x] + srq[i][L][x] + srq[i][R][x]) % MOD;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("nondec.in", "r", stdin);
    freopen("nondec.out", "w", stdout);

    cin >> N >> K;
    A.resize(N), cin >> A;
    for(int& v : A) v--;
    
    mat last{}, nlast{};
    for(int k = 1; k <= N; k++) {
        // cool trick!
        int rad = 1, i = 0; while(k % (2 * rad) == 0) rad *= 2, i++;
        last = {}, nlast = {};
        for(int j = k - 1; j >= k - rad; j--) {
            for(int x = A[j]; x < 20; x++)
                for(int y = x; y < 20; y++)
                    nlast[A[j]][y] = (nlast[A[j]][y] + last[x][y]) % MOD;
            nlast[A[j]][A[j]]++;
            for(int y = 0; y < 20; y++)
                for(int x = y; x >= 0; x--)
                    srq[i][j][y] = (srq[i][j][y] + nlast[x][y]) % MOD;
            last = nlast;
        }
        last = {}, nlast = {};
        for(int j = k; j < N && j < k + rad; j++) {
            for(int y = A[j]; y >= 0; y--)
                for(int x = y; x >= 0; x--)
                    nlast[x][A[j]] = (nlast[x][A[j]] + last[x][y]) % MOD;
            nlast[A[j]][A[j]]++;
            for(int x = 0; x < 20; x++)
                for(int y = x; y < 20; y++)
                    srq[i][j][x] = (srq[i][j][x] + nlast[x][y]) % MOD;
            last = nlast;
        }
    }

    int Q; cin >> Q;
    for(int i = 0; i < Q; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        cout << query(a, b) + 1 << '\n';
    }
}