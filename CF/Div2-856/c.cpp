#include <bits/stdc++.h>
using namespace std;

void testcase() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    
    vector<int> s(n);
    int j = n - 2;
    for(int i = n - 1; i >= 0; i--) {
        while(j >= 0 && a[j] >= (i - j + 1)) j--;
        s[i] = i - j;
    }
    for(int i = 0; i < n; i++)
        cout << s[i] << " ";
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) testcase();
}