#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
    int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
};


int main() {
    int N;
    cin >> N;
    vector<int> b(N + 1);
    for(int i = 1; i <= N; i++) cin >> b[i];
    ll a = 0;
    BIT bit(N);
    for(int i = 1; i <= N; i++) bit.add(i, 1);
    vector<int> last(N + 1, 0);
    for(ll i = 1; i <= N; i++) {
        if(last[b[i]] > 0)
            bit.add(last[b[i]], -1);
        a += bit.sum(i - 1) - bit.sum(last[b[i]]);
        last[b[i]] = i;
    }
    cout << a << endl;
}