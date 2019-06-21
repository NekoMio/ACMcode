#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline void gmax(int &a, int b) { a < b ? a = b : 0; }
inline void gmin(int &a, int b) { a > b ? a = b : 0; }
inline int min(int a, int b) { return a < b ? a : b; }
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read()
{
	int x=0,f=1;char ch=getc();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
	return x*f;
}
const int MAXN = 100005;
struct edge
{
	int END, next, v;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].v = c;
	v[p].next = first[a];
	first[a] = p++;
}
int LX[MAXN], RX[MAXN], Index, n, m, len, dis[MAXN];
void DFS(int rt)
{
	LX[rt] = ++Index;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		dis[v[i].END] = dis[rt] + v[i].v;
		DFS(v[i].END);
	}
	RX[rt] = Index;
}
int in[MAXN], L[MAXN], R[MAXN];
int Max[MAXN], Min[MAXN], Sum[1000][20000], a[MAXN], cnt, Add[MAXN], sqt, sqr = 4000;
inline void Rebuild()
{
	for (int i = 1; i <= n; i++) a[i] += Add[in[i]];
	for (int i = 1; i <= cnt; i++) Add[i] = 0;
	cnt = 0;
	L[++cnt] = 1;
	Min[cnt] = Max[cnt] = a[1];
	for (int i = 1; i <= n; i++)
	{
		if (a[i] - Min[cnt] > sqr || Max[cnt] - a[i] > sqr)
		{
			R[cnt] = i - 1;
			L[++cnt] = i;
			Max[cnt] = Min[cnt] = a[i];
		}
		gmax(Max[cnt], a[i]);
		gmin(Min[cnt], a[i]);
		in[i] = cnt;
		if (i - L[cnt] == sqt)
		{
			R[cnt] = i, L[++cnt] = i + 1;
		}
	}
	if (L[cnt] == n + 1) cnt--;
	else R[cnt] = n;
	for (int i = 1; i <= cnt; i++)
	{
		for (int j = 0; j <= Max[i] - Min[i]; j++)
			Sum[i][j] = 0;
		for (int j = L[i]; j <= R[i]; j++)
			Sum[i][a[j] - Min[i]]++;
		for (int j = 1; j <= Max[i] - Min[i]; j++)
			Sum[i][j] += Sum[i][j - 1];
	}
}
inline int Calc(int l, int r, int x)
{
	int ans = 0;
	if (in[l] == in[r])
	{
		for (int i = l; i <= r; i++)
			if (a[i] + Add[in[l]] <= x)
				ans++;
		return ans;
	}
	else
	{
		for (int i = l; i <= R[in[l]]; i++)
			if (a[i] + Add[in[l]] <= x)
				ans++;
		for (int i = L[in[r]]; i <= r; i++)
			if (a[i] + Add[in[r]] <= x)
				ans++;
		for (int i = in[l] + 1; i <= in[r] - 1; i++)
			if (x >= Min[i])
				ans += Sum[i][min(x, Max[i]) - Min[i]];
		return ans;
	}
}
inline int Query(int l, int r, int k)
{
	if (r - l + 1 < k) return -1;
	int ll = 0, rr = 2e6, ans = 0;
	while (ll <= rr)
	{
		int mid = ll + rr >> 1;
		if (Calc(l, r, mid) >= k) ans = mid, rr = mid - 1;
		else ll = mid + 1;
	}
	return ans;
}
inline void Rebuild(int z)
{
	Min[z] = Max[z] = a[L[z]] + Add[z];
	for (int i = L[z]; i <= R[z]; i++)
	{
		a[i] += Add[z];
		gmin(Min[z], a[i]);
		gmax(Max[z], a[i]);
	}
	Add[z] = 0;
	for (int i = 0; i <= Max[z] - Min[z]; i++)
		Sum[z][i] = 0;
	for (int i = L[z]; i <= R[z]; i++)
		Sum[z][a[i] - Min[z]]++;
	for (int j = 1; j <= Max[z] - Min[z]; j++)
		Sum[z][j] += Sum[z][j - 1];
}
int times = 0;
inline void Update(int l, int r, int x)
{
	times++;
	if (in[l] == in[r])
	{
		for (int i = l; i <= r; i++)
			a[i] += x;
		Rebuild(in[l]);
	}
	else
	{
		for (int i = l; i <= R[in[l]]; i++)
			a[i] += x;
		Rebuild(in[l]);
		for (int i = L[in[r]]; i <= r; i++)
			a[i] += x;
		Rebuild(in[r]);
		for (int i = in[l] + 1; i < in[r]; i++)
		{
			Add[i] += x;
			Max[i] += x;
			Min[i] += x; 
		}
	}
	if (times == 1000)
	{
		Rebuild();
		times = 0;
	}
}
int main()
{
	// freopen ("j21.in", "r", stdin);
	// freopen ("j.out", "w", stdout);
	memset (first, -1, sizeof (first));
	n = read(), m = read(), len = read();
	for (int i = 2; i <= n; i++)
	{
		int x = read();
		add(x, i, read());
	}
	DFS(1);
	sqt = 300;
	// sqr = sqt * len;
	for (int i = 1; i <= n; i++)
		a[LX[i]] = dis[i];
	Rebuild();
	while (m--)
	{
		int op = read(), x = read(), k = read();
		if (op == 1)
		{
			printf ("%d\n", Query(LX[x], RX[x], k));	
		}
		else
		{
			Update (LX[x], RX[x], k);
		}
	}
}
