#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

int N, M;
vector<set<int>> adj;
vector<set<int>> radj;
vector<int> p;

int get_p(int s) {
    return p[s] == -1 ? s : p[s] = get_p(p[s]);
}

int main() {
    cin >> N >> M;
    adj.resize(N), radj.resize(N), p.resize(N, -1);
    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].insert(b);
        radj[b].insert(a);
    }
    //cout << strnl(adj) << endl;

    // remove all edges with no outward edges
    vector<bool> noedges(N);
    queue<int> q;
    for(int i = 0; i < N; i++)
        if(adj[i].empty())
            q.push(i);
    while(!q.empty()) {
        int s = q.front();
        noedges[s] = true;
        q.pop();
        for(int u : radj[s]) {
            adj[u].erase(s);
            if(adj[u].empty()) 
                q.push(u);
        }
    }
    //cout << strnl(adj) << endl;
	for(int i = 0; i < N; i++) 
		if(adj[i].size() == 1)
			q.push(i);
	while(!q.empty()) {
		int s = q.front();
		q.pop();
        
        int a = s, b;
        for(int u : adj[a])
            b = u;
        a = get_p(a);
        b = get_p(b);
        if(a != b) {
            if(radj[a].size() < radj[b].size()) swap(a, b);
            //cout << a << " " << b << endl;
            p[b] = a;
            for(int u : radj[b]) {
                adj[u].erase(b);
                adj[u].insert(a);
                if(adj[u].size() == 1) {
                    radj[a].erase(u);
                    q.push(u);
                } else {
                    radj[a].insert(u);
                }
            }
        }
	}
    //cout << str(p) << endl;
    int Q;
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if(noedges[x] || noedges[y])
            cout << "B";
        else if(get_p(x) == get_p(y))
            cout << "B";
        else
            cout << "H";
    }
    cout << endl;
}