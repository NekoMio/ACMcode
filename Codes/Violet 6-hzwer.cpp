#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define mod 10007
#define pi acos(-1)
#define inf 0x7fffffff
#define ll long long
using namespace std;
ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,blo,id;
int v[50005],bl[50005];
int f[505][505];
map<int,int>mp;
int val[50005],cnt[50005];
vector<int>ve[50005];
void pre(int x)
{   
    memset(cnt,0,sizeof(cnt));
    int mx=0,ans=0;
    for(int i=(x-1)*blo+1;i<=n;i++)
    {       
        cnt[v[i]]++;        
        int t=bl[i];
        if(cnt[v[i]]>mx||(cnt[v[i]]==mx&&val[v[i]]<val[ans]))
            ans=v[i],mx=cnt[v[i]];
        f[x][t]=ans;
    }
}
int query(int l,int r,int x)
{
    int t=upper_bound(ve[x].begin(),ve[x].end(),r)-lower_bound(ve[x].begin(),ve[x].end(),l);
    return t;
}
int query(int a,int b)
{
    int ans,mx;
    ans=f[bl[a]+1][bl[b]-1];
    mx=query(a,b,ans);
    for(int i=a;i<=min(bl[a]*blo,b);i++)
    {
        int t=query(a,b,v[i]);
        if(t>mx||(t==mx&&val[v[i]]<val[ans]))ans=v[i],mx=t;
    }
    if(bl[a]!=bl[b])
        for(int i=(bl[b]-1)*blo+1;i<=b;i++)
        {
            int t=query(a,b,v[i]);
            if(t>mx||(t==mx&&val[v[i]]<val[ans]))ans=v[i],mx=t;
        }
    return ans;
}
int main()
{
    n=read();m=read();
    blo=200;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        v[i]=read();
        if(!mp[v[i]])
        {
            mp[v[i]]=++id;
            val[id]=v[i];
        }
        v[i]=mp[v[i]];
        ve[v[i]].push_back(i);
    }
    for(int i=1;i<=n;i++)bl[i]=(i-1)/blo+1;
    for(int i=1;i<=bl[n];i++)pre(i);
    for(int i=1;i<=m;i++)
    {
        int a=read(),b=read();
        a=(a+ans-1)%n+1;b=(b+ans-1)%n+1;
        if(a>b)swap(a,b);
        ans=val[query(a,b)];
        printf("%d\n",ans);
    }
    return 0;
}