#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, T;
    cin >> N >> T;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i], A[i] %= T;
    sort(A.begin(), A.end());
    int mx = A.back();
    int best = 1e9;
    for(int i = 0; i < N; i++) {
        best = min(best, (mx - A[i] + 1) / 2);
        mx = A[i] + T;
    }
    cout << best << endl;
}