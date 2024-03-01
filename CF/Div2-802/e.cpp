#include <cplib/general.h>
using namespace std;

int main() {
    int n, m; rd(n, m); 
    vector<vector<int>> a(n, vector<int>(m)); rd(a);
    vector<vector<bool>> bad(n, vector<bool>(m));
    int cnt = 0;
    auto check = [&] (int i, int j) {
        if(a[i][j] == 1) return false;
        if(i > 0 && a[i - 1][j] < a[i][j]) return false;
        if(j > 0 && a[i][j - 1] < a[i][j]) return false;
        if(i < n - 1 && a[i + 1][j] < a[i][j]) return false;
        if(j < m - 1 && a[i][j + 1] < a[i][j]) return false;
        return true;
    };
    auto upd = [&] (int i, int j) {
        bool nw = check(i, j);
        cnt += nw - bad[i][j];
        bad[i][j] = nw;
    };
    auto upd_around = [&] (int i, int j) {
        upd(i, j);
        if(i > 0) upd(i - 1, j);
        if(j > 0) upd(i, j - 1);
        if(i < n - 1) upd(i + 1, j);
        if(j < m - 1) upd(i, j + 1);
    };
    vector<pair<int, int>> updlst;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            upd(i, j);
            if(bad[i][j]) {
                updlst.pb({i, j});
                if(i > 0) updlst.pb({i - 1, j});
                if(j > 0) updlst.pb({i, j - 1});
                if(i < n - 1) updlst.pb({i + 1, j});
                if(j < m - 1) updlst.pb({i, j + 1});
            }
        }
    }
    auto swap_ = [&] (int x1, int y1, int x2, int y2) {
        swap(a[x1][y1], a[x2][y2]);
        upd_around(x1, y1);
        upd_around(x2, y2);
    };
    auto sum_around = [&] (int i, int j) {
        int sm = bad[i][j];
        if(i > 0) sm += bad[i - 1][j];
        if(j > 0) sm += bad[i][j - 1];
        if(i < n - 1) sm += bad[i + 1][j];
        if(j < m - 1) sm += bad[i][j + 1];
        return sm;
    };
    if(cnt > 10) {
        cout << 2 << endl;
    } else if(cnt == 0) {
        cout << 0 << endl;
    } else {
        set<pair<int, int>> ans;
        auto try_swap = [&] (int x1, int y1, int x2, int y2) {
            swap_(x1, y1, x2, y2);
            if(cnt == 0) {
                if(a[x1][y1] > a[x2][y2])
                    ans.insert({a[x2][y2], a[x1][y1]});
                else
                    ans.insert({a[x1][y1], a[x2][y2]});
            }
            swap_(x1, y1, x2, y2);
        };
        for(auto [x1, y1] : updlst) {
            if(sum_around(x1, y1) == cnt) {
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < m; j++) {
                        try_swap(x1, y1, i, j);
                    }
                }
            } else {
                for(auto [x2, y2] : updlst) {
                    if(a[x1][y1] > a[x2][y2]) {
                        try_swap(x1, y1, x2, y2);
                    }
                }
            }
        }
        if(ans.size() == 0) cout << 2 << endl;
        else cout << 1 << " " << ans.size() << endl;
    }
}