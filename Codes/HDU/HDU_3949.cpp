#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct LinearBasis
{
	long long v[65];
	int n, t, cnt;
	void Build(long long *x, int n)
	{
		this->n = n;
		long long a[65];
		memset (a, 0, sizeof (a));
		for (int i = 1; i <= n; i++)
		{
			long long t = x[i];
			for (int j = 62; j >= 0; j--)
			{
				if ((t & (1ll << j)) == 0) continue;
				if (a[j]) t ^= a[j];
				else
				{
					for (int k = 0; k < j; k++) if (t & (1 << k)) t ^= a[k];
					for (int k = j + 1; k <= 62; k++) if (a[k] & (1ll << j)) a[k] ^= t;
					cnt++;
					a[j] = t;
					break;
				}
			}
		}
		t = cnt != n;
		for (int i = 0; i <= 62; i++) if (a[i]) v[++v[0]] = a[i];
		
	}
	long long Query(int k)
	{
		k -= t;
		if (!k) return 0;
		if (k >= (1ll << v[0])) return -1;
		long long ret = 0;
		for (int i = 1; i <= v[0]; i++)
		{
			if (k & (1 << (i - 1)))
			{
				ret ^= v[i];
				k -= (1 << (i - 1));
			}
		}
		// if (k) return -1;
		return ret;
	}
	void clear()
	{
		memset (v, 0, sizeof (v));
		n = t = cnt = 0;
	}
}G;
long long a[10005];
int main()
{
	int t;
	// freopen ("1.in", "r", stdin);
	// freopen ("1.out", "w", stdout);
	scanf ("%d", &t);
	int Cnt = 0;
	while (t--)
	{
		printf ("Case #%d:\n", ++Cnt);
		G.clear();
		int n;
		scanf ("%d", &n);
		for (int i = 1; i <= n; i++) 
			scanf("%I64d", &a[i]);
		G.Build(a, n);
		int q, k;
		scanf ("%d", &q);
		for (int i = 1; i <= q; i++)
		{
			scanf ("%d", &k);
			printf ("%I64d\n", G.Query(k));
		}
	}
}
