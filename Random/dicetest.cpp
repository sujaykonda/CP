#include <cplib/general.h>
using namespace std;

int main() {
    int n; rd(n);
    vector<array<map<int, int>, 2>> dp(n + 1);
    dp[0][0][0] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 1; i + j <= n; j++) {
            for(auto [u, v] : dp[i][0]) {
                dp[i + j][1][u + j * j] += v;
            }
            for(auto [u, v] : dp[i][1]) {
                dp[i + j][0][u - j * j] += v;
            }
        }
    }
    //cout << str(dp) << endl;
    for(int i = 0; i < n; i++) cout << (dp[i][0][0] + dp[i][1][0]) << ", ";
    cout << endl;
}