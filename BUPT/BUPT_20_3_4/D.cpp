#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#define N 100005
using namespace std;
double p[N];
int n;
int zz;
struct ro{
	int to,next;
}road[N*2];
int fa[N],b[N],a[N];
void build(int x,int y)
{
	zz++;
	road[zz].to=y;
	road[zz].next=a[x];
	a[x]=zz;
}
double f[N][2];
void dfs2(int x)
{
	for(int i=a[x];i;i=road[i].next)
	{
		int y=road[i].to;
		if(y==fa[x])	continue;
		fa[y]=x;
		dfs2(y);
		f[x][0]+=f[y][0]*p[y]+(f[y][1]+1)*(1.0-p[y]);
		f[x][1]+=f[y][0]*p[y]+f[y][1]*(1.0-p[y]);
	}
}
int main()
{
	scanf("%d",&n);
	fa[0]=-1;
	for(int i=1;i<=n;i++)scanf("%lf",&p[i-1]);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		build(x,y);
		build(y,x);
	}
	
	dfs2(0);
	printf("%.6f\n",f[0][0]*p[0]+(f[0][1]+1)*(1.0-p[0]));
	return 0;
}
/*
5
0.36 0.69 0.49 0.95 0.66
2 3
0 3
3 4
2 1
*/
