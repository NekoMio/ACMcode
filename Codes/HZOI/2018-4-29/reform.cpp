#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
#include <cassert>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
set<int> st[405];
int max(int a, int b, int c, int d)
{
	return max(a, max(b, max(c, d)));
}
long long fab = 100000;
long long val[2] = {9705276, 12805858}, a[100005], Max, b[100005], c[100005];
double tmp;
bool Test(int n)
{
	if (1ll * n * val[0] > Max) return 0;
	return 1;
}
long long Calc(int S, int n)
{
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		if (S & (1 << (i - 1)))
			ans += val[1];
		else ans += val[0];
	return ans;
}
struct data
{
	int a, b;
	data(int _a = 0, int _b = 0): a(_a), b(_b) {}
}pre[405][205][205];
int F[405][205][205];
void Upd(int i, int j, int k, int pi, int pj, int pk)
{
	if (F[pi][pj][pk] == -1) return;
	if (F[i][j][k] <= F[pi][pj][pk])
	{
		F[i][j][k] = F[pi][pj][pk];
		pre[i][j][k].a = pj, pre[i][j][k].b = pk;
	}
}
int S[405];
void BUILD(int mid, int z, int y, int pos, int t)
{
	S[mid - pos] = z - pre[mid - pos][z][y].a;
	S[mid + pos + 1 + t] = y - pre[mid - pos][z][y].b;
	if (mid <= pos + 1) return;
	BUILD(mid, pre[mid - pos][z][y].a, pre[mid - pos][z][y].b, pos + 1, t);
}
int main()
{
	freopen("reform1.in", "r", stdin);
	int n = read();
	Max = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf ("%lf", &tmp);
		a[i] = round(tmp * fab);
		if (a[i] < val[0]) n--, i--;
		Max = max(Max, a[i]);
	}
	int nx = 0, ny = 0, len = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= 400; j++)
		{
			if ((a[i] - j * val[0]) % val[1] == 0)
			{
				b[i] = j;
				c[i] = (a[i] - j * val[0]) / val[1];
				if (Max == a[i])
				{
					nx = b[i], ny = c[i];
					len = nx + ny;
				}
				assert(!st[b[i]].count(c[i]));
				st[b[i]].insert(c[i]);
				break;
			}
		}
	}
	memset (F, -1, sizeof (F));
	F[0][0][0] = st[nx].count(ny);
	for (int i = 1; i <= len / 2; i++)
	{
		for (int j = 0; j <= i && j <= nx; j++) if (ny - i + j >= 0)
		{
			for (int k = 0; k <= i && k <= nx; k++) if (ny - i + k >= 0)
			{
				if (j + k > nx || i - j + i - k > ny) continue;
				Upd(i, j, k, i - 1, j, k);
				if (j > 0) Upd(i, j, k, i - 1, j - 1, k);
				if (k > 0) Upd(i, j, k, i - 1, j, k - 1);
				if (j > 0 && k > 0) Upd(i, j, k, i - 1, j - 1, k - 1);
				if (F[i][j][k] == -1) continue;
				F[i][j][k] += st[j].count(i - j);
				if (j != k) F[i][j][k] += st[k].count(i - k);
				if (i * 2 != len)
				{
				// if ((j != nx - k || i - j != ny - i + k)) 
					F[i][j][k] += st[nx - k].count(ny - i + k);
					// if ((k != nx - j || i - k != ny - i + j))
					if (k != j)
						F[i][j][k] += st[nx - j].count(ny - i + j);
				}
			}
		}
	}
	int ans = 0, si, sj;
	int t = len / 2;
	for (int i = 1; i <= nx; i++)
		for (int j = 1; j <= nx; j++) if (j + i == nx || ((len & 1) && (j + i == nx - 1)))
		{
			if (ans < F[t][i][j])
			{
				ans = F[t][i][j];
				si = i, sj = j;
			}
		}
	// printf ("%d\n", ans);
	BUILD(t, si, sj, 0, (len & 1));
	for (int i = 1; i <= len; i++)
	{
		if (S[i])
			printf ("P");
		else printf ("Q");
	}
	printf ("\n");
	// while (1);
}
