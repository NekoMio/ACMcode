#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 90015
using namespace std;
int n,K,m,zz=1;
struct ro{
	int to,next,l;
}road[1000005];
int a[N];
void build(int x,int y,int z)
{
	zz++;
	road[zz].to=y;
	road[zz].l=z;
	road[zz].next=a[x];
	a[x]=zz;
	
	zz++;
	road[zz].to=x;
	road[zz].l=0;
	road[zz].next=a[y];
	a[y]=zz;
}
int S,T;
int deep[N],q1[N],he,en;
bool bfs()
{
	en=he=1;
	memset(deep,0,sizeof(int)*(n*K+10));
	deep[S]=1;
	q1[1]=S;
	while(he<=en)
	{
		int x=q1[he];he++;
		for(int i=a[x];i;i=road[i].next)
		{
			int y=road[i].to;
			if(road[i].l<=0||deep[y])continue;
			deep[y]=deep[x]+1;
			if(y==T) return 1;
			en++;
			q1[en]=y;
		}
	}
	return 0;
}
int dfs(int x,int sum)
{
	if(x==T)return sum;
	int flow=0;
	for(int i=a[x];i;i=road[i].next)
	{
		int y=road[i].to;
		if(road[i].l<=0||deep[y]!=deep[x]+1)continue;
		int k=dfs(y,min(sum,road[i].l));
		road[i].l-=k;
		road[i^1].l+=k;
		flow+=k;
		sum-=k;
		if(!sum)break;
	}
	return flow;
}
int work()
{
	int ans=0;
	while(bfs())
	{
		int x;
		while(x=dfs(S,0x3fffffff)) ans+=x;
	}
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&K,&m);
	S=K*n+1;T=S+1;
	for(int i=1;i<=K;i++)
	{
		build(S,i+n*(i-1),1);
		build(i*n,T,K);
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		for(int j=1;j<=K;j++)
		{
			if(j!=K) build(x+(j-1)*n,y+j*n,1);
			else build(x+(j-1)*n,y,1);
		}
	}
	printf("%d\n",work());
	return 0;
}