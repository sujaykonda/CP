#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct Node
{
    Node *back;
    int value;
    Node *front;
};

void remove_node(Node *n)
{
    if (n->front != 0)
    {
        n->front->back = n->back;
    }
    if (n->back != 0)
    {
        n->back->front = n->front;
    }
    delete n;
}

int N;
vector<pair<int, int>> bottoms;
vector<pair<int, int>> peaks;
map<int, Node *> nodemap;
int vpeaks = 0;

int main()
{
    ifstream fin("mountains.in");
    fin >> N;
    for (int i = 0; i < N; i++)
    {
        pair<int, int> peak;
        fin >> peak.first >> peak.second;
        bottoms.push_back(make_pair(peak.first + peak.second, i));
        bottoms.push_back(make_pair(peak.first - peak.second, i));
        peaks.push_back(peak);
    }
    fin.close();
    sort(bottoms.begin(), bottoms.end());

    vpeaks = N;

    Node *start = new Node;
    start->value = -1;
    start->back = 0;
    start->front = 0;
    Node *lastnode = start;
    for (int i = 0; i < bottoms.size(); i++)
    {
        if (nodemap.count(bottoms[i].second))
        {
            Node *n = nodemap[bottoms[i].second];
            if (n->back->value != -1)
            {
                vpeaks--;
            }
            if (lastnode->value == n->value)
            {
                lastnode = n->back;
            }
            remove_node(n);
        }
        else
        {
            Node *newnode = new Node;
            newnode->value = bottoms[i].second;
            newnode->back = lastnode;
            newnode->front = 0;
            lastnode->front = newnode;
            lastnode = newnode;
            nodemap[bottoms[i].second] = newnode;
        }
    }

    ofstream fout("mountains.out");
    fout << vpeaks << endl;
    fout.close();
}