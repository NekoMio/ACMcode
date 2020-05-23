#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<map>
#define N 100005
using namespace std;
int n,K;
long long lc,pc,lm,pm,t,d;
int A[N];
long long ans=1e18;
long long sm[N],to[N],sum;
int l1,l2;
int main()
{
	scanf("%d%d",&n,&K);
	scanf("%lld%lld%lld%lld",&lc,&pc,&lm,&pm);
	scanf("%lld%lld",&t,&d);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	sort(A+1,A+n+1);
	
	for(int i=1;i<=n;i++)
	{
		if(A[i]<lm)
		{
			l1=i;
		}
		else break;
	}
	for(int i=l1;i;i--)
	{
		sm[i]=sm[i+1]+lm-A[i];
		to[i]=A[i];
	}
	for(int i=l1+1;i<=n;i++)
	{
		if(A[i]-d>=lm) to[i]=A[i]-d,sum+=d;
		else to[i]=lm,sum+=A[i]-lm;	
	}
	int zz1=n+1;

	if(sm[1]<=sum&&A[1]+d>=lm)
	{
		ans=1ll*sm[1]*t+1ll*n*pm;
	}
	if(K!=1)
	{
		long long tmp=0;
		for(int i=1;i<=n;i++)
		{
			if(A[i]>d) sum+=d;
			else sum+=A[i]-1;
			if((i+(K-2))/(K-1)>n-zz1+1)
			{
				zz1--;
				if(A[zz1]<lc)
				{
					tmp+=lc-A[zz1];
					sum-=A[zz1]-to[zz1];
				}
				else if(to[zz1]<lc)
				{
					sum-=lc-to[zz1];
				}
				if(A[zz1]+d<lc)
				{
					break;
				}
			}
					
			if(A[i+1]+d<lm&&zz1>i+1) continue;
			if(sm[i+1]-sm[zz1]+tmp<=sum&&zz1>i)
			{
				ans=min(ans,1ll*t*(sm[i+1]-sm[zz1]+tmp)+1ll*(n-zz1+1)*pc+1ll*(zz1-i-1)*pm);
			}
		}
	}
	if(ans==1e18) printf("-1\n");
	else printf("%lld\n",ans);
	return 0;
}
/*
5 3
7 5 4 3
2 3
1 3 5 6 9
*/
