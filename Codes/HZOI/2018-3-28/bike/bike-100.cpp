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
const int MAXN = 50005;
int a[MAXN], l[MAXN], n, k;
long long f[MAXN][21], S[MAXN][2], Sum[MAXN][2], lSum[MAXN][2];
long long SUM(int l, int r)
{
	if (l > r) return 0;
	long long t = Sum[r][0] - Sum[l - 1][0];
	long long Size = lSum[r][0] - lSum[l - 1][0];
	return t - Size * S[l][0];
}
long long SUM2(int r, int l)
{
	if (l > r) return 0;
	long long t = Sum[l][1] - Sum[r + 1][1];
	long long Size = lSum[l][1] - lSum[r + 1][1];
	return t - Size * S[r][1];
}
long long len(int l, int r)
{
	return S[r][0] - S[l][0];
}
long long Calc(int L, int R)
{
	int ll = L, rr = R, ans = 0;
	while (ll <= rr)
	{
		int mid = ll + rr >> 1;
		if (len(L, mid) >= len(mid, R)) ans = mid, rr = mid - 1;
		else ll = mid + 1;
	}
	return SUM(L, ans - 1) + SUM2(R, ans);
}
bool Judge(int x, int y, int mid, int j)
{
	return Calc(x, mid) + f[x][j - 1] < Calc(y, mid) + f[y][j - 1];
}
#define TNT(x, y)\
(\
	Calc(x, y) + f[x][j - 1]\
)
struct data
{
	int id, pos;
	data(int _id = 0, int _pos = 0) : id(_id), pos(_pos) {}
}st[MAXN];
int main()
{
	// freopen ("bike_example_2.in", "r", stdin);
	// freopen("13.txt", "w", stdout);
	n = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i < n; i++)
		l[i] = read();
	for (int i = 1; i <= n; i++)
		S[i][0] = S[i - 1][0] + l[i - 1];
	for (int i = 1; i <= n; i++)
		lSum[i][0] = lSum[i - 1][0] + a[i];
	for (int i = 1; i <= n; i++)
		Sum[i][0] = Sum[i - 1][0] + a[i] * S[i][0];
	// for (int i = 1; i <= n; i++)
		// printf ("%d ", Sum[i][0]);
	// printf ("\n");
	for (int i = n; i >= 1; i--)
		S[i][1] = S[i + 1][1] + l[i];
	for (int i = n; i >= 1; i--)
		lSum[i][1] = lSum[i + 1][1] + a[i];
	for (int i = n; i >= 1; i--)
		Sum[i][1] = Sum[i + 1][1] + a[i] * S[i][1];
	// for (int i = 1; i <= n; i++)
	// {
	// 	for (int j = 1; j <= n; j++)
	// 		printf ("%d ", Calc(i, j));
	// 	printf ("\n");
	// }
	// while (1);
	memset (f, 0x3f, sizeof (f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		f[i][1] = SUM2(i, 1);
		// printf ("%lld ", f[i][1]);
	}
	// printf ("\n");
	for (int j = 2; j <= k; j++)
	{
		int top = 0;
		st[++top] = data(1, 1);
		for (int i = 2; i <= n; i++)
		{
			int ans = n + 1;
			int l = i + 1, r = n;// ans = n + 1;
			while (top && st[top].pos >= i && TNT(st[top].id, st[top].pos) >= TNT(i, st[top].pos)) r = st[top].pos, top--;
			l = max(st[top].pos + 1, i);
			while (l <= r)
			{
				int mid = l + r >> 1;
				if (Judge(i, st[top].id, mid, j)) ans = mid, r = mid - 1;
				else l = mid + 1;
			}
			if (ans <= n)
				st[++top] = data(i, ans); 
		}
		// for (int i = 1; i <= top; i++)
		// 	printf ("%d ", st[i].id);
		// printf ("\n");
		int now = 1;
		for (int i = 1; i <= n; i++)
		{
			if (i >= st[now + 1].pos) now++;
			f[i][j] = f[st[now].id][j - 1] + Calc(st[now].id, i);
			// printf("%d\n", st[now].id);
			// printf ("%lld ", f[i][j]);
		}
		// printf ("\n");
	}
	// for (int j = 1; j <= k; j++)
	// {
		// for (int i = 1; i <= n; i++)
			// printf ("%lld ", f[i][j]);
		// printf ("\n");
	// }	
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[i][k] + SUM(i, n));
	printf ("%lld\n", ans);
}