/*
 * @Author: WildRage 
 * @Date: 2017-07-02 16:07:15 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-07-02 17:58:06
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int a[1005], sum[10][1005],n;
int DP[1005][300];
bool had[10];
int N = (1 << 8) - 1;
vector<int> in[10];
int get_num(int p, int len)
{
	int now = lower_bound(in[a[p]].begin(), in[a[p]].end(), p) - in[a[p]].begin();
	int ans = now + len - 1;
	if (in[a[p]].size() - 1 < ans)
		return -1;
	return in[a[p]][ans];
}
int Judge(int len)
{
	memset(DP, 0, sizeof(DP));
	for (int i = 0; i < n; i++)
	{
		int to = get_num(i + 1, len);
		if (to != -1)
			DP[to][(1 << (a[i + 1] - 1))] = max(DP[i][0] + len, DP[to][1 << (a[i + 1] - 1)]);
		to = get_num(i + 1, len + 1);
		if (to != -1)
			DP[to][(1 << (a[i + 1] - 1))] = max(DP[i][0] + len + 1, DP[to][(1 << (a[i + 1] - 1))]);
		for (int j = 1; j < N; j++)
		{
			if (DP[i][j])
			{
				DP[i + 1][j] = max(DP[i + 1][j], DP[i][j]);
				if (j & (1 << (a[i + 1] - 1)))
					continue;
				to = get_num(i + 1, len);
				if (to != -1)
					DP[to][j | (1 << (a[i + 1] - 1))] = max(DP[i][j] + len, DP[to][j | (1 << (a[i + 1] - 1))]);
				to = get_num(i + 1, len + 1);
				if (to != -1)
					DP[to][j | (1 << (a[i + 1] - 1))] = max(DP[i][j] + len + 1, DP[to][j | (1 << (a[i + 1] - 1))]);
			}
			DP[i + 1][N] = max(DP[i + 1][N], DP[i][N]);
		}
	}
	return DP[n][N];
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		had[a[i]] = 1;
		in[a[i]].push_back(i);
	}
	int ans = 0;
	for(int i=1;i<=8;i++)if(had[i])ans++;
	int l = 1, r = 256;
	while (l <= r)
	{
		int mid = l + r >> 1;
		int x = Judge(mid);
		ans = max(x, ans);
		if (x)
			l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%d", ans);
}
