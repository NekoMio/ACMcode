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
const int MOD = 1073741824;
const int MAXN = 5005;
int prime[MAXN + 2], cnt, mu[MAXN + 2];
bool isnprime[MAXN + 2];
int gcd[MAXN + 2][MAXN + 2];
void Get_mu()
{
	isnprime[1] = 1;
	mu[1] = 1;
	for (register int i = 2; i <= MAXN; i++)
	{
		if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
		for (register int j = 1; j <= cnt; j++)
		{
			if (i * prime[j] > MAXN) break;
			isnprime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
}
inline int Calc(int i, int d, int B)
{
	int ans = 0;
	for (register int j = 1; j <= B / d; j++)
		(gcd[i][d * j] == 1) ? ans += (B / (j * d)) : 0;
	return ans;
}
inline int g(int x, int y)
{
	if (x && y) return x < y ? gcd[x][y - x] : gcd[x - y][y];
	else return x | y;
}
int main()
{
	// freopen ("1.out", "w", stdout);
	Get_mu();
	int A = read(), B = read(), C = read();
	if (B > C) swap(B, C);
	register int i, j, d;
	for (i = 0; i <= MAXN; i++)
		for (j = 0; j <= MAXN; j++)
			gcd[i][j] = g(i, j);
	int ans = 0;
	for (i = 1; i <= A; i++)
		for (d = 1; d <= B; d++)
			mu[d] ? ans += mu[d] * (A / i) * Calc(i, d, B) * Calc(i, d, C) : 0;
	printf ("%d\n", (ans & 0x3fffffff));
}