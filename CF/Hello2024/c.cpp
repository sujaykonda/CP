#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    a.resize(unique(a.begin(), a.end()) - a.begin());
    n = a.size();
    int b = 1e9;
    int c = 1e9;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(b < a[i] && c < a[i]) {
            ans++;
            if(b < c) b = a[i];
            else c = a[i];
        } else if(b < a[i]) c = a[i];
        else if(c < a[i]) b = a[i];
        else if(b < c) b = a[i];
        else c = a[i]; 
    }
    cout << ans << endl;

}
 
int main() {
    int t; rd(t);
    while(t--) tc();
}