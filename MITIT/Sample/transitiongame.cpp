#include <cplib/general.h>
using namespace std;

int main() {
    int N; rd(N);
    vector<int> A(N); rd(A);
    vector<int> B(N, -1);
    int ans = 0;
    for(int i = 0; i < N; i++) {
        if(B[i] == -1) {
            int x = i;
            do {
                B[x] = i;
                x = A[x] - 1;
            } while(B[x] == -1);
            if(B[x] != i) {
                continue;
            }
            int y = x;
            do {
                x = A[x] - 1;
                ans++;
            } while(y != x);
        }
    }
    cout << ans << endl;
}