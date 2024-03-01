#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 2e18;

vector<vector<pair<int, int>>> adj;
vector<ll> d[2];
vector<int> p;

void dfs(int s, int e, ll cd, vector<ll>& dv) {
	dv[s] = cd;
    p[s] = e;
	for(pair<int, int> edge : adj[s]) {
		if(edge.first == e) continue;
		dfs(edge.first, s, cd + edge.second, dv);
	}
};

int max_score(int N, int X, int Y, ll K, vector<int> U, vector<int> V, vector<int> W) {
    adj = vector<vector<pair<int, int>>>(N);
	for(int i = 0; i < N - 1; i++) {
		adj[U[i]].push_back({V[i], W[i]});
		adj[V[i]].push_back({U[i], W[i]});
	}
    d[0] = d[1] = vector<ll>(N);
    p = vector<int>(N);

	dfs(X, -1, 0, d[0]);
	dfs(Y, -1, 0, d[1]);

    int ans = 0;
    // solve no double case
    {
        vector<ll> e;
        for(int i = 0; i < N; i++) {
            e.push_back(d[0][i]);
            e.push_back(d[1][i]);
        }
        sort(e.begin(), e.end());
        ll sm = 0;
        for(int i = 0; i < e.size(); i++) {
            if(sm > K) {
                break;
            }
            ans = i;
            sm += e[i];
        }

        if(sm <= K) ans = e.size();
    }
    // solve double case
    {
        vector<bool> onXY(N);
        for(int i = X; i != -1; i = p[i]) onXY[i] = true;
        vector<int> A, B;
        for(int i = 0; i < N; i++) {
            // ignore nodes on X to Y, we can merge them at the end (with two pointers!)
            if(onXY[i]) continue;
            // split the nodes into two groups, A and B
            // A nodes are nodes whose greedy method is to repeatedly select the smallest
            // This is due to the fact that the difference between max and min is >= min
            // B nodes are nodes whose greedy method is to select nodes to be connected from both paths
            // and if necessary pick one from to just have one path
            if(2 * min(d[0][i], d[1][i]) <= max(d[0][i], d[1][i])) {
                A.push_back(i);
            } else {
                B.push_back(i);
            }
        }
        // A case
        vector<ll> Ares[2];
        {
            vector<ll> deltas;
            for(int i : A) {
                deltas.push_back(min(d[0][i], d[1][i]));
                deltas.push_back(llabs(d[0][i] - d[1][i]));
            }
            sort(deltas.begin(), deltas.end());
            Ares[0].push_back(0);
            int k = 0;
            // solve greedly by picking smallest "delta"
            for(ll delta : deltas) {
                Ares[k ^ 1].push_back(Ares[k].back() + delta);
                k ^= 1;
            }
        }
        // B case
        vector<ll> Bres[2];
        {
            sort(B.begin(), B.end(), [&] (int a, int b) { return max(d[0][a], d[1][a]) < max(d[0][b], d[1][b]); });
            Bres[0].push_back(0);
            // solve even case greedly by picking smallest max distance
            for(int i : B) {
                Bres[0].push_back(Bres[0].back() + max(d[0][i], d[1][i]));
            }
            vector<ll> addmn(B.size() + 1);
            addmn[B.size()] = INF;
            for(int i = B.size() - 1; i >= 0; i--) {
                addmn[i] = min(addmn[i + 1], min(d[0][B[i]], d[1][B[i]]));
            }
            // solve odd case greedly by picking max for the first n - 1 (which is even case) and then smallest min distance after
            ll submx = 0;
            for(int i = 0; i < B.size(); i++) {
                submx = max(submx, llabs(d[0][B[i]] - d[1][B[i]]));
                Bres[1].push_back(min(Bres[0][i + 1] - submx, Bres[0][i] + addmn[i]));
            }
        }

        // two pointer merging (requirement: a[i] - a[i - 1] must grow while i increases (for both a and b))
        auto merge2p = [&] (vector<ll> a, vector<ll> b) {
            if(a.size() == 0) return vector<ll>(0);
            if(b.size() == 0) return vector<ll>(0);
            int i = 0, j = 0;
            vector<ll> c(a.size() + b.size() - 1);
            while(i < a.size() && j < b.size()) {
                c[i + j] = a[i] + b[j];
                if(i == a.size() - 1) j++;
                else if(j == b.size() - 1) i++;
                else if(a[i + 1] + b[j] <= a[i] + b[j + 1]) i++;
                else j++;
            }
            return c;
        };

        vector<ll> res((A.size() + B.size()) * 2 + 1, INF);
        // merge all evens & odds togethor 
        // node: evens and odds differences are increasing and such we can merge them with 2p merging
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                vector<ll> c = merge2p(Ares[i], Bres[j]);
                for(int k = 0; k < c.size(); k++) {
                    res[i ^ j + 2 * k] = min(res[i ^ j + 2 * k], c[k]);
                }
            }
        }

        // compute XY case
        // XY case is all the nodes on the path between X and Y
        ll sm = 0;
        int cnt = 0;
        vector<ll> res2;
        {
            vector<ll> deltas;
            for(int i = 0; i < N; i++) {
                if(onXY[i]) {
                    cnt++;
                    sm += min(d[0][i], d[1][i]);
                    deltas.push_back(llabs(d[0][i] - d[1][i]));
                }
            }
            sort(deltas.begin(), deltas.end());
            res2.push_back(0);
            // solve greedly again by picking smallest delta
            for(ll delta : deltas) {
                res2.push_back(res2.back() + delta);
            }
        }
        
        // final step is to lazily merge res & res2 (essentially to only calculate the results for K via two pointers)
        int j = res.size() - 1;
        for(int i = 0; i < res2.size(); i++) {
            while(j > 0 && res[j] + res2[i] + sm > K) j--;
            if(res[j] + res2[i] + sm <= K) ans = max(ans, i + j + cnt);
        }
        // reason we cant merge res & res2 via two pointer merging is due to the fact that res & res2 have no 
        // special properties (like previously the even and odd splitting) to merge them.
    }
    return ans;
}


int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	int T; cin >> T;
	vector<int> out;
	while(T--) {
		int N, X, Y;
		ll K;
		cin >> N >> X >> Y >> K;
		vector<int> U(N - 1);
		vector<int> V(N - 1);
		vector<int> W(N - 1);
		for(int i = 0; i < N - 1; i++) {
			cin >> U[i] >> V[i] >> W[i];
		}
        out.push_back(max_score(N, X, Y, K, U, V, W));
	}
    for(int i = 0; i < out.size(); i++) {
        int a; cin >> a;
        if(out[i] != a) {
            cout << "FAILED TEST " << i << ": " << out[i] << " " << a << endl;
        }
    }
}
