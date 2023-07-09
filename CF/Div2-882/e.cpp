#include <cplib/general.h>
using namespace std;

int n; 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int area(int a, int b, int c) {
    int A = (a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c);
    return A > 0 ? A : 0;
}

int q(int a, int b, int c) {
    cout << "? " << a + 1 << " " << b + 1 << " " << c + 1 << endl;
    int s; rd(s); return s;
}

void findTri(int& a, int& b, int& c, int& v) {
    if(n <= 30) {
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++)
                for(int k = j + 1; k < n; k++) {
                    int A = q(i, j, k);
                    for(int l = 1; l <= 4; l++) {
                        if(A == area(l, l, l)) {
                            a = i, b = j, c = k, v = l;
                            return;
                        }
                    }
                }
                    
    } else {
        while(true) {
            int i = uniform_int_distribution<int>(0, n - 3)(rng);
            int j = uniform_int_distribution<int>(i + 1, n - 2)(rng);
            int k = uniform_int_distribution<int>(j + 1, n - 1)(rng);
            int A = q(i, j, k);
            for(int l = 1; l <= 4; l++) {
                if(A == area(l, l, l)) {
                    a = i, b = j, c = k, v = l;
                    return;
                }
            }
        }
    }
}

int main() {
    rd(n);
    if(n <= 8) {

    } else {
        int a, b, c, v; findTri(a, b, c, v);
        if(v == 1) {
            for(int i = 0; i < n; i++) {

            }
        } else {
            
        }
    }
}