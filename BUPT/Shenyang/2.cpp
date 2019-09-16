#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 200005
using namespace std;
int T,n,m,K;
struct ro{
	int to,next;
}road[N*2],roa[N*2];
int zz1,zz2;
int a[N],A[N];
void build1(int x,int y)
{
	zz1++;
	roa[zz1].to=y;
	roa[zz1].next=a[x];
	a[x]=zz1;
}
void build2(int x,int y)
{
	zz2++;
	road[zz2].to=y;
	road[zz2].next=A[x];
	A[x]=zz2;
}
int fa[N],size[N];
bool bj[N];
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void hb(int x,int y)
{
	if(find(x)==find(y))return;
	size[find(x)]+=size[fa[y]];
	fa[find(y)]=find(x);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		zz1=0,zz2=0;
		memset(A,0,sizeof(A));
		memset(a,0,sizeof(a));
		memset(fa,0,sizeof(fa));
		memset(size,0,sizeof(size));
		memset(bj,0,sizeof(bj));
		scanf("%d%d%d",&n,&m,&K);
		for(int i=1;i<=n;i++) fa[i]=i,size[i]=1;
		for(int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			build1(x,y);
			build1(y,x);
		}
		for(int i=1;i<=K;i++)
		{
			int x;
			scanf("%d",&x);
			bj[x]=1;
		}
		for(int i=1;i<=n;i++)
		{
			if(bj[i])continue;
			for(int j=a[i];j;j=roa[j].next)
			{
				int y=roa[j].to;
				if(bj[y])continue;
				hb(i,y);
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(!bj[i])continue;
			for(int j=a[i];j;j=roa[j].next)
			{
				int y=roa[j].to;
				if(!bj[y])
				{
					build2(i,n+find(y));
					build2(n+find(y),i);
					size[n+find(y)]=size[find(y)];
				}
				else
				{
					if(i<y)
					{
						build2(i,y);
						build2(y,i);
					}
				}
			}
		}
		
		double ans=-1;
		for(int i=A[find(1)+n];i;i=road[i].next)
		{
			int y=road[i].to;
			double sm=0;
			int js=0;
			for(int j=A[y];j;j=road[j].next)
			{
				js++;
				int to=road[j].to;
				if(to==find(1)+n||to<=n)continue;
				sm+=size[to];
			}
			sm/=1.0*js;
			sm+=size[find(1)+n];
			if(sm>ans) ans=sm;
		}
		printf("%.7f\n",ans);
	}
	return 0;
}
/*
3
7 6 2
1 2
1 3
2 5
2 4
3 6
4 7
2 3
7 7 2
1 2
1 3
2 5
2 4
3 6
4 7
2 4
2 3
4 5 2
1 2
1 3
3 4
2 4
2 3
2 3
*/