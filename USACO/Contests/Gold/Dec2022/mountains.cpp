#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < tree.size()) tree[k] += x, k += k&-k; }
    int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
    int upper_bound(ll x) {
        ll s = 0, p = 0;
        for(int i = lg(tree.size()); i >= 0; i--)
            if(p + (1 << i) < tree.size() && s + tree[p + (1 << i)] <= x)
                p += (1 << i), s += tree[p];
        return p + 1;
    }
    void addsub(int k, ll x) {
        add(k, x);
        int k2 = upper_bound(sum(k));
        if(k2 < tree.size()) add(k2, -x);
    }
};




int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int N;
    cin >> N;
    vector<ll> h(N);
    for(int i = 0; i < N; i++) cin >> h[i];
    vector<BIT> bits;
    vector<int> cnt(N);
    for(int i = 0; i < N - 1; i++) {
        BIT bit(N - i - 1);
        int mx = 0;
        for(int j = 1; j < N - i; j++)
            if(mx == 0 || (h[mx + i] - h[i]) * j <= (h[j + i] - h[i]) * mx) 
                bit.add(j, j - mx), mx = j, cnt[i]++;
        bits.push_back(bit);
    }
    int Q;
    cin >> Q;
    for(int q = 0; q < Q; q++) {
        int x, y;
        cin >> x >> y;
        x--;
        h[x] += y;
        for(int i = 0; i < x; i++) {
            int s = bits[i].sum(x - i);
            if(s == x - i) cnt[i]--;
            if((h[s + i] - h[i]) * (x - i) <= (h[x] - h[i]) * s) { 
                cnt[i]++;
                bits[i].addsub(x - i, x - i - s);
                while(true) {
                    int j = bits[i].upper_bound(x - i);
                    if(j == N - i) break;
                    if((h[j + i] - h[i]) * (x - i) >= (h[x] - h[i]) * j) break;
                    bits[i].addsub(j, x - i - bits[i].sum(j));
                    cnt[i]--;
                }
            }
        }
        if(x < N - 1) {
            cnt[x] = 0;
            BIT bit(N - x - 1);
            int mx = 0;
            for(int j = 1; j < N - x; j++)
                if(mx == 0 || (h[mx + x] - h[x]) * j <= (h[j + x] - h[x]) * mx) 
                    bit.add(j, j - mx), mx = j, cnt[x]++;
            bits[x] = bit;
        }
        int s = 0;
        for(int c : cnt) s += c;
        cout << s << endl;
    }
}