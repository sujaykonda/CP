#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int visited[100001];
int N;
int M;
vector<pair<int, bool>> pc[100001];

int dfs(int s, int b)
{
    if (visited[s] != 0)
    {
        if (b != visited[s])
            return 0;
        else
            return 1;
    }
    visited[s] = b;
    int n = 1;
    for (pair<int, bool> c : pc[s])
    {
        n *= dfs(c.first, ((b - 1) ^ c.second) + 1);
    }
    return n;
}

int main()
{
    ifstream fin("revegetate.in");
    fin >> N;
    fin >> M;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        char c;
        fin >> c >> a >> b;
        pc[a].push_back(make_pair(b, c == 'D'));
        pc[b].push_back(make_pair(a, c == 'D'));
    }
    fin.close();

    ofstream fout("revegetate.out");

    int s = 0;
    string a = "1";
    while (s < N)
    {
        s++;
        if (visited[s] != 0)
        {
            continue;
        }
        bool d = dfs(s, 1);
        if (!d)
        {
            fout << 0 << endl;
            fout.close();
            return 1;
        }
        a.push_back('0');
    }
    fout << a << endl;
}