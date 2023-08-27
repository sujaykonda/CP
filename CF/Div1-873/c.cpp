#include <cplib/str.h>
using namespace std;

void tc() {
    int n; rd(n);
    string s; rd(s);
    vector<int> pals = manacher(s);
    vector<int> evens(n);
    for(int i = 1; i < pals.size(); i += 2)
        evens[i / 2] = pals[i] / 2;
    evens[n - 1] = n;
    stack<int> st; st.push(n - 1);
    vector<int> dp(n + 1); dp[n] = 0;
    for(int i = n - 1; i >= 0; i--) {
        st.push(i);
        while(st.top() - i >= evens[st.top()]) st.pop();
        if(st.top() != n - 1)
            dp[i] = dp[2 * st.top() - i + 2] + 1;
    }
    ll sm = 0;
    for(int i = 0; i < n; i++) sm += dp[i];
    cout << sm << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}