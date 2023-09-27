#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> p(n); rd(p);
    
    int cnt = n - 1;
    vector<bool> done(n);
    for(int i = 0; i < n; i++) {
        p[i]--;
        if(p[i] > 0 && done[p[i] - 1]) {
            cnt--;
        }
        done[p[i]] = true;
    }
    cout << cnt << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}