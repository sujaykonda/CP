#include <cplib/general.h>
using namespace std;

const int MX = 1e6 + 1;
array<array<int, MX>, 20> jmp;
array<int, MX> val, ans, dep;
array<stack<int, vector<int>>, MX> last;
int main() {
    int q; rd(q);
    stack<int> s; s.push(0);
    stack<int> o; o.push(-1);
    for(int i = 1; i <= q; i++) {
        string t; rd(t);
        if(t[0] == '+') {
            assert(s.top() >= 0);
            rd(val[i]);
            dep[i] = dep[s.top()] + 1;
            jmp[0][i] = s.top();
            for(int j = 0; j < 19; j++) jmp[j + 1][i] = jmp[j][jmp[j][i]];
            bool nw = true;
            if(!last[val[i]].empty()) {
                int d = dep[i] - dep[last[val[i]].top()];
                int p = i;
                for(int j = 19; j >= 0; j--) {
                    if(d >= (1 << j))
                        p = jmp[j][p], d -= (1 << j);
                }
                if(p == last[val[i]].top())
                    nw = false;
            }
            if(nw) last[val[i]].push(i), o.push(val[i]);
            else o.push(-1);
            ans[i] = ans[s.top()] + nw;
            s.push(i);
        } else if(t[0] == '-') {
            int k; rd(k);
            int p = s.top();
            for(int j = 19; j >= 0; j--)
                if(k >= (1 << j))
                    p = jmp[j][p], k -= (1 << j);
            s.push(p);
            o.push(-1);
        } else if(t[0] == '!') {
            s.pop();
            if(o.top() != -1) last[o.top()].pop();
            o.pop();
        } else if(t[0] == '?') {
            cout << ans[s.top()] << endl;
        }
    }
}