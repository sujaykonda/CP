#include <bits/stdc++.h>
using namespace std;

const int f(const int& n, const int& k) {
    if(n < k) return 0;
    if(n % k == 0)
        return n / k;
    int d = n / k;
    return f(n - ((n - d * k) / (d + 1) + ((n - d * k) % (d + 1) != 0)) * (d + 1), k);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int N;
    cin >> N;
    int ans = 0;
    for(int i = 0; i < N; i++) {
        int a, k;
        cin >> a >> k;
        ans ^= f(a, k);
    }
    if(ans == 0) cout << "Aoki\n";
    else cout << "Takahashi\n";
}