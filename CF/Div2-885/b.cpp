#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> c(n); rd(c);
    vector<priority_queue<int>> dist(k + 1);
    vector<int> last(k + 1);
    for(int i = 1; i <= n; i++) {
        dist[c[i - 1]].push(i - last[c[i - 1]] - 1);
        last[c[i - 1]] = i;
    }
    for(int i = 1; i <= k; i++)
        dist[i].push(n - last[i]);
    int best = n;
    for(int i = 1; i <= k; i++) {
        int x = dist[i].top() / 2;
        dist[i].pop();
        dist[i].push(x);
        best = min(best, dist[i].top());
    }
    cout << best << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}