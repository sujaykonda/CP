#include <bits/stdc++.h>

using namespace std;

int N, B;

vector<pair<int, int>> snow;
vector<pair<int, int>> linkedlist;
vector<pair<pair<int, int>, int>> boots;
vector<bool> ans;

int main()
{
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);
    cin >> N >> B;

    snow.resize(N);
    linkedlist.resize(N);
    boots.resize(B);
    ans.resize(B);
    for (int i = 0; i < N; i++)
    {
        cin >> snow[i].first;
        snow[i].second = i;
    }

    for (int i = 0; i < B; i++)
    {
        cin >> boots[i].first.first >> boots[i].first.second;
        boots[i].second = i;
    }
    for (int i = 0; i < N; i++)
    {
        linkedlist[i].first = i - 1;
        linkedlist[i].second = i + 1;
    }

    sort(snow.begin(), snow.end());
    reverse(snow.begin(), snow.end());
    sort(boots.begin(), boots.end());
    reverse(boots.begin(), boots.end());

    int i = 0, j = 0;
    int gap = 0;
    while (j < B)
    {
        if (boots[j].first.second < gap)
        {
            ans[boots[j].second] = true;
        }
        if (boots[j].first.first >= snow[i].first)
        {
            j++;
            continue;
        }
        // snow removal
        int snowi = snow[i].second;
        int ngap = linkedlist[snowi].second - linkedlist[snowi].first;
        linkedlist[linkedlist[snowi].second].first = linkedlist[snowi].first;
        linkedlist[linkedlist[snowi].first].second = linkedlist[snowi].second;
        gap = max(gap, ngap);
        i++;
    }
    for (int i = 0; i < B; i++)
        cout << !ans[i] << endl;
}