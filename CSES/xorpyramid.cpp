#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, p;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    while(n > 1) {
        p = (1 << (__builtin_clzll(1) - __builtin_clzll(n - 1))), n -= p;
        for(int i = 0; i < n; i++)
            a[i] ^= a[i + p];
    }
    cout << a[0] << endl;
}