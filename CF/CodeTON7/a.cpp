#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    while(a.size() > 1) {
        int ind = 0;
        for(int i = 0; i < a.size(); i++) if(a[i] == a.size()) ind = i;
        if(ind == 0) {
            cout << "NO" << endl;
            return;
        }
        a.erase(a.begin() + ind);
    }
    cout << "YES" << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}