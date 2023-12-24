#include <cplib/general.h>
using namespace std;

void tc() { 
    int n, m;
    string s, t; rd(n, m, s, t);
    vector<queue<int>> closest(26);
    for(int i = 0; i < n; i++) {
        closest[s[i] - 'a'].push(i);
    }
    
    for(int i = 0; i < m; i++) {
        if(closest[t[i] - 'a'].empty()) {
            cout << "NO" << endl;
            return;
        }
        for(int j = 0; j < t[i] - 'a'; j++) {
            while(!closest[j].empty() && closest[j].front() < closest[t[i] - 'a'].front()) {
                closest[j].pop();
            }
        }
        closest[t[i] - 'a'].pop();
    }
    cout << "YES" << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}