#include <cplib/math/mint.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, lim; rd(n, lim);
    if(lim > (n * (n + 1)) / 2) {
        cout << 0 << endl;
        return 0;
    }
    int nC2 = (n * (n + 1)) / 2;
    Comb<MOD> comb(nC2);
    vector<vector<mint<MOD>>> points(n + 1, vector<mint<MOD>>(nC2 + 1));
    points[0] = vector<mint<MOD>>(nC2 + 1, 1);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            mint<MOD> ch = comb.choose(i, j);
            for(int x = 0; x <= nC2; x++) {
                points[i + 1][x] += ch * points[j][x] * points[i - j][x];
            }
        }
        for(int x = 0; x <= nC2; x++) {
            points[i + 1][x] *= bpow(mint<MOD>(x), i + 1);
        }
    }
    
    vector<mint<MOD>> P(nC2 + 2);
    P[0] = 1;
    for(int i = 0; i <= nC2; i++) {
        for(int j = i; j >= 0; j--) {
            P[j + 1] += P[j];
            P[j] *= -i;
        }
    }

    mint<MOD> ans;
    for(int i = 0; i <= nC2; i++) {
        mint<MOD> b = points[n][i] * comb.invf[nC2 - i] * ((nC2 - i) % 2 ? -1 : 1) * comb.invf[i];
        mint<MOD> last = P[nC2 + 1];
        for(int j = nC2; j >= lim; j--) {
            ans += b * last; 
            last *= i;
            last += P[j];
        }
    }
    cout << ans << endl;
}