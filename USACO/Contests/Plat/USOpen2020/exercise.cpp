#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
const char nl = '\n';
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

typedef unsigned long long ull;
typedef __uint128_t L;

int N, M;
ull m;
int Nf;

ull reduce(ull a) {
	ull q = (ull)((L(m) * a) >> 64);
	ull r = a - q * M; // can be proven that 0 <= r < 2*b
	return r >= M ? r - M : r;
}

int solve(int d) {
    int w = 1;
    for(int i = 1; i <= N; i++)
        w = reduce((ull)w * (i - (i % d == 0)));
    w = Nf - w;
    w += (w < 0) * M;
    return w;
}

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : (fe(a * a % m, b / 2, m) * ((b % 2 ? a : 1) % m) % m); }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    cin >> N >> M; M--;
    m = ull((L(1) << 64) / M);
    Nf = 1;
    for(int i = 1; i <= N; i++) Nf = reduce((ull)Nf * i);
    vector<bool> comp(N + 1);
    int ans = 1;
    for(int i = 2; i <= N; i++) {
        if(!comp[i]) {
            int sm = 0;
            for(int d = i; d <= N; d *= i)
                sm = (sm + solve(d)) % M;
            ans = ((ll)ans * fe(i, sm, M + 1)) % (M + 1);

            for(int j = i + i; j <= N; j += i)
                comp[j] = true;
        }
    }
    cout << ans << endl;
}
