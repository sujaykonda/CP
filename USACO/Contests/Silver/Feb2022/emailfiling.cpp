#include <bits/stdc++.h>
using namespace std;

int N, M, K;
int folder[100000];
int rem[10000];
bitset<100000> filed;
struct cmp
{
    bool operator()(int a, int b) { return folder[a] > folder[b]; }
};
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        filed.reset();
        cin >> N >> M >> K;
        int ff = 0;
        int fe = 0;
        int le = K - 1;
        for (int i = 0; i < N; i++)
        {
            cin >> folder[i];
            folder[i]--;
            rem[folder[i]]++;
        }
        priority_queue<int, vector<int>, cmp> pq;
        for (int j = 0; j < K - 1; j++)
        {
            pq.push(j);
        }
        while (le < N - 1 && ff < M)
        {
            if (rem[ff] == 0)
                ff++;
            else if (!pq.empty() && folder[pq.top()] < ff + K)
            {
                int j = pq.top();
                pq.pop();
                if (j >= fe)
                {
                    filed[j] = 1;
                    rem[folder[j]]--;
                    le++;
                    pq.push(le);
                }
            }
            else
            {
                while (fe < N && filed[fe])
                    fe++;
                fe++;
                le++;
                pq.push(le);
            }
        }
        string answer = "YES";
        while (ff < M)
        {
            if (rem[ff] == 0)
                ff++;
            else
            {
                if (pq.empty())
                {
                    answer = "NO";
                    break;
                }
                int j = pq.top();
                pq.pop();
                if (j >= fe && !filed[j])
                {
                    if (folder[j] >= ff + K)
                    {
                        answer = "NO";
                        break;
                    }
                    filed[j] = 1;
                    rem[folder[j]]--;
                    while (fe > 0)
                    {
                        fe--;
                        if (!filed[fe])
                        {
                            pq.push(fe);
                            break;
                        }
                    }
                }
            }
        }
        cout << answer << endl;
        for (int i = 0; i < M; i++)
            rem[i] = 0;
    }
}