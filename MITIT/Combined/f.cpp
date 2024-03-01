#include <cplib/general.h>
using namespace std;

int main() {
    int T; rd(T);
    while(T--) {
        int N; rd(N);
        string s; rd(s);
        int p = N;
        vector<vector<int>> dp(2 * N + 1, vector<int>(N + 1, -N)); 
        vector<int> ldp(N + 1, -N);
        ldp[0] = 0;
        dp[p] = ldp;
        vector<int> best = ldp;
        for(int i = 0; i < N; i++) {
            p += s[i] == '1' ? 1 : -1;
            ldp = vector<int>(N + 1, -N);
            for(int j = 1; j <= N; j++) {
                ldp[j] = best[j - 1];
                if(i == N - 1) {
                    for(int k = 0; k < p; k++) ldp[j] = max(ldp[j], dp[k][j - 1] + 1);
                } else {
                    ldp[j] = max(ldp[j], dp[p - 1][j - 1] + 1);
                }
            }
            for(int j = 0; j <= N; j++) best[j] = max(best[j], ldp[j]);
            for(int j = 0; j <= N; j++) {
                dp[p][j] = max(dp[p][j], ldp[j]);
            }
        }
        for(int i = 1; i <= N; i++) cout << ldp[i] << " ";
        cout << endl;
    }
}