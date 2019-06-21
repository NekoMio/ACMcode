#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100005][5], ans;
int N, D, K;
bool mark[100005];
int ansl;
bool check(int x)
{
	for (int i = 1; i <= D; i++)
		if(mark[a[x][i]])
			return 1;
	return 0;
}
void dfs(int L, int R, int l, int r, int k)
{
	while(r < R && check(r + 1)) r++;
	while(l > L && check(l - 1)) l--;
	if (ans < r - l + 1 || (ans == r - l + 1 && ansl > l))
	{
		ans = r - l + 1;
		ansl = l; 
	}
	if(k == K)
		return;
	if(r + 1 <= R)
	{
		for (int i = 1; i <= D; i++)
		{
			if(!mark[a[r + 1][i]])
			{
				mark[a[r + 1][i]] = 1;
				dfs(L, R, l, r + 1, k + 1);
				mark[a[r + 1][i]] = 0;
			}
		}
	}
	if(l - 1 >= L)
	{
		for (int i = 1; i <= D; i++)
		{
			if(!mark[a[l - 1][i]])
			{
				mark[a[l - 1][i]] = 1;
				dfs(L, R, l - 1, r, k + 1);
				mark[a[l - 1][i]] = 0;
			}
		}
	}
}
void Binary_Search(int l, int r)
{
	int mid = l + r >> 1;
	for (int i = 1; i <= D; i++)
	{
		mark[a[mid][i]] = 1;
		dfs(l, r, mid, mid, 1);
		mark[a[mid][i]] = 0;
	}
	if(l == r)
		return;
	Binary_Search(l, mid);
	Binary_Search(mid + 1, r);
}
int main()
{
	int T;
	scanf("%d", &T);
	int num = 0;
	while(T--)
	{
		num++;
		scanf("%d%d%d",&N, &D, &K);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= D; j++)
				scanf("%d", &a[i][j]);
		ans = 0, ansl = 0x3f3f3f;
		Binary_Search(1, N);
		printf("Case #%d: %d %d\n",num , ansl - 1, ans + ansl - 2);
	}
}