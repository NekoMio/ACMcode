#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 65
using namespace std;
int n;
int A[N*N],cnt1[2000],cnt2[2000];
int zz,ans[100005][N];
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
		if(!cnt1[abs(A[x]-ans[zz][i])])
		{
			yx=0;
			break;
		}
	}
	if(yx)
	{
		for(int i=2;i<=ans[zz][0];i++)
		{
			cnt1[abs(A[x]-ans[zz][i])]--;
			cnt2[abs(A[x]-ans[zz][i])]++;
		}
		cnt1[abs(A[x]-ans[zz][1])]--;
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
		cnt1[abs(A[x]-ans[zz][1])]++;
	}
	yx=1;
	int tmp=ans[zz][2]-A[x];
	for(int i=1;i<=ans[zz][0];i++)
	{
		if(!cnt1[abs(tmp-ans[zz][i])])
		{
			
			yx=0;
			break;
		}
	}

	if(yx)
	{
		for(int i=2;i<=ans[zz][0];i++)
		{
			cnt1[abs(tmp-ans[zz][i])]--;
			cnt2[abs(tmp-ans[zz][i])]++;
		}
		cnt1[abs(tmp-ans[zz][1])]--;
		ans[zz][0]++;
		ans[zz][ans[zz][0]]=tmp;
	
		dfs(x-1);
		ans[zz][ans[zz][0]]=0;
		ans[zz][0]--;
		for(int i=2;i<=ans[zz][0];i++)
		{
			cnt1[abs(tmp-ans[zz][i])]++;
			cnt2[abs(tmp-ans[zz][i])]--;
		}
		cnt1[abs(tmp-ans[zz][1])]++;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n*(n-1)/2;i++)
	{
		scanf("%d",&A[i]);
		cnt1[A[i]]++;
	}
	zz++;
	cnt1[A[n*(n-1)/2]]--;
	ans[zz][0]=2;
	ans[zz][1]=0;ans[zz][2]=A[n*(n-1)/2];
	if(ans[zz][2]>999)
	{
		printf("0\n");
		return 0;
	}
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
10
17 24 31 41 55 67 84 98 110 115 122 127 139 142 166 167 194 197 221 225 249 262 264 281 309 333 364 388 391 429 431 448 530 554 558 571 585 595 626 652 669 693 710 779 820


0 41 262 429 571 595 626 693 710 820
10
1 4 5 7 7 7 14 15 15 15 19 21 22 22 22 22 22 26 29 29 36 37 37 41 43 44 44 44 48 51 58 58 59 63 65 65 66 70 80 87 102 109 123 124 128
*/
