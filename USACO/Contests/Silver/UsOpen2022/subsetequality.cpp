#include <bits/stdc++.h>

#define MAX_L 18

using namespace std;

string s;
string t;
int Q;

bool one[MAX_L];
bool two[MAX_L][MAX_L];

int countLetter(string str, char c)
{
    int s = 0;
    int i = -1;
    while ((i = str.find_first_of(c, i + 1)) != str.npos)
        s++;
    return s;
}

bool check(string q)
{

    for (int i = 0; i < q.length(); i++)
        for (int j = i; j < q.length(); j++)
            if (!two[q[i] - 'a'][q[j] - 'a'])
                return false;
    return true;
}

int main()
{
    cin >> s >> t;
    cin >> Q;

    for (char c = 'a'; c <= 'r'; c++)
        one[c - 'a'] = countLetter(s, c) == countLetter(t, c);

    for (char c = 'a'; c <= 'r'; c++)
    {
        if (!one[c - 'a'])
            continue;
        for (char c2 = 'a'; c2 <= 'r'; c2++)
        {
            if (!one[c2 - 'a'])
                continue;
            string ns, nt;
            for (char c3 : s)
                if (c3 == c || c3 == c2)
                    ns.push_back(c3);
            for (char c3 : t)
                if (c3 == c || c3 == c2)
                    nt.push_back(c3);
            two[c - 'a'][c2 - 'a'] = ns == nt;
        }
    }

    for (int i = 0; i < Q; i++)
    {
        string q;
        cin >> q;
        char t = check(q) ? 'Y' : 'N';
        cout << t;
    }
    cout << endl;
}