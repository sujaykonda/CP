#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    string str; rd(str);
    vector<int> l(n), r(n);
    for(int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        l[i]--, r[i]--;
    }
    function<int(int)> dfs = [&] (int s) {
        if(l[s] == -1 && r[s] == -1) return 0;
        int mn = 1e9;
        if(l[s] != -1) {
            mn = min(mn, dfs(l[s]) + (str[s] != 'L'));
        }
        if(r[s] != -1) {
            mn = min(mn, dfs(r[s]) + (str[s] != 'R'));
        }
        return mn;
    };
    cout << dfs(0) << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}