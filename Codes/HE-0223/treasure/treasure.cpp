// WildRage treasure T2

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
long long f[13][(1 << 12) + 1], g[(1 << 12) + 1];
long long mp[13][13];
int Log[(1 << 12) + 1];
long long v[(1 << 12) + 1], p[(1 << 12) + 1], ref[(1 << 12) + 1];
int main()
{
	freopen ("2017treasure.in", "r", stdin);
	freopen ("2017treasure.out", "w", stdout);
	int n = read(), m = read();
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			mp[i][j] = mp[j][i] = 10000000000ll;
		}
	}
	// memset(mp, 0x0f, sizeof (mp));
	int a, b;
	for (int i = 1; i <= m; i++)
	{
		a = read() - 1, b = read() - 1;
		mp[a][b] = min(min(mp[a][b], mp[b][a]), (long long)read());
		mp[b][a] = mp[a][b];
	}
	int N = (1 << n) - 1;
	memset (f, 0x3f, sizeof (f));
	for (int i = 0; i < n; i++) Log[1 << i] = i;
	for (int i = 0; i < n; i++) f[0][1 << i] = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			int T = 0;
			for (int s = 0; s < n; s++) 
			{
				if (!(j & (1 << s)))
				{
					v[T] = 10000000000ll;
					p[T] = 1 << s;
					for (int k = j; k != 0; k -= (k & -k))
					{
						int nxt = Log[k & -k];
						v[T] = min(v[T], mp[s][nxt] * (i + 1));
						// printf("%d\n", v[T]);
					}
					T++;
				}
			}
			// printf ("%d\n", T);
			for (int s = 1; s < (1 << T); s++)
			{
				g[s] = g[s - (s & -s)] + v[Log[s & -s]];
				ref[s] = ref[s - (s & -s)] | p[Log[s & -s]];
				f[i + 1][j | ref[s]] = min(f[i + 1][j | ref[s]], f[i][j] + g[s]);
			}
		}
		
	}
	// for (int i = 0; i <= n; i++)
	// 	for (int j = 0; j <= (1 << n) - 1; j++)
	// 		printf ("%lld%c", f[i][j], " \n"[j == (1 << n) - 1]);
	long long ans = 0x0f0f0f0f0f0f0f0fll;
	for (int i = 0; i <= n; i++)
		ans = min(ans, f[i][N]);
	printf ("%lld", ans);
	//fclose(stdin), fclose(stdout);
	return 0;
}
