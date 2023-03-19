#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define maxv 1000000000000000000LL
ll l, r, o;

struct Node
{
    vector<Node *> children;
    char v = 0;
    ll s = 0;

    void calc_size()
    {
        if (s > 0)
            return;
        for (Node *child : children)
        {
            child->calc_size();
            if (child->s > maxv + 1 - s)
                s = maxv + 1;
            else
                s += child->s;
        }
        if (children.size() == 0)
            s = 1;
    }

    void print(ll i, ll ls, ll rs)
    {
        if (i + s < ls || i >= rs)
            return;
        for (Node *child : children)
        {
            child->print(i, ls, rs);
            if (child->s > maxv + 1 - i)
                i = maxv + 1;
            else
                i += child->s;
            if (i >= rs)
                return;
        }
        if (children.size() == 0)
            cout << v;
    }
};

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> l >> r >> o;
    // letter to node
    Node *root = new Node();
    root->v = 'a';
    vector<Node *> ends(26);
    ends[0] = root;
    for (int i = 0; i < o; i++)
    {
        char pc;
        string s;
        cin >> pc >> s;
        Node *parent = ends[pc - 'a'];
        ends[pc - 'a'] = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (ends[s[i] - 'a'] == 0)
            {
                ends[s[i] - 'a'] = new Node();
                ends[s[i] - 'a']->v = s[i];
            }
            parent->children.emplace_back(ends[s[i] - 'a']);
        }
    }
    root->calc_size();
    root->print(0, l, r);
    cout << endl;
}