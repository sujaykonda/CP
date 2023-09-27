#include <cplib/math/mint.h>
using namespace std;

const int MOD = 998244353;

int main() {
    int n, k; rd(n, k);
    mint<MOD> invk = 1 / k;
    vector<vector<mint<MOD>>> cnt(n + 1, vector<mint<MOD>>(k + 1)), sm(n + 1, vector<mint<MOD>>(k + 1));
    cnt[0][0] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            cnt[i + 1][j + 1] += cnt[i][j] * (k - j);
            sm[i + 1][j + 1] += sm[i][j] * (k - j);
        }
        mint<MOD> suffcnt, suffsm;
        for(int j = k - 1; j >= 1; j--) {
            suffcnt += cnt[i][j];
            suffsm += sm[i][j];
            cnt[i + 1][j] += suffcnt;
            sm[i + 1][j] += suffsm;
        }
        cnt[i + 1][0] += cnt[i + 1][k];
        sm[i + 1][0] += cnt[i + 1][k] + sm[i + 1][k];
    }
    mint<MOD> ans;
    for(int i = 0; i < k; i++) ans += sm[n][i];
    cout << ans << endl;
}