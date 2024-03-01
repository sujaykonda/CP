#include <cplib/general.h>
using namespace std;

const int MX = 2e5 + 1;
const int SQRTMX = 640;
pair<int, int> dp[MX];

int main() {
    int t; cin >> t;
    dp[0] = {0, -1};
    for(int i = 1; i < MX; i++) {
        int sm = 1;
        dp[i] = {1e9, 1e9};
        for(int j = 2; sm <= i; j++) {
            dp[i] = min(dp[i], {j + dp[i - sm].first, j - 1});
            sm += j;
        }
    }
    auto tc = [&] () {
        ll n, x, y, s;
        cin >> n >> x >> y >> s;
        ll m = (x % y);
        s -= m * n;
        if(s % y != 0 || s < 0) {
            cout << "NO" << endl;
        } else {
            s /= y;
            x /= y;
            vector<int> cur;
            cur.push_back(x);
            s -= x;
            while(s >= 0) {
                if(cur.size() + dp[s].first <= n) {
                    while(cur.size() + dp[s].first < n) cur.push_back(0);
                    while(s > 0) {
                        int ns = s;
                        for(int i = 0; i <= dp[s].second; i++) {
                            cur.push_back(i);
                            ns -= i;
                        }
                        s = ns;
                    }
                    cout << "YES" << endl;
                    for(int i : cur) cout << i * y + m << " ";
                    cout << endl;
                    return;
                }
                x++;
                cur.push_back(x);
                s -= x;
            }
            cout << "NO" << endl;
        }
    };
    while(t--) tc();
}