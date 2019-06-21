#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
struct edge
{
    int next,END,v;
}v[200005];
int first[605],p;
void add(int a,int b,int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int low[605],dfn[605],Index;
bool flag[605];
stack<int> st;
int belong[605],T;
void tarjan(int rt)
{
    low[rt] = dfn[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for(int i = first[rt]; i != -1; i = v[i].next)
    {
        if(!dfn[v[i].END])
        {
            tarjan(v[i].END);
            low[rt] = min(low[rt],low[v[i].END]);
        }
        else if(flag[v[i].END])
        {
            low[rt] = min(low[rt],dfn[v[i].END]);
        }
    }
    if(dfn[rt]==low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            belong[v] = T;
        }while(dfn[v]!=low[v]);
    }
}
int INF;
int map[605][605];
int main()
{
    int ans = 0;
    memset(first,-1,sizeof(first));
    int n,m1,m2;
    scanf("%d%d%d",&n,&m1,&m2);
    int a,b;
    memset(map,0xC3,sizeof(map));
    memset(&INF,0xC3,sizeof(INF));
    for(int i = 1; i <= n; i++)
        map[i][i] = 0;
    for(int i = 1; i <= m1; i++)
    {
        scanf("%d%d",&a,&b);
        add(b, a, -1);
        add(a, b, 1);
        map[a][b] = max(map[a][b], 1);
        map[b][a] = max(map[b][a], -1);
    }
    for(int i = 1; i <= m2; i++)
    {
        scanf("%d%d",&a,&b);
        add(a, b, 0);
        map[a][b] = max(map[a][b], 0);
        //add(b, a, 0);
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i);
    
    for(int d = 1; d <= T; d++)
    {
        for(int k = 1; k <= n; k++)
        {
            if(belong[k]!=d) continue;
            for(int i = 1; i <= n; i++)
            {
                if(belong[i]!=d)continue;
                if(map[i][k]==INF)continue;
                for(int j = 1; j <= n; j++)
                {
                    if(belong[j]!=d)continue;
                    if(map[k][j]==INF)continue;
                    map[i][j] = max (map[i][j], map[i][k] + map[k][j]);
                }
            }
        }
        int ret = 0;
        for(int i = 1; i <= n; i++)
        {
            if(belong[i]!=d)continue;
            for(int j = 1; j <= n; j++)
            {
                if(belong[j]!=d)continue;
                ret = max(ret, abs(map[i][j]));
            }
        }
        ans+=ret+1;
    }
    for(int i =1 ;i <= n; i++)
        if(map[i][i]!=0)
        {
            puts("NIE");
            return 0;
        }
    printf("%d\n",ans);
}