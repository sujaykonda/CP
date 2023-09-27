#include <cplib/general.h>
using namespace std;

int main() {
    int n; rd(n);
    vector<int> p(n - 1); rd(p);
    vector<int> cnt(n);
    vector<int> dep(n);
    for(int i = 0; i < n - 1; i++) cnt[p[i] - 1]++;
    for(int i = 1; i < n; i++) dep[i] = 1 + dep[p[i - 1] - 1];
    if(cnt[0] == n - 1) {
        cout << 1 << endl;
        for(int i = 0; i < n - 1; i++) cout << 1 << endl;
        cout << 1 << endl;
    } else {
        vector<int> top(n);
        for(int i = 1; i < n; i++) {
            if(p[i - 1] - 1 == 0) top[i] = i;
            else top[i] = top[p[i - 1] - 1];
        }
        bool bad = false;
        vector<int> off(n);
        for(int i = 1; i < n; i++) {
            if(cnt[i] == 1) {
                int c = (dep[i] % 2) + 1;
                if(off[top[i]] == 0) off[top[i]] = c;
                else if(off[top[i]] != c) bad = true;
            }
        }
        if(!bad) {
            cout << 2 << endl;
            for(int i = 1; i < n; i++) cout << ((off[top[i]] + dep[i]) % 2) + 1 << " ";
            cout << endl;
            while(true) {
                int done ; rd(done);
                if(done != 0) break;
                int a, b; rd(a, b);
                if(b == 1) cout << 2 << endl;
                else cout << 1 << endl;
            }
        } else {
            cout << 3 << endl;
            for(int i = 1; i < n; i++) cout << (dep[i] % 3) + 1 << " ";
            cout << endl;
            while(true) {
                int done = 0; rd(done);
                if(done != 0) break;
                int a, b, c; rd(a, b, c);
                if(a == 0) {
                    if(b == 0) {
                        cout << 3 << endl;
                    } else {
                        cout << 2 << endl;
                    }
                } else if(b == 0) {
                    if(c == 0) {
                        cout << 1 << endl;
                    } else {
                        cout << 3 << endl;
                    }
                } else {
                    cout << 1 << endl;
                }
            }
        }
    }
    
}