#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<queue>
#define N 505
using namespace std;
int n,m;
int a[N][N];
int d[N][N];
int zz;
struct ro{
	int to,next,l;
}road[N*N];
int A[N];
void build(int x,int y,int z)
{
	zz++;
	road[zz].to=y;
	road[zz].next=A[x];
	road[zz].l=z;
	A[x]=zz;
}
queue<int> q1;
int dis[N];
int D[N][N]; 
bool rd[N];
void bfs(int S)
{
	q1.push(S);
	rd[S]=1;
	memset(dis,0,sizeof(dis));
	dis[S]=0x7fffffff;
	while(!q1.empty())
	{
		int x=q1.front();q1.pop();
		rd[x]=0;
		for(int i=A[x];i;i=road[i].next)
		{
			int y=road[i].to;
			if(dis[y]<min(dis[x],road[i].l))
			{
				dis[y]=min(dis[x],road[i].l);
				if(!rd[y])
				{
					rd[y]=1;
					q1.push(y);
				}
			}
		}
	}
	for(int i=1;i<=m;i++) D[S][i]=dis[i];
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			if(!a[i][j]) a[i][j]=1000005;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int l=j+1;l<=m;l++)
			{
				if(a[i][j]<a[i][l]) d[j][l]++;
				else if(a[i][j]>a[i][l]) d[l][j]++;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(d[i][j]>d[j][i]) build(i,j,d[i][j]);
		}
	}
	
	for(int i=1;i<=m;i++)bfs(i);
	for(int i=1;i<=m;i++)
	{
		bool yx=1;
		for(int j=1;j<=m;j++)
		{
			if(j==i)continue;
			if(D[i][j]<D[j][i])
			{
				yx=0;
				break;
			}
		}
		if(yx) printf("%d ",i);
	}
	return 0;
}
/*
5 6
1 B 3 R 4 B
2 B 3 R 4 R
1 B 2 R 3 R
3 R 4 B 5 B
3 B 4 B 5 B
1 R 2 R 4 R
*/