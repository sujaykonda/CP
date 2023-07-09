#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    string S, T; rd(S, T);
    int diff1 = 0, diff2 = 0;
    for(int i = 0; i < n; i++) diff1 += S[i] != T[i];
    for(int i = 0; i < n; i++) diff2 += S[i] != T[n - 1 - i];
    cout << min(2 * diff1 - (diff1 % 2), (diff2 == 0) ? 2 : (2 * diff2 - 1 + (diff2 % 2))) << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}