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
const int INF = 0x3f3f3f3f;
template<typename _Tp, typename _T>
inline void gmin(_Tp &x, _T y)
{
    if (x > y) x = y;
}
int a[15][15];
int cnt[15], n, N;
int DP[11][11][11][11][(1 << 10) + 1];
int vis[11];
bool Cheak(int x, int len, int y)
{
    memset (vis, 0, sizeof (vis));
    for (int i = 1; i <= len; i++) vis[a[x][i]] = 1;
    len++;
    for (int i = 1; i <= cnt[y]; i++)
    {
        if (len <= cnt[x] && a[x][len] == a[y][i])
            vis[a[x][len]] = 1, len++;
        if (!vis[a[y][i]]) return 0;
    }
    if (len <= cnt[x]) return 0;
    return 1;
}
int ext[15][15];
int Catch[15][15][15];
int f(int y, int ylen, int x, int xlen, int S)
{
	printf ("%d %d %d %d %d\n", y - 1, ylen, x - 1, xlen, S);
    if (DP[y][ylen][x][xlen][S] != -1) return DP[y][ylen][x][xlen][S];
	DP[y][ylen][x][xlen][S] = INF;
    if (S == N && ylen == 1 && xlen == cnt[x]) return DP[y][ylen][x][xlen][S] = 0;
	if (y && ylen == 1)
	{
		for (int i = 1; i <= n; i++) if (!(S & (1 << (i - 1))))
			for (int j = 0; j <= cnt[i]; j++)
				if (Catch[i][j][y])
					gmin(DP[y][ylen][x][xlen][S], f(i, j + 1, x, xlen, S | (1 << (i - 1))));
		gmin(DP[y][ylen][x][xlen][S], f(0, 1, x, xlen, S));
	}
	else
	{
		for (int i = 1; i <= n; i++) if (!(S & (1 << (i - 1))))
			if (Catch[x][xlen][i])
				gmin(DP[y][ylen][x][xlen][S], f(y, ylen, i, 0, S | (1 << (i - 1))));
		for (int i = 1; i < 10; i++)
		{
			int a2 = (i == a[x][xlen + 1]);
			int a1 = (i == a[y][ylen - 1]);

			if (a1 && a2) gmin(DP[y][ylen][x][xlen][S], f(y, ylen - 1, x, xlen + 1, S) + 1);
			if (a1 && (ext[x][xlen] & (1 << i))) gmin(DP[y][ylen][x][xlen][S], f(y, ylen - 1, x, xlen, S) + 1);
			if (a2 && (ext[y][ylen] & (1 << i))) gmin(DP[y][ylen][x][xlen][S], f(y, ylen, x, xlen + 1, S) + 1);
		}
	}
	return DP[y][ylen][x][xlen][S];
}
bool Calc(int x, int len, int y)
{
	if (~ext[x][cnt[x]] & ext[y][cnt[y]]) return 0;
	int j = len + 1;
	for (int i = 1; i <= cnt[y]; i++)
		if (j <= cnt[x] && a[x][j] == a[y][i]) j++;
	return j == cnt[x] + 1;
}
int main()
{
	// freopen ("C.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
    {
        int x = read();
        while (x != 0) a[i][++cnt[i]] = x, x = read();
    	for (int j = 1; j <= cnt[i] + 1; j++) ext[i][j] = ext[i][j - 1] | (1 << a[i][j]);
	}
	ext[0][0] = ~0U;
    for (int i = 0; i <= n; i++)
		for (int k = 0; k <= cnt[i]; k++)
    		for (int j = 0; j <= n; j++) 
				if (i != j)
    				Catch[i][k][j] = Calc(i, k, j);
	memset (DP, -1, sizeof (DP));
    N = (1 << n) - 1;
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        gmin(ans, f(i, cnt[i] + 1, 0, 0, (1 << (i - 1))));
	printf ("%d\n", ans == INF ? -1 : ans);
}
