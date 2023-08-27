#include <cplib/general.h>
using namespace std;
const int XMX = 1e6 + 1;
int x, q, M; 
struct mint {
    int v; mint(int _v) : v(_v) {}
    friend mint operator*(mint a, mint b) { return mint((ll)a.v * b.v % M); }
};
array<int, XMX> spf;
int main() {
    for(int i = 0; i < XMX; i++) spf[i] = i;
    for(int i = 2; i * i < XMX; i++) {
        if(spf[i] == i)
            for(int j = i; j < XMX; j += i)
                spf[j] = (spf[j] == j) ? i : spf[j];
    }
    rd(x, q, M);

    map<int, int> pf;
    bool iscomp = true;
    while(iscomp) {
        iscomp = false;
        for(int i = 2; i * i <= x; i++) {
            if(x % i == 0) {
                if(i != 2) pf[i]++;
                x /= i;
                iscomp = true;
                break;
            }
        }
    }
    if(x > 2)
        pf[x]++;
    mint ans(1);
    int zero = 0;
    for(auto [u, v] : pf) {
        if((v + 1) % M > 0)
            ans = ans * mint(v + 1);
        else 
            zero++;
    }
    vector<int> xs(q); rd(xs);
    for(int xi : xs) {
        while(xi > 1) {
            if(spf[xi] != 2) {
                if((pf[spf[xi]] + 1) % M > 0)
                    ans = ans * bpow(mint(pf[spf[xi]] + 1), M - 2);
                else
                    zero--;
                pf[spf[xi]]++;
                if((pf[spf[xi]] + 1) % M > 0)
                    ans = ans * mint(pf[spf[xi]] + 1);
                else
                    zero++;
            }
            xi /= spf[xi];
        }
        if(zero > 0) cout << 0 << endl;
        else cout << ans.v << endl;
    }
}