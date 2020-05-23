#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 65
using namespace std;
int n;
int A[N*N],cnt1[2000],cnt2[2000],cnt3[2000];
int zz,ans[100005][N],q1[N];
void dfs(int x)
{
	if(ans[zz][0]==n)
	{
		zz++;
		for(int i=0;i<=n;i++)
		{
			ans[zz][i]=ans[zz-1][i];
		}
		return;
	}
	if(x==0)return;
	if(cnt2[A[x]])
	{
		cnt2[A[x]]--;
		dfs(x-1);
		cnt2[A[x]]++;
		return;
	}
	bool yx=1;
	for(int i=1;i<=ans[zz][0];i++)
	{
		cnt3[abs(A[x]-ans[zz][i])]++;
	}
	for(int i=1;i<=ans[zz][0];i++)
	{
		if(cnt3[abs(A[x]-ans[zz][i])]>cnt1[abs(A[x]-ans[zz][i])])
		{
			yx=0;
			break;
		}
	}
	for(int i=1;i<=ans[zz][0];i++)
	{
		cnt3[abs(A[x]-ans[zz][i])]=0;
	}
	if(yx)
	{
		for(int i=2;i<=ans[zz][0];i++)
		{
			cnt1[abs(A[x]-ans[zz][i])]--;
			cnt2[abs(A[x]-ans[zz][i])]++;
		}
		cnt1[A[x]]--;
		ans[zz][0]++;
		ans[zz][ans[zz][0]]=A[x];
	
		dfs(x-1);
		ans[zz][ans[zz][0]]=0;
		ans[zz][0]--;
		for(int i=2;i<=ans[zz][0];i++)
		{
			cnt1[abs(A[x]-ans[zz][i])]++;
			cnt2[abs(A[x]-ans[zz][i])]--;
		}
		cnt1[A[x]]++;
	}
	yx=1;
	int tmp=ans[zz][2]-A[x];
	for(int i=1;i<=ans[zz][0];i++)
	{
		cnt3[abs(tmp-ans[zz][i])]++;
	}
	for(int i=1;i<=ans[zz][0];i++)
	{
		if(cnt3[abs(tmp-ans[zz][i])]>cnt1[abs(tmp-ans[zz][i])])
		{
			yx=0;
			break;
		}
	}
	for(int i=1;i<=ans[zz][0];i++)
	{
		cnt3[abs(tmp-ans[zz][i])]=0;
	}

	if(yx)
	{
		for(int i=1;i<=ans[zz][0];i++)
		{
			cnt1[abs(tmp-ans[zz][i])]--;
			cnt2[abs(tmp-ans[zz][i])]++;
		}
		cnt2[A[x]]--;
		ans[zz][0]++;
		ans[zz][ans[zz][0]]=tmp;
	
		dfs(x-1);
		ans[zz][ans[zz][0]]=0;
		ans[zz][0]--;
		for(int i=1;i<=ans[zz][0];i++)
		{
			cnt1[abs(tmp-ans[zz][i])]++;
			cnt2[abs(tmp-ans[zz][i])]--;
		}
		cnt2[A[x]]++;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n*(n-1)/2;i++)
	{
		scanf("%d",&A[i]);
	}
	if(A[n*(n-1)/2]>999)
	{
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n*(n-1)/2;i++)
	{
		cnt1[A[i]]++;
	}
	zz++;
	cnt1[A[n*(n-1)/2]]--;
	ans[zz][0]=2;
	ans[zz][1]=0;ans[zz][2]=A[n*(n-1)/2];
	
	dfs(n*(n-1)/2-1);
	zz--;
	for(int i=1;i<=zz;i++)
	{
		sort(ans[i]+1,ans[i]+n+1);
	}
	for(int i=1;i<=zz;i++)
	{
		for(int j=1;j<zz;j++)
		{
			for(int k=1;k<=n;k++)
			{
				if(ans[j][k]>ans[j+1][k])
				{
					swap(ans[j],ans[j+1]);
					break;
				}
				else if(ans[j][k]<ans[j+1][k])
				{
					break;
				}
				if(k==n)
				{
					for(int l=j+1;l<zz;l++)
					{
						swap(ans[l],ans[l+1]);
					}
					zz--;
				}
			}
		}
	}
	printf("%d\n",zz);
	for(int i=1;i<=zz;i++)
	{
		for(int j=1;j<=n;j++) printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
/*
4
1 3 5 6 7 8 
*/