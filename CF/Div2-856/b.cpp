#include <bits/stdc++.h>
using namespace std;

void testcase() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++) {
        while(a[i] == 1 || (i > 0 && a[i] % a[i - 1] == 0)) a[i]++;
    }
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) testcase();
}