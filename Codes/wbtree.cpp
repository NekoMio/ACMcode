#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
class edge
{
public:
    int END, next;
} v[2000005];
int first[1000005], p=1;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int fa[1000005], dep[1000005];
int Idx[1000005];
void dfs(int rt, int f, int Dep)
{
    fa[rt] = f;
    dep[rt] = Dep;
    for (int i = first[rt]; i != -1; i=v[i].next)
    {
        if(v[i].END!=f)
        {
            Idx[v[i].END]=(i+1)/2;
            dfs(v[i].END,rt,Dep+1);
        }
    }
}
bool mark[1000005];
void Mark(int a,int b)
{
    if(dep[a]<dep[b])swap(a,b);
    while(dep[a]>dep[b])
    {
        mark[Idx[a]]=1;
        a=fa[a];
    }
    while(a!=b)
    {
        mark[Idx[a]]=1;
        mark[Idx[b]]=1;
        a=fa[a];
        b=fa[b];
    }
}
int get_ans(int x)
{
    int ans=0;
    while(x!=1)
    {
        if(mark[Idx[x]])
        {
            ans=Idx[x];
            break;
        }
        x=fa[x];
    }
    return ans;
}
int main()
{
    memset(first,-1,sizeof(first));
    int n, m, a, b;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs(1, 0, 1);
    int op,s,e;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d",&s);
            printf("%d\n",get_ans(s));
        }
        else 
        {
            scanf("%d%d",&s,&e);
            Mark(s,e);
        }
    }
}
