#include <cplib/general.h>
using namespace std;

void tc() {
    int n, a, q; rd(n, a, q);
    string s; rd(s);
    int worstcase = a;
    int bestcase = a;
    int readoffline = 0;
    for(int i = 0; i < q; i++) {
        if(s[i] == '+') {
            bestcase++;
            if(readoffline > 0) {
                readoffline--;
            } else {
                worstcase++;
            }
        } else {
            readoffline++;
        }
    }
    if(bestcase >= n && worstcase < n) {
        cout << "MAYBE" << endl;
    } else if(bestcase >= n && worstcase >= n) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}