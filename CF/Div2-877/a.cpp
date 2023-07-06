#include <cplib/general.h>
using namespace std;

void testcase() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int num = a[0];
    for(int i = 0; i < n; i++) {
        if(a[i] < 0) num = a[i];
        if(num >= 0 && a[i] > num) num = a[i];
    }
    cout << num << nl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}