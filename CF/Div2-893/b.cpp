#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m, d; rd(n, m, d);
    int x = m;
    vector<int> s(m); rd(s);
    if(s[0] == 1) {
        s.erase(s.begin());
        m--;
    }
    s.insert(s.begin(), 1);
    s.push_back(n + 1);
    int base = 0;
    for(int i = 1; i <= m + 1; i++) {
        base += (s[i] - s[i - 1] - 1) / d + 1;
    }
    int cnt = 0;
    for(int i = 1; i <= m; i++) {
        int basev = (s[i + 1] - s[i] - 1) / d + 1 + (s[i] - s[i - 1] - 1) / d + 1;
        int newv = (s[i + 1] - s[i - 1] - 1) / d + 1;
        //cout << newv << " " << basev << endl;
        if(newv + 1 == basev) cnt++;
    }
    if(cnt == 0) {
        cout << base << " " << x << endl;
    } else {
        cout << base - 1 << " " << cnt << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}