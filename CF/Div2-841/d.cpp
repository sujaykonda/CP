#include <cplib/bs.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    vector<vector<int>> a(n, vector<int>(m)); rd(a);
    cout << bsmax(1, n, [&] (ll x) {
        vector<vector<int>> b(n + 1, vector<int>(m + 1));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                b[i + 1][j + 1] = (a[i][j] >= x) + b[i + 1][j] + b[i][j + 1] - b[i][j];
        for(int i = x; i <= n; i++) {
            for(int j = x; j <= m; j++) {
                if(b[i][j] - b[i - x][j] - b[i][j - x] + b[i - x][j - x] == x * x) {
                    return true;
                }
            }
        }
        return false;
    }) << endl;
}

int main() {
    int t; rd(t); while(t--) tc();
}