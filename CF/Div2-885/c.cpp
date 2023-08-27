#include <cplib/general.h>
using namespace std;

int stepgcd(int a, int b) {
    //cout << a << " " << b << endl;
    if(a == 0) return 0;
    if(b == 0) return 1;
    if((a / b) % 2 == 0) {
        return (stepgcd(b, b - (a % b)) + 1) % 3;
    } else {
        return (stepgcd(b, a % b) + 1) % 3;
    }
}

void tc() {
    int n; rd(n);
    vector<int> a(n), b(n);
    rd(a); rd(b);
    int t = -1;
    bool good = true;
    for(int i = 0; i < n; i++) {
        if(a[i] == b[i] && a[i] == 0) continue;
        int j;
        if(a[i] > b[i]) {
            j = stepgcd(a[i], b[i]);
        } else {
            j = (stepgcd(b[i], b[i] - a[i]) + 1) % 3;
        }
        if(t == -1) t = j;
        else if(t != j) good = false;
    }
    cout << (good ? "YES" : "NO") << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}