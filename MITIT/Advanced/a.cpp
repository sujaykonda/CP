#include <cplib/general.h>
using namespace std;

int main() {
    int Q; rd(Q);
    vector<int> v; v.pb(0);
    while(Q--) {
        int T; rd(T);
        if(T == 1) {
            int m, k; rd(m, k);
            v.pb((k%2)?m:0);
        } else if(T == 2) {
            int x, y; rd(x, y);
            v.pb(v[x]^v[y]);
        } else if(T == 3) {
            int x, m, k; rd(x, m, k);
            v.pb((k%2)?(v[x]^m):v[x]);
        } else if(T == 4) {
            int x; rd(x);
            cout << v[x] << endl;
        }
    }
}