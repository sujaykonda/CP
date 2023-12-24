#include <cplib/general.h>
using namespace std;

int main() {
    int N, K; cin >> N >> K;
    if(K >= N / 2 && K < N) {
        if(K == N - 1) {
            for(int i = 0; i < N; i++) cout << (i % 2 ? ")" : "(");
            cout << endl;
        } else {
            string p = "";
            for(int i = 0; i < N / 4 - (K - N / 2 + (N % 4 == 2)) / 2; i++) {
                p += "(";
            }
            for(int i = 0; i < (K - N / 2 + (N % 4 == 2)) / 2; i++) {
                p += "()";
            }
            string rp = p;
            reverse(rp.begin(), rp.end());
            string s = (N % 4 == 2 ? "(" : "") + p + (K % 2 == 1 ? ")" : "") + rp;
            while(s.size() < N) s += ")";
            cout << s << endl;
        }

    } else {
        cout << -1 << endl;
    }
}