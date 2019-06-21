#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1000005],b[10005];
int next[10005];
void Get_next(int m)
{
	int j = 0, k = -1;
	next[0] = -1;
	while(j < m)
		if(k == -1 || b[j] == b[k])
			j++, k++, next[j] = k;
		else
			k = next[k];
}
int Kmp(int n, int m)
{
	int i = 0, j = 0;
	while(i < n)
	{
		if(j == -1 || a[i] == b[j])
			i++, j++;
		else
			j = next[j];
		if(j == m)
			return i;
	}
	return -1;
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d", a + i);
		for (int i = 0; i < m; i++)
			scanf("%d", b + i);
		Get_next(m);
		int ans = Kmp(n, m);
		if(ans == -1)
			printf("-1\n");
		else
			printf("%d\n", ans - m + 1);
	}
}