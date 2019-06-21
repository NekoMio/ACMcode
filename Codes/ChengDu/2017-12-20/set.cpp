#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int MAXN = 1e3 + 5;

long long f[MAXN][2], g[MAXN][2];
long long a[MAXN], A[MAXN];
int ans[MAXN], Ans[MAXN];

int main()
{
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
	int n = read();
	if (n > 10)
	{
		for (int i = 1; i <= n; i++)
			a[i] = read() ^ a[i - 1];
		memset (f, -1, sizeof (f));
		f[0][1] = f[0][0] = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (f[i][0] + f[i][1] < ((f[j][0] ^ a[i] ^ a[j]) + f[j][1]))
				{
					f[i][0] = f[j][0] ^ a[i] ^ a[j], f[i][1] = f[j][1];
					g[i][0] = -1, g[i][1] = j;
				}
				else if ((f[i][0] + f[i][1] == (f[j][0] ^ a[i] ^ a[j]) + f[j][1]) && f[i][0] > (f[j][0] ^ a[i] ^ a[j]))
				{
					f[i][0] = f[j][0] ^ a[i] ^ a[j], f[i][1] = f[j][1];
					g[i][0] = -1, g[i][1] = j;
				}
				if ((f[i][0] + f[i][1]) < f[j][0] + (f[j][1] ^ a[i] ^ a[j]))
				{
					f[i][0] = f[j][0], f[i][1] = f[j][1] ^ a[i] ^ a[j];
					g[i][0] = j, g[i][1] = -1;
				}
				else if (f[i][0] + f[i][1] == f[j][0] + (f[j][1] ^ a[i] ^ a[j]) && f[i][0] > f[j][0])
				{
					f[i][0] = f[j][0], f[i][1] = f[j][1] ^ a[i] ^ a[j];
					g[i][0] = j, g[i][1] = -1;
				}
			}
		}
		int now = n;
		while (now != 0)
		{
			if (g[now][0] >= 0)
			{
				for (int i = g[now][0] + 1; i <= now; i++)
					ans[i] = 2;
				now = g[now][0];
			}
			else
			{
				for (int i = g[now][1] + 1; i <= now; i++)
					ans[i] = 1;
				now = g[now][1];
			}
		}
		for (int i = 1; i <= n; i++)
			printf ("%d ", ans[i]);
	}
	else
	{
		for (int i = 1; i <= n; i++)
			A[i] = read();
		int N = (1 << n) - 1;
		long long Max = 0, Max1 = 0;
		for (int i = 0; i <= N; i++)
		{
			long long now = 0, now1 = 0;
			for (int j = 1; j <= n; j++)
				if (i & (1 << (j - 1))) now ^= A[j];
				else now1 ^= A[j];
			if (now + now1 > Max + Max1)
			{
				Max = now, Max1 = now1;
				for (int j = 1; j <= n; j++)
					if (i & (1 << (j - 1))) Ans[j] = 1;
					else Ans[j] = 2;
			}
			else if (now + now1 == Max + Max1 && now < Max)
			{
				Max = now, Max1 = now1;
				for (int j = 1; j <= n; j++)
					if (i & (1 << (j - 1))) Ans[j] = 1;
					else Ans[j] = 2;
			}
		}
		for (int i = 1; i <= n; i++)
			printf ("%d ", Ans[i]);
	}
	// while (1);
}
