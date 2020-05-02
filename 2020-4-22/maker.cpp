#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<map>
#include<ctime>
#define N 200005
using namespace std;
struct no{
	int x,y;
}node[N];
int zz,B[N],f[N][10];
int main()
{
	freopen("test.in","w",stdout);
	int T=20;
	printf("%d\n",T);
	while(T--)
	{
		int n=100000,K=100000;
		printf("%d %d\n",n,K);
		for(int i=1;i<=K;i++)
		{
			int x=rand()*rand()%n+1,y=rand()*rand()%n+1;
			printf("%d %d\n",x,y);
			node[i].x=x,node[i].y=y;
		}
		int Q=10;
		printf("%d\n",Q);
		
		for(int i=1;i<=Q;i++)
		{
			int x=rand()*rand()%n+1,y=rand()*rand()%n+1;
			long long sm=0;
			for(int j=1;j<=K;j++)
			{
				if(node[i].x<=x&&node[i].y<=y)
				{
					sm+=x-node[i].x+y-node[i].y;
				}
			}
			printf("%lld\n",sm);
		}
		printf("\n");
	}
	return 0;
}
/*
2
6 7
1 2 3 1 2 3
2
1 3 1
2
1 1 2
2
1 6 2
2
3 5
1 2 3
2
1 3 2
2
1 1 2
2
*/
