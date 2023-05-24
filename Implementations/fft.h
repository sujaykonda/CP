#include <bits/stdc++.h>
#include <nt.h>
using namespace std;
using ll = long long;

using cd = complex<long double>;
const long double PI = 3.14159265358979323846;
// sorts indices by reverse binary order
template<class T> void rsort(vector<T>& a) {
    for (int i = 1, j = 0; i < a.size(); i++) {
        int bit = a.size() / 2;
        for (; j & bit; bit /= 2) j ^= bit;
        if (i < (j ^= bit)) swap(a[i], a[j]);
    }
}
// fft
template<class T> void fft(vector<T>& a, vector<T>& rts) {
    rsort(a);
    int n = a.size(), lgn = 0; while((1 << lgn) < n) lgn++;
    for(int k = 0; k < lgn; k++) {
        for(int i = 0; i < n; i += (1 << (k + 1))) {
            for (int j = 0; j < (1 << k); j++) {
                T v = a[i + j + (1 << k)] * rts[j * (1 << (lg - k))];
                a[i + j + (1 << k)] = a[i + j] - v, a[i + j] += v;
            }
        }
    }
}


// convolution with arbitrary mods 
template<int MOD> std::vector<mint<MOD>> convMod(std::vector<mint<MOD>>& A, std::vector<mint<MOD>>& B) {
    int n = 1; while(n < A.size() || n < B.size()) n *= 2;
    n *= 2, A.resize(n), B.resize(n);
    // create a poly and b poly
    std::vector<cd> a(n), b(n);
    int cut = sqrt(MOD);
    for(int i = 0; i < n; i++) a[i] = cd(A[i].v / cut, A[i].v % cut);
    for(int i = 0; i < n; i++) b[i] = cd(B[i].v / cut, B[i].v % cut);
    
    // root gen
    std::vector<cd> rts(n / 2);
    for(int i = 0; i < n / 2; i++)
        rts[i] = cd(cos(2 * PI * i / n), sin(2 * PI * i / n));

    fft<cd>(a, rts), fft<cd>(b, rts);
    std::vector<cd> ma(n), mb(n);
    for(int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        ma[j] = (a[i] + conj(a[j])) * b[i] / cd(2.0 * n);
        mb[j] = (a[i] - conj(a[j])) * b[i] / cd(2.0 * n) / cd(0, 1);
    }
    fft<cd>(ma, rts), fft<cd>(mb, rts);
    std::vector<mint<MOD>> res(n);
    for(int i = 0; i < n; i++) {
        mint<MOD> av(ll(real(ma[i]) + .5)), 
            bv(ll(imag(ma[i]) + .5) + ll(real(mb[i]) + .5)), 
            cv(ll(imag(mb[i]) + .5));
        res[i] = (av * cut + bv) * cut + cv;
    }
    return res;
}