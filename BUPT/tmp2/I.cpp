#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define N 100005
using namespace std;
int T,n;
struct no{
	int x,y;
}node[N];
map<int,int> ma;
int A[N*2],op,zz;
int cnt[2][N];
int B[2][N];
int tmp[2][2];
int bj[2][N];
long long sm1,sm2;
bool cmp(int x,int y)
{
	return cnt[op][x]>cnt[op][y];
}
int main()
{
	scanf("%d",&T);
	int cc=0;
	while(T--)
	{
		scanf("%d",&n);
		ma.clear();
		zz=0;
		memset(bj,0,sizeof(bj));
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&node[i].x,&node[i].y);
			if(!ma[node[i].x]) ma[node[i].x]=1,zz++,A[zz]=node[i].x;
			if(!ma[node[i].y]) ma[node[i].y]=1,zz++,A[zz]=node[i].y;
		}
		if(n==2)
		{
			cc++;
			printf("Case %d: 2 1\n",cc);
			continue;
		}
		sort(A+1,A+zz+1);
		for(int i=1;i<=zz;i++) ma[A[i]]=i;
		for(int i=1;i<=n;i++)
		{
			node[i].x=ma[node[i].x];
			node[i].y=ma[node[i].y];
			cnt[0][node[i].x]++;
			cnt[1][node[i].y]++;
		}
		for(int i=1;i<=zz;i++)
		{
			B[0][i]=i;
			B[1][i]=i;
		}
		op=0;
		sort(B[0]+1,B[0]+zz+1,cmp);
		op=1;
		sort(B[1]+1,B[1]+zz+1,cmp);
		op=0;
		memset(tmp,0,sizeof(tmp));
		tmp[0][0]=1;
		bj[0][B[0][1]]=1;
		bj[1][B[1][1]]=1;
		for(int i=2;i<=zz;i++)
		{
			if(cnt[0][B[0][i]]==cnt[0][B[0][i-1]])
			{
				tmp[0][op]++;
				
				bj[0][B[0][i]]=op+1;
			}
			else if(op==0&&cnt[0][B[0][i]]==cnt[0][B[0][i-1]]-1)
			{
				op=1;
				tmp[0][op]++;
				bj[0][B[0][i]]=op+1;
			}
			else break;
		}
		op=0;
		tmp[1][0]=1;
		for(int i=2;i<=zz;i++)
		{
			if(cnt[1][B[1][i]]==cnt[1][B[1][i-1]])
			{
				tmp[1][op]++;
				bj[1][B[1][i]]=op+1;
			}
			else if(op==0&&cnt[1][B[1][i]]==cnt[1][B[1][i-1]]-1)
			{
				op=1;
				tmp[1][op]++;
				bj[1][B[1][i]]=op+1;
			}
			else break;
		}
		sm1=1ll*tmp[0][0]*tmp[1][0];
		sm2=1ll*tmp[0][1]*tmp[1][0]+1ll*tmp[0][0]*tmp[1][1];
		long long su=sm1;
		for(int i=1;i<=n;i++)
		{
			int x=bj[0][node[i].x],y=bj[1][node[i].y];
			if(x==1&&y==1) sm1--;
			if(x==1&&y==2) sm2--;
			if(x==2&&y==1) sm2--;
		}
		cc++;
		
		if(sm1)
		{
			if(cnt[0][B[0][1]]+cnt[1][B[1][1]]==2) sm1/=2;
			printf("Case %d: %d %lld\n",cc,cnt[0][B[0][1]]+cnt[1][B[1][1]],sm1);
		}
		else
		{
			if(cnt[0][B[0][1]]+cnt[1][B[1][1]]-1==2)  printf("Case %d: %d %lld\n",cc,cnt[0][B[0][1]]+cnt[1][B[1][1]]-1,(sm2+su)/2);
			else printf("Case %d: %d %lld\n",cc,cnt[0][B[0][1]]+cnt[1][B[1][1]]-1,(sm2+su));
		} 
	}
	return 0;
}
/*
5
5
1 2
1 3
2 3
4 5
6 7
3
1 2
2 3
3 1
4
1 1
2 2
3 3
4 4
2 
1 1
1 2
3
1 1
1 2
2 3
*/