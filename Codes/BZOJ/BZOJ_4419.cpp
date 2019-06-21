#include <cstring>
#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;
const int N = 200005;
set<int> st[N];
int Sum[N];
int Ans[N];
int main()
{
    int n, m;
    scanf ("%d%d", &n, &m);
    char s[5];
    int a, b;
    // for (int i = 1; i <= n; i++)
        // st[i].insert(i);
    while (m--)
    {
        scanf ("%s", s);
        if (s[0] == '!')
        {
            scanf ("%d", &a);
            Sum[a]++;
        }
        else if (s[0] == '+')
        {
            scanf ("%d%d", &a, &b);
            Ans[a] -= Sum[b], Ans[b] -= Sum[a];
            st[b].insert(a);
            st[a].insert(b);
        }
        else
        {
            scanf ("%d%d", &a, &b);
            Ans[a] += Sum[b], Ans[b] += Sum[a];
            st[b].erase(a);
            st[a].erase(b);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (set<int>::iterator it = st[i].begin(); it != st[i].end(); it++)
        {
            Ans[*it] += Sum[i];
        }
    }
    for (int i = 1; i <= n; i++)
        printf ("%d%c", Ans[i], " \n"[i == n]);
}