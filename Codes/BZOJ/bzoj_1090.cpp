#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
char s[105];
int n;
int f[105][105];
int Judge(int i, int k, int l, int r)
{
	if ((r - i + 1) % (k - i + 1))
		return 0;
	int len = k - i + 1;
	for (int j = l; j <= r; j++)
	{
		int H = (j - l) % len;
		if(H == 0) H = len;
		if(s[i + H] != s[j])
			return 0;
	}
	return 1;
}
void DP()
{
	for (int l = 1; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			f[i][j] = l;
			for (int k = i; k < j; k++)
			{
				if (Judge(i, k, i, j))
					f[i][j] = min(f[i][j], f[i][k] + 3 + (int)floor(log10(l / (k - i + 1))));
				f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
			}
		}
	}
}
int main()
{
	//freopen("1.out", "w", stdout);
	scanf("%s", s + 1);
	memset(f, 0x3f, sizeof(f));
	n = strlen(s + 1);
	DP();
	//printf("%d\n", f[6][14]);
	printf("%d\n", f[1][n]);
}