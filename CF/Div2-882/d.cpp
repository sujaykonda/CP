#include <cplib/general.h>
using namespace std;

int n, m, q; 
vector<int> o, nxt;

int get(int i) {
    if(nxt[i] == i || i == n) return i;
    else return (nxt[i] = get(nxt[i]));
}

int main() {
    rd(n, m, q);
    string s; rd(s);
    int cnt = 0;
    o.resize(n, n + 1);
    nxt.resize(n);
    for(int i = 0; i < n; i++) nxt[i] = i;
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b); a--;
        int j = get(a);
        while(j < b) {
            o[j] = cnt++, nxt[j] = j + 1;
            j = get(j);
        }
    }
    vector<int> ro(cnt);
    for(int i = 0; i < n; i++) 
        if(o[i] != n + 1) ro[o[i]] = i;
    
    int num1s = 0;
    for(char c : s)
        num1s += (c == '1');
    int cor1s = 0;
    for(int i = 0; i < cnt && i < num1s; i++)
        if(s[ro[i]] == '1') cor1s++;
    for(int i = 0; i < q; i++) {
        int x; rd(x); x--;
        if(s[x] == '1') {
            if(o[x] < num1s - 1) cor1s--;
            if(num1s <= cnt && s[ro[num1s - 1]] == '1') cor1s--;
            s[x] = '0';
            num1s--;
        } else {
            if(o[x] < num1s) cor1s++;
            s[x] = '1';
            if(num1s < cnt && s[ro[num1s]] == '1') cor1s++;
            num1s++;
        }
        cout << min(cnt, num1s) - cor1s << endl;
    }
}