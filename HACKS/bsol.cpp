#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; cin >> T; while(T--){
		int N; cin >> N;
		int min = N+1, minLucky = N+1, ans = 0;
		while(N--){
			int curr; cin >> curr;
			if(curr < min) min = curr;
			else if(curr < minLucky){
				ans++;
				minLucky = curr;
			}
		}
		cout << ans << "\n";
	}
}