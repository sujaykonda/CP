#include <bits/stdc++.h>
using namespace std;

const int MXN = 5000;
int main() {
    // finding the best division strategy
    vector<int> bits(MXN + 1, 1e9); bits[MXN] = 0;
    for(int i = MXN; i > 0; i--) {
        for(int j = i + 1; j >= 1; j--) {
            bits[i / j] = min(bits[i / j], bits[i] + j);
        }
    }
    cout << bits[0] << endl;
}