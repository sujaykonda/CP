#include <cplib/general.h>
using namespace std;
const int INF = 1e8;
int main() {
    int n, m, k; rd(n, m, k);
    vector<int> c(n); rd(c);
    vector<vector<int>> d(2 * n, vector<int>(2 * n, INF));
    for(int i = 0; i < 2 * n; i++) d[i][i] = 0;
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b); a--, b--;
        d[a][b + (c[a] != c[b]) * n] = d[b + (c[a] != c[b]) * n][a] = 1;
        d[a + n][b + n * (c[a] == c[b])] = d[b + n * (c[a] == c[b])][a + n] = 1;
        d[a][a + n] = d[a + n][a] = k;
    }
    for(int z = 0; z < 2 * n; z++) {
        for(int i = 0; i < 2 * n; i++) {
            for(int j = i + 1; j < 2 * n; j++) {
                d[i][j] = d[j][i] = min(d[i][j], d[i][z] + d[z][j]);
            }
        }
    }
    int best = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z <= k; z++)
                best = max(best, min(z + d[i][j], k - z + d[i][j + n]));
        }
    }
    cout << best << endl;
}