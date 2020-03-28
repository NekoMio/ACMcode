#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 50005
using namespace std;
int TT,n,C[N],D[N],M[N],P[N],e[N],R[N],E[N];
int zz=1,a[N*2];
struct ro{
	int to,next,l,c;
}road[N*10];
void build(int x,int y,int l,int c)
{
	zz++;
	road[zz].to=y;
	road[zz].next=a[x];
	road[zz].l=l;
	road[zz].c=c;
	a[x]=zz;	

	zz++;
	road[zz].to=x;
	road[zz].next=a[y];
	road[zz].l=0;
	road[zz].c=-c;
	a[y]=zz;
}
int S,T;
long long dis[N];
queue<int> q1;
bool rd[N];
bool bfs()
{
	q1.push(S);
	memset(dis,0x3f,sizeof(long long)*(n*2+5));
	dis[S]=0;
	rd[S]=1;
	while(!q1.empty())
	{
		int x=q1.front();q1.pop();
		rd[x]=0;
		for(int i=a[x];i;i=road[i].next)
		{
			int y=road[i].to;
			if(road[i].l<=0) continue;
			if(dis[y]>dis[x]+road[i].c)
			{
				dis[y]=dis[x]+road[i].c;
				if(!rd[y])
				{
					rd[y]=1;
					q1.push(y);
				}
			}
		}
	}
	if(dis[T]==dis[0]) return 0;
	return 1;
}
long long ans;
int dfs(int x,int sum)
{
	if(x==T)
	{
		ans+=1ll*sum*dis[T];
		return sum;
	}
	rd[x]=1;
	int flow=0;
	for(int i=a[x];i;i=road[i].next)
	{
		int y=road[i].to;
		if(road[i].l<=0||dis[y]!=dis[x]+road[i].c||rd[y])continue;
		int k=dfs(y,min(sum,road[i].l));
		flow+=k;
		sum-=k;
		road[i].l-=k;
		road[i^1].l+=k;
		if(!sum) break;
	}
	return flow;
}
long long work(long long sm)
{
	ans=0;
	while(bfs())
	{
		int x=0;
		while(x=dfs(S,sm))
			memset(rd,0,sizeof(bool)*(n*2+5));
		memset(rd,0,sizeof(bool)*(n*2+5));
	}
	return ans;
}
int main()
{
	// freopen("test.in","r",stdin);
	// freopen("2.out","w",stdout);
	scanf("%d",&TT);
	while(TT--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			int c,d,m,p;
			scanf("%d%d%d%d",&C[i],&D[i],&M[i],&P[i]);
		}
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&e[i],&R[i],&E[i]);
		}
		long long sm=0;
		for(int i=1;i<=n;i++)
		{
			sm+=P[i];
			sm-=D[i];
			if(sm<0)
			{
				printf("-1\n");
				break;
			}
			sm=min(sm,1ll*e[i]);
		}
		if(sm<0)continue;
		zz=1;
		for(int i=1;i<=n*2+2;i++) a[i]=0;
		S=n*2+1;T=S+1;
		sm=0;
		for(int i=1;i<=n;i++)
		{
			sm+=D[i];
			build(S,i,5e8,C[i]);
			build(i,i+n,P[i],M[i]);
			build(i+n,T,D[i],0);
			if(i!=n)
			{
				build(i,i+1,5e8,R[i]);
				build(i+n,i+1+n,e[i],E[i]);
			}
		}
		printf("%lld\n",work(sm));
	}
	return 0;
}
/*
*/
