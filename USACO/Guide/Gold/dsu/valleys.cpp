// benq's code is very confusing, this does the exact same
// first observation is that you can notice to track all regions we can loop through the grid cells in height order
// the basic idea is that we track the number of holes in each region through two dsus
// one dsu will track the holes, by going through the order in reverse (we are removing a cell)
// and the other will track the regions along with the holes inside those regions

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = long long;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

void setio(string name = "") { 
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    if(name != "") {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
vi range(int s, int e) { vi r(e - s); for(int i = s; i < e; i++) r[i - s] = i; return r; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

int dx[] = {1, 0, 0, -1, 1, 1, -1, -1};
int dy[] = {0, 1, -1, 0, 1, -1, 1, -1};

struct DSU
{
    vector<ll> e;
    DSU(int N) : e(N, -1) {}
    ll get(int x) { return e[x] < 0 ? x : x = get(e[x]); }
    ll size(int x) { return -e[x]; }
    bool unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return false;
        if (e[x] > e[y])
            swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};

int main() {
    setio("valleys");
    int N;
    cin >> N;
    N += 2;
    vector<vector<int>> h(N, vector<int>(N, 1000001));
    vector<int> o;
    for(int i = 1; i < N - 1; i++)
        for(int j = 1; j < N - 1; j++)
            cin >> h[i][j], o.pb(N * i + j);
    
    // sort o by height
    sort(o.begin(), o.end(), [&] (int a, int b) { return h[a / N][a % N] < h[b / N][b % N]; });
    
    // mark all non valley locations
    DSU rdsu(N * N);
    vector<bool> valley(N * N, true);
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < N; j++)
            if(i == 0 || i == N - 1 || j == 0 || j == N - 1)
                valley[N * i + j] = false, rdsu.unite(0, N * i + j);

    // mark the change in holes by seening how the holes change from removing cell o[i] from the region
    vector<int> deltaholes(o.size());
    for(int i = o.size() - 1; i >= 0; i--) {
        int xy = o[i];
        valley[xy] = false;
        // assume that removing cell o[i] will result in adding one more hole, meaning adding o[i] will result in one less hole
        deltaholes[i]--;
        for(int j = 0; j < 8; j++) {
            int nxy = xy + N * dx[j] + dy[j];
            if(!valley[nxy]) 
                if(rdsu.unite(nxy, xy)) 
                    // if removing cell o[i] will merge into another hole, then it reduces the number of holles, so in reverse it will increase the number of holes
                    deltaholes[i]++;
        }
    }

    // go again, track the number of holes, and sum up the valleys
    ll sum = 0;
    vector<int> holecnt(N * N);
    DSU dsu(N * N);
    for(int i = 0; i < o.size(); i++) {
        int xy = o[i];
        valley[xy] = true;
        for(int j = 0; j < 4; j++) {
            int nxy = dsu.get(xy + N * dx[j] + dy[j]);
            int rxy = dsu.get(xy);
            if(valley[nxy]) 
                if(dsu.unite(nxy, rxy))
                    // when uniting two parents we must also sum up their holecnts
                    holecnt[dsu.get(xy)] = holecnt[nxy] + holecnt[rxy];
        }
        // use deltaholes and add that to the holecnt
        holecnt[dsu.get(xy)] += deltaholes[i];
        // if there are no holes then we add it to the sum
        if(holecnt[dsu.get(xy)] == 0)
            sum += dsu.size(dsu.get(xy));
    }
    cout << sum << endl;
}