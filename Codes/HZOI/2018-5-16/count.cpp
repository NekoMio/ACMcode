#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MOD = 1e9 + 7;
int h[105];
int f[2][105][1005][3];
int main()
{
	int n = read(), L = read();
	if (n == 1) return printf ("1"), 0;
	for (int i = 1; i <= n; i++) h[i] = read();
	sort(h + 1, h + n + 1);
	f[0][1][0][2] = 1, f[0][1][0][1] = 2;
	int now = 0;
	for (int i = 1; i < n; i++)
	{
		now ^= 1;
		memset (f[now], 0, sizeof (f[now]));
		for (int j = 1; j <= i; j++)
		{
			for (int k = 0; k <= L; k++)
			{
				for (int l = 0; l <= 2; l++)
				{
					if (f[now ^ 1][j][k][l])
					{
						int nxt = k + (h[i + 1] - h[i]) * (2 * j + l - 2);
						if (nxt > L) continue;
						if (l)
						{
							f[now][j][nxt][l - 1] = (f[now][j][nxt][l - 1] + 1ll * f[now ^ 1][j][k][l] * l % MOD) % MOD;
							f[now][j + 1][nxt][l - 1] = (f[now][j + 1][nxt][l - 1] + 1ll * f[now ^ 1][j][k][l] * l % MOD) % MOD;
						}
						f[now][j - 1][nxt][l] = (f[now][j - 1][nxt][l] + 1ll * f[now ^ 1][j][k][l] * (j - 1) % MOD) % MOD;
						f[now][j + 1][nxt][l] = (f[now][j + 1][nxt][l] + 1ll * f[now ^ 1][j][k][l] * (j - 1 + l) % MOD) % MOD;
						f[now][j][nxt][l] = (f[now][j][nxt][l] + 1ll * f[now ^ 1][j][k][l] * (2 * j - 2 + l) % MOD) % MOD;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= L; i++)
		ans = (ans + f[now][1][i][0]) % MOD;
	printf ("%d\n", ans);
}
