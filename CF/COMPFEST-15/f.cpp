#include <cplib/general.h>
using namespace std;
const int BSZ = 300;
const int MX = 1e5;
int N; 

void solve(vector<int>& A, vector<int>& B, int q) {
    
    vector<int> cntA(MX + 1), cntB(MX + 1);
    for(int i = 0; i < N; i++) cntA[A[i]]++;
    for(int i = 0; i < N; i++) cntB[B[i]]++;
    vector<int> fA(MX + 1), fB(MX + 1);
    int Asm = 1, Bsm = 1;
    for(int i = MX - 1; i >= 0; i--) {
        fA[i] = Asm;
        fB[i] = Bsm;

        Asm += cntA[i];
        Bsm += cntB[i];
    }
    vector<int> cntO(MX + 1);
    for(int i = 0; i < N; i++) cntO[fA[A[i]] + fB[B[i]]]++;
    vector<int> fO(MX + 1);
    int Osm = 1;
    for(int i = 0; i <= MX; i++) {
        fO[i] = Osm;
        Osm += cntO[i];
    }

    vector<bool> mod(N);
    vector<pair<int, int>> queries(q);
    for(int i = 0; i < q; i++) {
        rd(queries[i].first, queries[i].second);
        if(queries[i].first < 3) {
            mod[queries[i].second] = true;
            string s; rd(s);
            if(s[0] == '-') queries[i].second *= -1;
        }
    }

    for(int i = 0; i < N; i++) {
        if(!mod[i]) {
            
        }
    }
}

int main() {
    rd(N);
    vector<int> A(N); rd(A);
    vector<int> B(N); rd(B);
    int Q; rd(Q);
    for(int i = 0; i < Q / BSZ; i++) {
        solve(A, B, min(Q, i * BSZ + BSZ) - i * BSZ);
    }
}