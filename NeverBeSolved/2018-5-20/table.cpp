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
int MOD;
const int MAXN = 4e6 + 5;
int F[MAXN];
int Inv[MAXN];
int powS[MAXN];
int pow_mod(long long a, long long b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
int C(int n, int m)
{
	if (n < m) return 0;
	if (n < 0 || m < 0) return 0;
	return 1ll * F[n] * Inv[n - m] % MOD * Inv[m] % MOD;
}
int main()
{
	int H = read(), W = read(), S = read();
	MOD = read();
	F[0] = 1;
	for (int i = 1; i <= MAXN - 5; i++) F[i] = 1ll * F[i - 1] * i % MOD;
	Inv[MAXN - 5] = pow_mod(F[MAXN - 5], MOD - 2);
	for (int i = MAXN - 6; i >= 0; i--) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
	int ans = 0;
	long long Sum = 1ll * H * W;
	H--, W--;
	int tmp = pow_mod(S + 1, Sum - 2 * W - 2 * H);
	for (int i = W - 1; i >= 0; i--)
	{
		ans = (ans + 1ll * tmp * C(i + H - 1, H - 1) % MOD * C(H + i + S + W - 1, S - H) % MOD) % MOD;
		tmp = 1ll * tmp * (S + 1) % MOD;
	}
	tmp = pow_mod(S + 1, Sum - 2 * H - 2 * W);
	for (int i = H - 1; i >= 0; i--)
	{
		ans = (ans + 1ll * tmp * C(i + W - 1, W - 1) % MOD * C(H + W + S + W - 1, S - i) % MOD) % MOD;
		tmp = 1ll * tmp * (S + 1) % MOD;
	}
	printf ("%d\n", ans);
}
