#include <cplib/bs.h>
using namespace std;

int main() {
    int n, m, q; rd(n, m, q);
    vector<vector<int>> v(n, vector<int>(m));
     
    while(q--) {
        int x, y; rd(x, y);
        cout << bsmax(0, min(n, m), [&] (int d) {

        }) << endl;
    }
}