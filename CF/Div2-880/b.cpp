#include <cplib/general.h>
using namespace std;

int main() {
    int n, k; ll m;
    rd(n, m, k);
    vector<ll> a(n); rd(a);
    sort(a.begin(), a.end()); 
    pair<int, int> best = {0, 0};
    for(int i = 0; i < n; i++) {
        if(i > 0 && a[i] == a[i - 1]) continue;
        ll right = m + 1;
        if(i + k - 1 < n) 
            right = a[i + k - 1];
        ll left = -1;
        if(i - k >= 0)
            left = a[i - k];
        if(left == -1 && right == m + 1)
            best = max(best, {m, a[i] - 1});
        else if (left == -1)
            best = max(best, {(right - (a[i] - 1) - 1) / 2 + a[i] - 1 + 1, a[i] - 1});
        else if (right == m + 1)
            best = max(best, {(a[i - 1] + 1 - left - 1) / 2 + 1 + m - (a[i - 1] + 1), a[i - 1] + 1});
        else {
            int v = min(a[i], max(a[i - 1], (left + right) / 2));
            best = max(best, {(v - left - 1) / 2 + (right - v - 1) / 2 + 1, v});
        }
    }
    cout << best.first << " " << best.second << endl;
}