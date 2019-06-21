#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int MOD = 1e9 + 7;
struct Matrix
{
	long long a[1005];
	int n;
	Matrix(int x)
	{
		n = x;
		memset(a, 0, sizeof(a));
	}
	Matrix operator*(const Matrix &b)
	{
		Matrix ans(n);
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				int t = (i - k + n) % n;
				ans.a[i] = (ans.a[i] + a[k] * b.a[t]) % MOD;
			}
		}
		return ans;
	}
	Matrix operator^(const int b)
	{
		Matrix c = *this, ans(n);
		ans.a[0] = 1;
		int k = b;
		while (k)
		{
			if (k & 1)
				ans = ans * c;
			k >>= 1;
			c = c * c;
		}
		return ans;
	}
};
long long pow_mod(long long a, int b, int p)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return ans;
}
bool flag[1005];
int map[1005];
int rt;
int main()
{
	int n, m, M, a;
	scanf("%d%d%d", &n, &m, &M);
	for (int i = 1; i <= M; i++)
	{
		bool no = 0;
		memset(flag, 0, sizeof(flag));
		for (int j = 1; j <= M - 1; j++)
		{
			int now = pow_mod(i, j, M);
			if (!flag[now])
				flag[now] = 1;
			else
			{
				no = 1;
				break;
			}
		}
		if (!no)
		{
			rt = i;
			break;
		}
	}
	for (int i = 0; i <= M - 2; i++)
	{
		map[pow_mod(rt, i, M)] = i;
	}
	Matrix A(M - 1);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a);
		A.a[map[a]] = (A.a[map[a]] + pow_mod(n, MOD - 2, MOD)) % MOD;
	}
	A = A ^ m;
	long long ans = 0;
	for (int i = 0; i <= M - 2; i++)
	{
		ans = (ans + A.a[i] * pow_mod(rt, i, M)) % MOD;
	}
	printf("%lld\n",ans);
}