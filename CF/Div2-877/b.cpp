#include <cplib/general.h>
using namespace std;

void testcase() {
    int n; rd(n);
    vector<int> p(n); rd(p);
    int ind1 = 0, ind2 = 0, indn = 0;
    for(int i = 0; i < n; i++) {
        if(p[i] == 1) ind1 = i + 1;
        if(p[i] == 2) ind2 = i + 1;
        if(p[i] == n) indn = i + 1;
    }
    if((ind1 < indn && indn < ind2) || (ind2 < indn && indn < ind1)) {
        cout << 1 << " " << 1 << endl;
    } else if(abs(indn - ind1) < abs(indn - ind2)) {
        cout << indn << " " << ind1 << endl;
    } else {
        cout << indn << " " << ind2 << endl;
    }
    
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}