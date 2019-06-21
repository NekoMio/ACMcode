#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline void gmin(int &a, int b) { a > b ? a = b : 0; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int INF = 0x3f3f3f3f;
struct Matrix
{
	int a[305][305];
	int n;
	Matrix(int _n = 0)
	{
		n = _n;
		memset (a, 0x3f, sizeof (a));
	}
	Matrix operator * (const Matrix &b)
	{
		Matrix ans(n);
		register int i, j, k;
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++) if (a[i][j] != INF)
				for (k = 1; k <= n; k++) if (b.a[j][k] != INF)
					gmin(ans.a[i][k], a[i][j] + b.a[j][k]);
		return ans;
	}
	bool check()
	{
		for (int i = 1; i <= n; i++)
			if (a[i][i] < 0) return 0;
		return 1;
	}
	void print()
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				printf ("%d%c", a[i][j], " \n"[j == n]);
		printf ("\n");
	}
}A[10], B, tmp;
int main()
{
	int n = read(), m = read();
	A[0].n = n;
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read();
		A[0].a[a][b] = read();
	}
	for (int i = 1; i <= n; i++)
		A[0].a[i][i] = 0;
	for (int i = 1; i <= 8; i++)
		A[i] = A[i - 1] * A[i - 1];
	B.n = n;
	for (int i = 1; i <= n; i++)
		B.a[i][i] = 0;
	int ans = 0;
	for (int i = 8; i >= 0; i--)
	{
		tmp = B * A[i];
		if (tmp.check())
		{
			B = tmp;
			ans |= (1 << i);
		}
	}
	ans++;
	if (ans == 512)
		printf ("0\n");
	else printf ("%d\n", ans);
}
