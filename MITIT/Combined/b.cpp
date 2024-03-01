#include <cplib/general.h>
using namespace std;

int main() {
    int N; rd(N);
    vector<int> a(N); rd(a);
    sort(a.begin(), a.end());
    cout << a[N / 2] << endl;
}