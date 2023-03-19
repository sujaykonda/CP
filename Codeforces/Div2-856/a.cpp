#include <bits/stdc++.h>
using namespace std;

int cmp(const string& a, const string& b) {
    return a.size() < b.size();
}

void testcase() {
    int n;
    cin >> n;
    vector<string> a(2 * n - 2);
    for(int i = 0; i < 2 * n - 2; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end(), cmp);
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < a[2 * i].size(); j++)
            if(a[2 * i][j] != a[2 * i + 1][a[2 * i].size() - j - 1]) {
                cout << "NO" << endl;
                return;
            }
    }
    cout << "YES" << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) testcase();
}