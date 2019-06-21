#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 5;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
vector<pair<int, int> > c[MAXN];
int size[MAXN];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int Ans[MAXN];
vector<pair<int,int> > DFS(int rt, int fa)
{
    map<int,int> mp;
    set<pair<int,int> > st;
    for (int i = 0; i < c[rt].size() && i < size[rt]; i++)
        st.insert(c[rt][i]);
    set<pair<int,int> >::iterator it, it2;
    for (it = st.begin(); it != st.end(); it++)
        mp[it->second]++;
    vector<pair<int,int> > ret = c[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        vector<pair<int,int> > ch = DFS(v[i].END, rt);
        for (int i = 0; i < ch.size(); i++)
        {
            it2 = st.end();
            ret.push_back(ch[i]);
            if (st.size() < size[rt])
            {
                st.insert(ch[i]);
                mp[ch[i].second]++;
            }
            else if (it2 != st.begin() && ch[i].first < (--it2)->first)
            {
                mp[it2->second]--;
                if (mp[it2->second] == 0) mp.erase(it2->second);
                st.erase(it2);
                st.insert(ch[i]);
                mp[ch[i].second]++;
            }
        }
    }
    Ans[rt] = mp.size();
    return ret;
}
int main()
{
    freopen("ac.in", "r", stdin);
    freopen("ac.out", "w", stdout);
    int n, a, b;
    n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    for (int i = 1; i <= n; i++) size[i] = read();
    int m = read();
    for (int i = 1; i <= m; i++)
        a = read(), b = read(), c[a].push_back(pair<int,int>(i,b));
    DFS(1, 0);
    int Q = read();
    while (Q--)
    {
        a = read();
        printf ("%d\n", Ans[a]);
    }
    fclose(stdin), fclose(stdout);
    // while(1);
}
/*
5
1 2
2 3
3 4
2 5
2 1 1 1 1
2
2 1
4 2
3
1
3
5

2
1
0


10
3 10
2 5
3 2
2 6
1 9
8 7
7 4
3 8
3 1
15 47 23 22 9 16 45 39 21 13
10
10 7
9 3
5 1
5 2
9 4
10 9
2 4
10 1
2 6
7 9
3
1
2
3

7
4
6
*/