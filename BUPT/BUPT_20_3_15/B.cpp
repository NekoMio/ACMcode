#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2004
using namespace std;
int T,n,m,K;
char b[N];
int ma[N][N];
const int p=998244353;
long long sm[2][N],f[2][N],g[2][N],su[2][N];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&K);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",b+1);
			for(int j=1;j<=m;j++)
			{
				ma[i][j]=(b[j]=='1');
			}
			ma[i][0]=-1;
		}
		int nw=1,la=0;
		for(int i=1;i<=m;i++)
		{
			f[nw][i]=1;
			g[nw][i]=(ma[1][i]==ma[1][i-1]);
			sm[nw][i]=sm[nw][i-1]+f[nw][i];
			su[nw][i]=su[nw][i-1]+g[nw][i];
		}
		for(int i=2;i<=n;i++)
		{
			swap(nw,la);
			for(int j=1;j<=m;j++)
			{
				long long l,r;
				if(j-K>0) l=sm[la][j-K-1];
				else l=0;
				if(j+K<=m) r=sm[la][j+K];
				else r=sm[la][m];
				f[nw][j]=(r-l+p)%p;
				
				if(j-K>0) l=su[la][j-K];
				else l=0;
				if(j+K<=m) r=su[la][j+K];
				else r=su[la][m];
				f[nw][j]=(f[nw][j]-(r-l+p)%p+p)%p;
				
				if(j-1-K>0) l=sm[la][j-1-K];
				else l=0;
				if(j-1+K<=m) r=sm[la][j-1+K];
				else r=sm[la][m];
				g[nw][j]=(r-l+p)%p;
				
				if(j-K>0) l=su[la][j-K];
				else l=0;
				if(j-1+K<=m) r=su[la][j-1+K];
				else r=su[la][m];
				g[nw][j]=(g[nw][j]-(r-l+p)%p+p)%p;
				
				if(ma[i][j]!=ma[i][j-1]) g[nw][j]=0;
				
				sm[nw][j]=(sm[nw][j-1]+f[nw][j])%p;
				su[nw][j]=(su[nw][j-1]+g[nw][j])%p;
			}
		}
		long long ans=0;
		for(int i=1;i<=m;i++) ans+=(f[nw][i]-g[nw][i]+p)%p,ans%=p;
		printf("%lld\n",ans);
	}
	return 0;
}
/*
3
2 2 1
00
10
5 5 1
00100
10101
00100
01000
11101
1
5 5 2
00100
10101
00100
01000
11101
*/