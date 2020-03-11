#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<queue>
#define N 10005
#define M 100005
using namespace std;
int n,K,zz,zz3;
int a[N],A[N];
struct ro{
	int to,next;
}road[M],roa[M];
void build2(int x,int y)
{
	zz3++;
	roa[zz3].to=y;
	roa[zz3].next=A[x];
	A[x]=zz3;
}
void build(int x,int y)
{
	zz++;
	road[zz].to=y;
	road[zz].next=a[x];
	a[x]=zz;
}
int dfn[N],zz1,st[N],top,low[N],zz2,bel[N];
int rd[N];
void dfs(int x)
{
	zz1++;
	dfn[x]=low[x]=zz1;
	top++;
	st[top]=x;
	rd[x]=1;
	for(int i=a[x];i;i=road[i].next)
	{
		int y=road[i].to;
		if(!dfn[y])
		{
			dfs(y);
			low[x]=min(low[y],low[x]);
		}
		else if(rd[y])
		{
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x])
	{
		zz2++;
		int v;
		do{
			v=st[top];
			top--;
			bel[v]=zz2;
			rd[v]=0;
		}while(dfn[v]!=low[v]);
	}
}
int dl[N];
int vis[N];
queue<int> q1;
int main()
{
	scanf("%d%d",&K,&n);
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		int aa,bb,cc;
		char aaa,bbb,ccc;
//		scanf("%d%c%d%c%d%c",&x,&a,&y,&b,&z,&c);
		scanf("%d %c",&x,&aaa);
		cout<<x<<' '<<aaa<<' '<<y<<' '<<bbb<<' '<<z<<' '<<ccc<<endl;
    // return 0;
		scanf("%d %c",&y,&bbb);
		scanf("%d %c",&z,&ccc);
		aa=(aaa=='R');
		bb=(bbb=='R');
		cc=(ccc=='R');
		build(x+(aa^1)*K,y+bb*K);
		build(x+(aa^1)*K,z+cc*K);
		
		build(y+(bb^1)*K,x+aa*K);
		build(y+(bb^1)*K,z+cc*K);
		
		build(z+(cc^1)*K,x+aa*K);
		build(z+(cc^1)*K,y+bb*K);
	}
	for(int i=1;i<=K*2;i++)
	{
		if(!dfn[i])
		{
			dfs(i);
		}
	}
	for(int i=1;i<=K;i++)
	{
		if(bel[i]==bel[i+K])
		{
			printf("-1\n");
			exit(0);
		}
		dl[bel[i]]=bel[i+K];
		dl[bel[i+K]]=bel[i];
	}
	memset(rd,0,sizeof(rd));
	for(int i=1;i<=K*2;i++)
	{
		for(int j=a[i];j;j=road[j].next)
		{
			int y=road[j].to;
			if(bel[y]==bel[i])continue;
			build2(bel[y],bel[i]);
			rd[bel[i]]++;
		}
	}
	for(int i=1;i<=zz2;i++)
	{
		if(!rd[i]&&!vis[i])
		{
			q1.push(i);
			vis[i]=1;
			vis[dl[i]]=2;
		}
	}
	while(!q1.empty())
	{
		int x=q1.front();q1.pop();
		for(int i=A[x];i;i=roa[i].next)
		{
			int y=roa[i].to;
			rd[y]--;
			if(!rd[y]&&!vis[y])
			{
				vis[y]=1;
				q1.push(y);
				vis[dl[y]]=2;
			}
		}
	}
	for(int i=1;i<=K;i++)
	{
		if(vis[bel[i]]==1) printf("B");
		else printf("R");
	}
	return 0;
}
/*
7 5
3 R 5 R 6 B
1 B 2 B 3 R
4 R 5 B 6 B
5 R 6 B 7 B
1 R 2 R 4 R
*/
