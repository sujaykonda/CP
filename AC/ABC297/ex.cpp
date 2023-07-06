#include <atcoder/all>
using namespace atcoder;
using namespace std;
using mint = modint998244353;

template<class T> struct Poly : vector<T> {
    Poly(int n) : vector<T>(n) {}
    Poly(vector<T> v) : vector<T>(v) {}
    Poly& operator*=(Poly o) { *this = convolution(*this, o); return *this; }
    Poly& operator*=(int v) { for(int i = 0; i < size(*this); i++) (*this)[i] *= v;  return *this;}
    friend Poly operator*(Poly a, Poly b) { return a *= b; }
    friend Poly operator*(Poly a, int b) { return a *= b; }
    friend Poly inv(Poly a, int n) {
        Poly b({1 / a[0]}); 
        Poly ab = a * (-1 / a[0]); ab[0] += 2;
        for(int k = 1; k < n; k *= 2) {
            b *= ab; b.resize(2 * k);
            Poly nab = ab * -1; nab[0] += 2;
            ab *= nab;
        }
        b.resize(n);
        return b;
    }
};

int main() {
    int n; cin >> n;
    Poly<mint> u(n + 1);
    for(int i = 1; i <= n; i++)
        for(int j = 1; i * j <= n; j++)
            u[i * j] += (j % 2 ? 1 : -1);
    Poly<mint> v(u); v[0]--; v *= v;
    v = inv(v, n + 1); u *= v;
    for(int i = 0; i <= n; i++) cout << u[i].val() << " ";
    cout << endl;
    cout << u[n].val() << endl;
    return 0;
}