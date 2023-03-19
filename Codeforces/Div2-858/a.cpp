#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        int dy = d - b;
        int dx = c - a;
        if(dx > dy || dy < 0) cout << -1 << endl;
        else cout << dy + dy - dx << endl; 
    }
}