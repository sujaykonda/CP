#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    string s; rd(s);
    int sm = 0;
    for(char c : s) sm += c - '0';
    if(((ll)sm * m) % n != 0) {
        cout << -1 << endl;
        return;
    }
    int csm = 0;
    for(int i = 0; i < m - 1; i++) {
        csm += s[i] - '0';
    }
    int tar = ((ll)sm * m) / n;
    for(int i = 0; i <= n - m; i++) {
        csm += s[i + m - 1] - '0';
        if(csm == tar) {
            cout << 1 << endl;
            cout << i + 1 << " " << i + m << endl;
            return;
        }
        csm -= s[i] - '0';
    }
    int invm = n - m;
    csm = 0;
    for(int i = 0; i < invm - 1; i++) {
        csm += s[i] - '0';
    }
    int invtar = ((ll)sm * invm) / n;
    for(int i = 0; i <= n - invm; i++) {
        csm += s[i + invm - 1] - '0';
        if(csm == invtar) {
            cout << 2 << endl;
            cout << 1 << " " << i << endl;
            cout << i + invm + 1 << " " << n << endl;
            return;
        }
        csm -= s[i] - '0';
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}