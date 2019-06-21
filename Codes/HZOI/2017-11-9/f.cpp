#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
stack<int> s;
int a[100005], pos[100005];
int L[100005], R[100005];
int U[(100005 << 1) + 200][17];
int st[(100005 << 1) + 200][17];
int QueryMx(int l, int r)
{
	int k = 0;
	while ((1 << k) <= r - l + 1) k++;
	k--;
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int Calc(int x, int mid, int &ans)
{
	for (int i = 16; i >= 0; i--)
		if (a[U[x][i]] <= mid)
			x = U[x][i], ans += (1 << i);
//	printf("%d\n",ans);
	if (a[x] == mid) return 0;
	if (min(L[x], R[x]) == mid)
	{
		ans ++;
		return 0;
	}
	else
	{
		ans += 2;
		return 1;
	}
}
int main()
{
//	freopen("f.in", "r", stdin);
//	freopen("f.out", "w", stdout);
	int n = read(), m = read();
	a[0] = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++)
		a[i] = read(), st[i][0] = a[i], pos[a[i]] = i;
	for (int i = 1; i <= n; i++)
	{
		while (!s.empty() && s.top() < a[i]) s.pop();
		L[i] = s.empty() ? 0 : s.top();
		s.push(a[i]);
	}
	while (!s.empty()) s.pop();
	for (int i = n; i >= 1; i--)
	{
		while (!s.empty() && s.top() < a[i]) s.pop();
		R[i] = s.empty() ? 0 : s.top();
		s.push(a[i]);
	}
	for (int i = 1; i <= 16; i++)
		for (int j = 1; j <= n; j++)
			st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
//	memset (U, 0x3f, sizeof (U));
	for (int i = 1; i <= n; i++) U[i][0] = pos[max(L[i], R[i])];
	for (int i = 1; i <= 16; i++)
		for (int j = 1; j <= n; j++)
			U[j][i] = U[U[j][i - 1]][i - 1];
	int x, y;
	while (m--)
	{
		x = read(), y = read();
		if (x > y) swap(x, y);
		int mid = QueryMx(x, y);
		int ans = 0;
		int X = Calc(x, mid, ans);
//		printf ("%d %d\n", ans, mid);
		int Y = Calc(y, mid, ans);
		if (X && Y) ans--; 
		printf ("%d\n", ans);
	}
//	fclose(stdin), fclose(stdout);
	return 0;
}
