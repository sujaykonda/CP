#include <cplib/general.h>
using namespace std;

void testcase() {
    int x, k; rd(x), rd(k);
    if(x % k == 0) cout << "2\n" << x - 1 << " " << 1 << endl;
    else cout << "1\n" << x << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}