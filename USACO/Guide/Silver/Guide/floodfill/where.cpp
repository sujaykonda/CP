#include <bits/stdc++.h>
using namespace std;

int N;
int grid[20][20];
bool done[20][20];

int lx, ly, mx, my;

int floodfill(int x, int y, int c)
{
    if (done[x][y] || x < lx || y < ly || x > mx || y > my || grid[x][y] != c)
        return 0;
    done[x][y] = true;
    int count = 1;
    count += floodfill(x + 1, y, c);
    count += floodfill(x - 1, y, c);
    count += floodfill(x, y + 1, c);
    count += floodfill(x, y - 1, c);
    return count;
}

bool check_pcl(int x1, int y1, int x2, int y2)
{
    int c1c = 0;
    int xc1 = -1, yc1 = -1;
    int c2c = 0;
    int xc2 = -1, yc2 = -1;

    for (int x = x1; x <= x2; x++)
    {
        for (int y = y1; y <= y2; y++)
        {
            done[x][y] = false;
            if (xc1 < 0)
            {
                c1c++;
                xc1 = x, yc1 = y;
            }
            else if (grid[xc1][yc1] == grid[x][y])
            {
                c1c++;
            }
            else if (xc2 < 0)
            {
                c2c++;
                xc2 = x, yc2 = y;
            }
            else if (grid[xc2][yc2] == grid[x][y])
            {
                c2c++;
            }
            else
            {
                return false;
            }
        }
    }
    lx = x1, ly = y1, mx = x2, my = y2;
    int fc1 = floodfill(xc1, yc1, grid[xc1][yc1]);
    int fc2 = floodfill(xc2, yc2, grid[xc2][yc2]);

    if (fc1 == c1c && fc2 != c2c)
    {
        return true;
    }
    if (fc2 == c2c && fc1 != c1c)
    {
        return true;
    }
    return false;
}

vector<pair<pair<int, int>, pair<int, int>>> pcls;

int main()
{
    freopen("where.in", "r", stdin);
    freopen("where.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string line;
        cin >> line;
        for (int j = 0; j < N; j++)
        {
            grid[i][j] = line[j] - 'A';
        }
    }

    for (int x1 = 0; x1 < N; x1++)
    {
        for (int y1 = 0; y1 < N; y1++)
        {
            for (int x2 = x1; x2 < N; x2++)
            {
                for (int y2 = y1; y2 < N; y2++)
                {
                    if (check_pcl(x1, y1, x2, y2))
                    {
                        pcls.push_back({{x1, y1}, {x2, y2}});
                    }
                }
            }
        }
    }

    int ans = 0;
    for (pair<pair<int, int>, pair<int, int>> pcl1 : pcls)
    {
        bool good = true;
        for (pair<pair<int, int>, pair<int, int>> pcl2 : pcls)
        {
            if (pcl2.first.first <= pcl1.first.first &&
                pcl2.first.second <= pcl1.first.second &&
                pcl2.second.first >= pcl1.second.first &&
                pcl2.second.second >= pcl1.second.second &&
                pcl1 != pcl2)
            {
                good = 0;
                break;
            }
        }
        if (good)
        {
            ans++;
        }
    }
    cout << ans << endl;
}