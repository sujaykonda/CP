#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    int pw = 0;
    priority_queue<int> pq;
    for(int i = 0; i < n - 1; i++) {
        pq.push(abs(a[i + 1] - a[i]));
        pw += abs(a[i + 1] - a[i]);
    }
    for(int i = 0; i < k - 1; i++) {
        pw -= pq.top(); pq.pop();
    }
    cout << pw << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}