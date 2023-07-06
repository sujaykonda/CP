#include <cplib/general.h>
// the previous include is just my template (rd(i) reads into i)
using namespace std;

// xor basis
struct XorBasis {
    array<int, 30> basis{};
    void add(int mask) {
        for(int i = 31; i >= 0; i--) {
            if(getbit(mask, i)) {
                if(!basis[i]) { basis[i] = mask; return; }
                mask ^= basis[i];
            }
        }
    }
    bool check(int mask) {
        for(int i = 30; i >= 0; i--) {
            if(getbit(mask, i) && basis[i]) {
                mask ^= basis[i];
            }
        }
        return mask == 0;
    }
    int getMax() {
        int mx = 0;
        for(int i = 30; i >= 0; i--) {
            if(!getbit(mx, i) && basis[i])
                mx ^= basis[i];
        }
        return mx;
    }
};

int main() {
    int q; rd(q);
    vector<XorBasis> rec(q + 1);
    for(int i = 1; i <= q; i++) {
        int t; rd(t);
        if(t == 1) {
            int x; rd(x);
            XorBasis copy = rec[i - 1];
            copy.add(x);
            rec[i] = copy;
        } else if(t == 2) {
            int x; rd(x);
            rec[i] = rec[i - 1];
            cout << rec[i].check(x) << " ";
        } else if(t == 3) {
            rec[i] = rec[i - 1];
            cout << rec[i].getMax() << " ";
        } else if(t == 4) {
            int x; rd(x);
            rec[i] = rec[x];
        }
    }
}
