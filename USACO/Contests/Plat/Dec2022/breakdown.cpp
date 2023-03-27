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

int N, K; 
vector<vector<int>> dist;
array<vector<int>, 4> dp_s;
array<vector<int>, 4> dp_n;
array<vector<vector<int>>, 3> dp_bet;

const int inf = 1000000000;

int add_edge(int a, int b) {
    for(int i = 0; i < N; i++) {

    }
}

int main() {
    cin >> N >> K;
    dist.resize(N, vector<int>(N));
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> dist[i][j];
    vector<pair<int, int>> edges(N * N);
    for(int i = 0; i < N * N; i++)
        cin >> edges[i].first >> edges[i].second, edges[i].first--, edges[i].second--;
    vector<int> sol(N * N);
    for(int i = N * N - 1; i >= 0; i--)
        sol[i] = add_edge(edges[i].first, edges[i].second);
    cout << strnl(sol);
}