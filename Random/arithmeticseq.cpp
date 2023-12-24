#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }

template<class T, T comb(T, T)>
struct SRQ {
    std::vector<T> v;
    std::vector<std::vector<T>> tab;
    SRQ(std::vector<T>& v) : v(v), tab(lg(v.size()) + 1, std::vector<T>(v.size())) {
        for(int k = 1; k <= v.size(); k++) {
            // cool trick!
            int rad = k&-k, i = lg(rad); 
            tab[i][k - 1] = T(v[k - 1]);
            for(int j = k - 2; j >= k - rad; j--)
                tab[i][j] = comb(v[j], tab[i][j + 1]);
            if(k < v.size()) tab[i][k] = v[k];
            for(int j = k + 1; j < v.size() && j < k + rad; j++)
                tab[i][j] = comb(tab[i][j - 1], v[j]); 
        }
    }
    T query(int L, int R) {
        if(L == R) return v[L]; int i = lg(R ^ L);
        return comb(tab[i][L], tab[i][R]);
    }
};

int srqmn(int a, int b) { return min(a, b); }
int srqgcd(int a, int b) { return gcd(a, b); }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n; cin >> n;
    int m; cin >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> d(n - 1);
    for(int i = 0; i < n - 1; i++) d[i] = a[i + 1] - a[i];
    vector<int> next(n);
    map<int, int> mp;
    for(int i = 0; i < n; i++) {
        if(mp.find(a[i]) != mp.end()) {
            next[mp[a[i]]] = i;
        }
        mp[a[i]] = i;
    }
    for(auto [u, v] : mp) next[v] = n;
    vector<ll> p(n + 1);
    for(int i = 1; i <= n; i++) p[i] = p[i - 1] + a[i - 1];
    SRQ<int, srqmn> mnrq(a);
    SRQ<int, srqgcd> gcdrq(d);
    SRQ<int, srqmn> duprq(next);
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        int mn = mnrq.query(l, r);
        ll sm = p[r + 1] - p[l];
        int d = gcdrq.query(l, r - 1);
        int sz = r - l + 1;
        if((ll)sz * mn + d * ((ll)sz * (sz - 1)) / 2 == sm) {
            if(d != 0 && duprq.query(l, r) <= r) {
                cout << "NO ";
            } else {
                cout << "YES ";
            }
        } else {
            cout << "NO ";
        }
    }
    cout << endl;
}