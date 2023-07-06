#include <cplib/general.h>
using namespace std;

int main() {
    int n, q; string s;
    rd(n, q, s);
    set<int> ls, rs;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 1 && s[i] == '(')
            ls.insert(i);
        if(i % 2 == 0 && s[i] == ')')
            rs.insert(i);
    }
    for(int i = 0; i < q; i++) {
        int j; rd(j); j--;
        if(j % 2 == 1) {
            if(s[j] == '(')
                ls.erase(j);
            else
                ls.insert(j);
        } else {
            if(s[j] == ')')
                rs.erase(j);
            else
                rs.insert(j);
        }
        s[j] = (s[j] == ')') ? '(' : ')';
        if(s.size() % 2 == 1 || ((ls.size() == 0) != (rs.size() == 0)) || (ls.size() >= 1 && rs.size() >= 1 && (*ls.begin() > *rs.begin() || *ls.rbegin() > *rs.rbegin()))) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
}