#include<bits/stdc++.h>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

typedef long long LL;

const int maxn=5e5+5, MX=30;
const int inf=522133279;

int n,k,root,son[maxn][2],p[maxn];

int f[maxn][MX+2],nmax[maxn],deep[maxn];
void dfs_dp(int k)
{
	nmax[k]=k;
	int l=son[k][0], r=son[k][1];
	if (l)
	{
		deep[l]=deep[k]+1;
		dfs_dp(l);
	}
	if (r)
	{
		deep[r]=deep[k]+1;
		dfs_dp(r);
		nmax[k]=max(nmax[k],nmax[r]);
	}
	f[k][1]=1;
	fo(j,2,MX) f[k][j]=min(f[k][j],min(f[l][j-1]+f[r][j-2],f[l][j-2]+f[r][j-1])+1);
}

int tag[maxn],maxdeep[maxn],num[maxn],h[MX+2];
void Make_tag(int st)
{
	for(int x=st; x!=-1; x=p[x])
	{
		maxdeep[x]=max(maxdeep[x],deep[st]);
		num[x]++;
		int y=p[x];
		if (y!=-1 && son[y][0]==x) tag[son[y][1]]=max(tag[son[y][1]],maxdeep[x]-1-deep[y]);
	}
}
bool check(int x)
{
	if (num[x]) return 1;
	int nowdeep=0, nownum=0;
	memset(h,31,sizeof(h));
	h[0]=f[son[x][1]][0], h[1]=f[son[x][1]][1];
	for(; x!=-1; x=p[x])
	{
		int y=p[x];
		nownum++;
		if (nowdeep+1<tag[x])
		{
			nownum+=h[nowdeep=tag[x]-1];
			if (nownum>=inf) return 0;
			fd(i,MX,nowdeep) if (h[i]<inf) h[i]-=h[nowdeep];
		}
		nowdeep++;
		fd(i,MX,nowdeep) h[i]=h[i-1];
		if (y!=-1 && son[y][0]==x && son[y][1])
		{
			int r=son[y][1], t=max(tag[r],nowdeep-1);
			if (f[r][t]>=inf) return 0;
			nownum+=f[r][t];
			fd(i,MX,nowdeep+1)
			{
				h[i]=min(h[i-1]+f[r][i]-f[r][t],h[i]+f[r][i-1]-f[r][t]);
				if (h[i]>n) h[i]=inf;
			}
			h[nowdeep]=0;
		} else if (y!=-1 && son[y][1]==x && son[y][0])
		{
			int l=son[y][0];
			if (nowdeep-(maxdeep[l]-deep[y])>1) return 0;
			nowdeep=max(nowdeep,maxdeep[l]-deep[y]);
			h[nowdeep]=0;
			nownum+=num[son[y][0]];
		}
	}
	return nownum<=k;
}

bool ans[maxn];
int main()
{
	scanf("%d %d",&n,&k);
	fo(i,1,n)
	{
		scanf("%d",&p[i]);
		if (p[i]==-1) root=i; else son[p[i]][(i>p[i])]=i;
	}
	
	memset(f,31,sizeof(f));
	fo(i,0,n) f[i][0]=0;
	deep[root]=1;
	dfs_dp(root);
	
	fo(i,1,n) if (check(i))
	{
		ans[i]=1;
		Make_tag(i);
	}
	
	fo(i,1,n) putchar(ans[i] ?'1' :'0');
	puts("");
}