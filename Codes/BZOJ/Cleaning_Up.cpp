#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int a[40005];
int pre[40005], pos[40005], cnt[40005];
int f[40005];
int main()
{
	memset(f,0x3f,sizeof(f));
	int n,k;
	scanf("%d%d",&n,&k);
	int m = sqrt(n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	f[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			if(pre[a[i]] <= pos[j])
				cnt[j]++;
		pre[a[i]] = i;
		for (int j = 1; j <= m; j++)
			if(cnt[j] > j)
			{
				pos[j]++;
				while(pre[a[pos[j]]] > pos[j]) pos[j]++;
				cnt[j]--;
			}
		for (int j = 1; j <= m; j++)
			f[i] = min(f[i], f[pos[j]] + j * j);
	}
	printf("%d", f[n]);
}