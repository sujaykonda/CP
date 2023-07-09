#include <cplib/general.h>
using namespace std;

adjlist adj;
vector<int> o;
vector<bool> done;
void dfs(int s) {
    int d = 0;
    done[s] = true;
    for(int u : adj[s])
        if(!done[u])
            dfs(u);
    o.pb(s);
}

int main() {
    int n, m; rd(n, m);

}