#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    vector<string> grid(n); rd(grid);
    bool good = true;
    for(int i = 0; i < n; i++) {
        int ucnt = 0;
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 'U') {
                if(ucnt % 2 == 0) {
                    grid[i][j] = 'W';
                    grid[i + 1][j] = 'B';
                } else {
                    grid[i][j] = 'B';
                    grid[i + 1][j] = 'W';
                }
                ucnt++;
            }
        }
        good = good && (ucnt % 2 == 0);
    }
    for(int j = 0; j < m; j++) {
        int lcnt = 0;
        for(int i = 0; i < n; i++) {
            if(grid[i][j] == 'L') {
                if(lcnt % 2 == 0) {
                    grid[i][j] = 'W';
                    grid[i][j + 1] = 'B';
                } else {
                    grid[i][j] = 'B';
                    grid[i][j + 1] = 'W';
                }
                lcnt++;
            }
        }
        good = good && (lcnt % 2 == 0);
    }
    if(good) {
        for(int i = 0; i < n; i++) cout << grid[i] << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}