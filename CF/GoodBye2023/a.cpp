#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> b(n); rd(b);
    int c = 2023;
    for(int bi : b) {
        if(c % bi != 0) {
            cout << "NO" << endl;
            return;
        }
        c /= bi;
    }
    cout << "YES" << endl;
    cout << c << " ";
    for(int i = 0; i < k - 1; i++) cout << 1 << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}