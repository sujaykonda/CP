#include <bits/stdc++.h>
using namespace std;
const int MX = 15001;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N; cin >> N;
    vector<int> A(N);
    int sm = 0;
    for(int i = 0; i < N; i++) {
        cin >> A[i]; 
        sm += A[i];
    }
    vector<int> cnt(sm + 1);
    for(int ai : A) cnt[ai]++;
    vector<bitset<MX>> lim(sm + 1);
    lim[0][0] = 1;
    int limsm = 0, left = N;
    for(int i = 1; i <= sm; i++) {
        lim[i] = lim[i - 1];
        for(int j = limsm + 1; j <= limsm + left; j++) {
            lim[i][j] = 1;
        }
        limsm += left;
        left -= cnt[i];
    }
    int M; cin >> M;
    vector<int> B(M);
    for(int i = 0; i < M; i++) cin >> B[i];

    
    vector<bitset<MX>> dp(sm + 1);
    dp[0][0] = 1;
    for(int i = M - 1; i >= 0; i--) {
        for(int j = 0; j * B[i] < sm; j++) {
            dp[j + 1] |= (dp[j] << B[i]) & lim[j + 1];
        }
    }
    int best = -1;
    for(int i = 0; i <= sm; i++) {
        if(dp[i][sm]) {
            best = i;
            break;
        }
    }
    cout << best << endl;
    if(best != -1) {
        vector<int> c;
        int curi = best, curj = sm, last = 0;
        while(curi > 0) {
            curi--;
            for(int j = last; j < M; j++) {
                if(dp[curi][curj - B[j]]) {
                    curj -= B[j];
                    c.push_back(B[j]);
                    last = j;
                    break;
                }
            }
        }
        set<pair<int, int>> s;
        for(int i = 0; i < N; i++) s.insert({A[i], i});
        for(int i = best - 1; i >= 0; i--) {
            auto p = s.rbegin();
            vector<int> changed;
            cout << c[i] << " ";
            for(int j = 0; j < c[i]; j++) {
                cout << (*p).second + 1 << " ";
                changed.push_back((*p).second);
                p++;
            }
            for(int j : changed) {
                s.erase({A[j], j});
                s.insert({--A[j], j});
            }
            cout << endl;
        }
        for(int i = 0; i < N; i++) assert(A[i] == 0);
    }
}