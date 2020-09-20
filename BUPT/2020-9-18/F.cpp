#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=3e5+10;
const int maxm=5e5+10; 
const LL MOD=998244353;
struct edge{
	int to,nxt;
}e[maxm<<1];
int head[maxm],cnt;
void add_edge(int u,int v)
{
	cnt++;
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
LL fpow(LL a, LL n, LL p)    
{
    LL ans = 1;
    while(n)
    {
        if(n&1)ans=ans*a%p;//若不取模就去掉p
        a=a*a%p;
        n>>=1;
    }
    return ans;
}
bool vis[maxn], flag[maxn];
LL dep[maxn];
int n,m;
LL ans=1;
LL tot=0;
void dfs(int now,int pre)
{
	vis[now]=1;
  flag[now] = 1;
	dep[now]=dep[pre]+1;
	for(int i=head[now];i;i=e[i].nxt){
		int nxt=e[i].to;
		if(nxt==pre) continue;
    if(vis[nxt]){
      ans=((ans%MOD)*(fpow(2,dep[now]+1-dep[nxt],MOD)-1))%MOD;
      tot+=dep[now]+1-dep[nxt];
      //return;
    }
		if (!flag[nxt]) dfs(nxt,now);
	}
  vis[now] = 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	if(m==0){
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++){
		if(!flag[i])
			dfs(1,-1);
	}
	LL tmp=m-tot;
	ans=((ans%MOD)*fpow(2,tmp,MOD))%MOD;
	printf("%lld\n",ans%MOD);
	return 0; 
}
/*
4 4
1 2
2 3
3 1
3 4
*/