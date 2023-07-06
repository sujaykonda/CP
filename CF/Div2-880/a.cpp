#include <cplib/general.h>
using namespace std;

int pow(int a, int b) {
    int x = 1;
    for(int i = 0; i < b; i++) x *= a;
    return x;
}

void tc() {
    int A, B, C; ll k;
    cin >> A >> B >> C >> k;
    int av = pow(10, A - 1);
    while(av < pow(10, A) && k > 0){ 
        if(min(pow(10, C) - av, pow(10, B)) - max(pow(10, B - 1), pow(10, C - 1) - av) >= 0) {
            k -= min(pow(10, C) - av, pow(10, B)) - max(pow(10, B - 1), pow(10, C - 1) - av);
        }
        av++;
    }
    if(k > 0) {
        cout << -1 << endl;
    } else {
        av--;
        int bv = min(pow(10, C) - av, pow(10, B)) + k - 1;
        cout << av << " + " << bv << " = " << av + bv << endl;
    }
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}