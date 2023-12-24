#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int k = 0;
    while(n % 2 == 0) n /= 2, k++;
    if(n == 1) {
        cout << 1 << " " << k << endl;
        return;
    }
    vector<int> cycle = {1};
    while((cycle.back() * 2) % n != 1) {
        cycle.push_back((cycle.back() * 2) % n);
    }
    
}