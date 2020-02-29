#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200005
using namespace std;
int n,K,zz,a[N];
struct ro{
	int to,next;
}road[N*2];
void build(int x,int y)
{
	zz++;
	road[zz].to=y;
	road[zz].next=a[x];
	a[x]=zz;
}
int fa[N],size[N];
int ans=0;
void dfs(int x)
{
	size[x]=1;
	for(int i=a[x];i;i=road[i].next)
	{
		int y=road[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		dfs(y);
		size[x]+=size[y];
	}
	if(size[x]>=K&&n-size[x]>=K)ans++;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		zz=0;
		scanf("%d%d",&n,&K);
		memset(a,0,sizeof(int)*(n+2));
		memset(fa,0,sizeof(int)*(n+2));
		memset(size,0,sizeof(int)*(n+2));
		for(int i=1;i<n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			build(x,y);
			build(y,x);
		}
		dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}
/*
*/