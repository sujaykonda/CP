#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2'000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();
    vector<int> last(n);
    for(int i = 0; i < n; i++) {
        vector<int> cur(n);
        for(int j = 0; j < n; j++) {
            cur[j] = inf.readInt(1, 3, "c");
            if(cur[j] == 2 && last[j] == 2) {
                cout << "INVALID GARDEN VERTICALLY ADJACENT WELLS" << endl;
                return 1;
            }
            if(j < n - 1) {
                inf.readSpace();
            }
        }
        last = cur;
        inf.readEoln();
    }
    inf.readEof();

}