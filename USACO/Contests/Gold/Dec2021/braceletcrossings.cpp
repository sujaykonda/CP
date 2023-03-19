#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool testcase() {
    int N, M;
    cin >> N >> M;
    bool good = true;
    vector<int> st(N, -1), en(N, -1);
    vector<vector<bool>> grb(N, vector<bool>(N));
    vector<vector<bool>> grt(N, vector<bool>(N));
    
    vector<int> parent(N, -2);
    for(int i = 0; i < M; i++) {
        int k;
        cin >> k;
        vector<bool> inscan(N);
        vector<int> bo;
        vector<int> to;
        vector<int> occ(N);
        stack<int> s;
        s.push(-1);
        for(int j = 0; j < k; j++) {
            int c;
            cin >> c;
            c--;
            if(s.top() != c) {
                if(parent[c] != -2 && parent[c] != s.top())
                    good = false;
                parent[c] = s.top(); 
                s.push(c);
            }
            else s.pop();
            if(!inscan[c]) bo.push_back(c);
            else to.push_back(c);
            inscan[c] = true;
            if(en[c] != -1) good = false;
            if(st[c] == -1) st[c] = i;
        }
        
        for(int j = 0; j < bo.size(); j++) {
            for(int m = 0; m < j; m++)
                if(grb[bo[j]][bo[m]])
                    good = false;
            for(int m = 0; m < j; m++)
                grb[bo[m]][bo[j]] = true;
        }
        for(int j = 0; j < to.size(); j++) {
            for(int m = 0; m < j; m++)
                if(grt[to[j]][to[m]])
                    good = false;
            for(int m = 0; m < j; m++)
                grt[to[m]][to[j]] = true;
        }
        for(int j = 0; j < bo.size(); j++)
            for(int m = 0; m < j; m++)
                grb[bo[m]][bo[j]] = true;
        for(int j = 0; j < to.size(); j++)
            for(int m = 0; m < j; m++)
                grt[to[m]][to[j]] = true;
        
        for(int j = 0; j < N; j++)
            if(!inscan[j] && st[j] != -1)
                en[j] = i;
        good &= s.size() == 1;
    }
    for(int j = 0; j < N; j++)
        if(en[j] == -1)
            en[j] = M;
    return good;
}

int main() {
    int T;
    cin >> T;
    for(int t = 0; t < T; t++) {
        if(testcase()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}