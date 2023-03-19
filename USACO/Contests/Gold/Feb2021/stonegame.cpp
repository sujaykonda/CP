#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxa = 1000001;
int main() {
    vector<int> cnt(maxa);
    int N;
    cin >> N;
    for(int i = 0; i < N; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }
    vector<int> P(maxa);
    for(int i = 1; i < maxa; i++) {
        P[i] = cnt[i] + P[i - 1];
    }
    
    ll ans = 0;
    for(int i = 1; i < maxa; i++) {
        vector<int> piles(maxa / i + (maxa % i != 0));
        int ocnt = 0;
        for(int j = 0; j < piles.size(); j++) {
            piles[j] = P[min(maxa, i * (j + 1)) - 1] - P[max(i * j - 1, 0)];
            if(j != 0)
                ocnt += piles[j] % 2;
        }
        if(ocnt == 1 && piles[1] % 2 == 1) {
            ans += piles[1];
        } else if(ocnt == 2) {
            for(int j = 2; j < piles.size(); j++) {
                if(piles[j] % 2 == 1 && piles[j - 1] % 2 == 1) {
                    ans += piles[j];
                    break;
                }
            }
        }
    }
    cout << ans << endl;
}