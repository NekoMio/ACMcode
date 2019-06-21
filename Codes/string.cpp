#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <ctime>
using namespace std;
vector<int> l;
struct Improtant
{
    int i, Imp;
    bool operator<(const Improtant &a) const
    {
        return Imp == a.Imp ? i < a.i : Imp < a.Imp;
    }
} number[50005];
struct Trie
{
    map<int, Trie *> mp;
    set<Improtant> mark;
} * root;
void insert(int x)
{
    Trie *rt = root;
    rt->mark.insert(number[x]);
    for (int i = 0; i < l.size(); i++)
    {
        if (!rt->mp[l[i]])
            rt->mp[l[i]] = new Trie;
        rt = rt->mp[l[i]];
        rt->mark.insert(number[x]);
    }
}
void Query(int k)
{
    Trie *rt = root;
    for (int i = 0; i < l.size(); i++)
    {
        if (rt->mp[l[i]] == NULL)
        {
            printf("0\n");
            return;
        }
        rt = rt->mp[l[i]];
    }
    set<Improtant>::iterator it = rt->mark.begin();
    printf("%d ", rt->mark.size());
    for (int i = 1; i <= k && it != rt->mark.end(); i++, it++)
    {
        printf("%d ", it->i);
    }
    printf("\n");
    return;
}
int main()
{
#ifdef Mine
    freopen("1.in", "r", stdin);
#else
    freopen("string.in", "r", stdin);
#endif
    freopen("string.out", "w", stdout);
    int n, m;
    root = new Trie;
    scanf("%d%d", &n, &m);
    int t, s, a;
    for (int i = 1; i <= n; i++)
    {
        number[i].i = i;
        scanf("%d%d", &t, &number[i].Imp);
        while (t--)
        {
            scanf("%d", &s);
            l.clear();
            for (int j = 1; j <= s; j++)
            {
                scanf("%d", &a);
                l.push_back(a);
            }
            insert(i);
        }
    }
    int k;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &k, &s);
        l.clear();
        for (int j = 1; j <= s; j++)
        {
            scanf("%d", &a);
            l.push_back(a);
        }
        Query(k);
    }
    //printf("%lf",(double)clock()/CLOCKS_PER_SEC);
}
