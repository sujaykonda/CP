#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MXN = 300;
const ll INF = 1e17;
#define getbit(mask, i) ((mask & (1LL << i)) > 0)

void upd(ll& x, ll y) {
    x = min(x, y);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N, K; cin >> N >> K;
    vector<int> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];
    vector<int> x(K + 2);
    x[0] = -1;
    for(int i = 1; i <= K; i++) cin >> x[i], x[i]--;
    x[K + 1] = N;
    vector<int> sa;
    for(int i = 0; i < N; i++) {
        bool bad = false;
        for(int j = 0; j <= K; j++) {
            if(x[j] == i) bad = true;
        }
        if(!bad) sa.push_back(a[i]);
    }
    sort(sa.begin(), sa.end());

    N = sa.size();
    vector<vector<ll>> dp(1 << (K + 1), vector<ll>(N + 1, INF));
    for(int i = 0; i <= N; i++) dp[0][i] = 0;
    
    auto compute_trans = [&] (int k, int mn, int mx) {
        if(k == 0 && k == K) {
            return -mn;
        }
        if(k == 0) {
            return min(max(0, a[x[1]] - mn), max(mx, a[x[1]]) - mn);
        } else if(k == K) {
            return min(max(0, a[x[K]] - mn), max(mx, a[x[K]]) - mn);
        } else {
            return max(0, min(a[x[k + 1]], a[x[k]]) - mn) + max(mx, max(a[x[k + 1]], a[x[k]]));
        }
    };
    vector<int> sm(1 << (K + 1));
    for(int msk = 1; msk < (1 << (K + 1)); msk++) {
        for(int k = 0; k <= K; k++) {
            if(getbit(msk, k)) {
                sm[msk] += x[k + 1] - x[k] - 1;
            }
        }
        for(int i = 0; i <= N - sm[msk]; i++) {
            for(int msk2 = (msk-1)&msk; msk2 > 0; msk2 = (msk2-1)&msk) {
                upd(dp[msk][i], dp[msk2][i] + dp[msk^msk2][i + sm[msk2]]);
            }
        }
        for(int k = 0; k <= K; k++) {
            if(getbit(msk, k)) {
                int dx = x[k + 1] - x[k] - 1;
                int mskk = msk ^ (1 << k);
                if(dx == 0) {
                    for(int i = 0; i <= N - sm[msk]; i++) {
                        if(k == 0 || k == K)
                            upd(dp[msk][i], dp[mskk][i]);
                        else
                            upd(dp[msk][i], dp[mskk][i] + max(a[x[k + 1]], a[x[k]]));
                    }
                } else {
                    for(int i = 0; i <= N - sm[msk]; i++) {
                        upd(dp[msk][i], dp[mskk][i] + compute_trans(k, sa[i + sm[msk] - dx], sa[i + sm[msk] - 1]));
                        upd(dp[msk][i], dp[mskk][i + dx] + compute_trans(k, sa[i], sa[i + dx - 1]));
                    }
                    if(dx > 1) {
                        set<ll> st;
                        for(int i = 0; i < dx - 1; i++) {
                            st.insert(dp[mskk][i]);
                        }
                        for(int i = 0; i <= N - sm[msk]; i++) {
                            st.erase(dp[mskk][i]);
                            st.insert(dp[mskk][i + dx - 1]);
                            upd(dp[msk][i], *st.begin() + compute_trans(k, sa[i], sa[i + sm[msk] - 1]));
                        }
                    }
                }
            }
        }
    }
    ll best = dp[(1 << (K + 1)) - 1][0];
    for(int i : sa) best += i;
    cout << best << endl;
}