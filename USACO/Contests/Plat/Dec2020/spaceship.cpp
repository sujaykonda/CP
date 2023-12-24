#include <cplib/general.h>
using namespace std;
typedef vector<vector<int>> Mat;
const int MOD = 1e9 + 7;
using ll = long long;

Mat mult(Mat A, Mat B) {
    Mat C(A.size(), vector<int>(B[0].size()));
    for(int i = 0; i < A.size(); i++) {
        for(int j = 0; j < B.size(); j++) {
            for(int k = 0; k < B[j].size(); k++) {
                C[i][k] = (C[i][k] + (ll) A[i][j] * B[j][k]) % MOD;
            }
        }
    }
    return C;
}

Mat add(Mat A, Mat B) {
    Mat C = A;
    for(int i = 0; i < A.size(); i++) {
        for(int j = 0; j < A[i].size(); j++) {
            C[i][j] += B[i][j];
            if(C[i][j] >= MOD) C[i][j] -= MOD;
        }
    }
    return C;
}

int main() {
    int N, K, Q; cin >> N >> K >> Q;
    Mat G(N, vector<int>(N));
    for(int i = 0; i < N; i++) {
        string s; cin >> s;
        for(int j = 0; j < N; j++) {
            if(s[j] == '1') G[i][j]++;
        }
    }

    vector<Mat> A(K, Mat(N, vector<int>(N)));
    A[1] = G;
    for(int i = 0; i < N; i++) A[1][i][i]++;
    for(int i = 2; i < K; i++) {
        A[i] = add(A[i - 1], mult(A[i - 1], A[i - 1]));
    }

    for(int i = 0; i < Q; i++) {
        int a, b, c, d; 
        cin >> a >> b >> c >> d;
        int ans = 0;
        Mat S(1, G[b]);
        S[0][b]++;
        Mat E(N, vector<int>(1));
        for(int j = 0; j < N; j++) E[j][0] = G[j][d];
        
    }

}