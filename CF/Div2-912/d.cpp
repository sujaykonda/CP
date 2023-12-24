#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
#include <cplib/bs.h>
using namespace std;

int main() {
    int n, q; rd(n, q);
    vector<ll> a(n); rd(a);
    vector<vector<ll>> b(20, vector<ll>(n));
    vector<vector<ll>> p(20, vector<ll>(n + 1));
    for(int i = 19; i >= 0; i--) {
        vector<int> cnt(1 << (i + 1));
        for(int j = 0; j < n; j++) {
            cnt[a[j] % (1LL << (i + 1))]++;
        }
        int k = 0;
        for(int j = 0; j < cnt.size(); j++) {
            while(cnt[j] > 0) {
                b[i][k++] = j;
                cnt[j]--;
            }
        }
        for(int j = 0; j < n; j++) {
            p[i][j + 1] = p[i][j] + b[i][j];
        }
    }

    vector<int> ls(60);
    for(int i = 0; i < 60; i++) {
        ls[i] = lower_bound(b[min(i, 19)].begin(), b[min(i, 19)].end(), (1LL << i)) - b[min(i, 19)].begin();
    }
    for(int i = 0; i < q; i++) {
        ll k; rd(k);
        bool notzero = false;
        for(int j = 59; j >= 0; j--) {
            int z = min(19, j);
            if((__int128_t) (1LL << j) * ls[j] - p[z][ls[j]] <= k) {
                int l = bsmax(ls[j], n, [&] (int x) { 
                    return (__int128_t) ((x == 0) ? (1LL << j) : b[z][x - 1]) * x - p[z][x] <= k; 
                });
                cout << bsmax((l == 0) ? (1LL << j) : b[z][l - 1], (l == n) ? ((1LL << (j + 1)) - 1) : b[z][l], [&] (ll x) {
                    return (__int128_t) x * l - p[z][l] <= k;
                }) << endl;
                notzero = true;
                break;
            }
        }
        if(!notzero) {
            cout << 0 << endl;
        }
    }
}