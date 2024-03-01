#include <cplib/general.h>
using namespace std;

int main() {
    int N; rd(N);
    vector<int> X(5 * N); rd(X);
    ll sm = 0;
    sort(X.begin(), X.end());
    for(int i = N; i < 4 * N; i++) sm += X[i];
    cout << setprecision(20) << endl;
    cout << (double) sm / (3 * N) << endl;
}