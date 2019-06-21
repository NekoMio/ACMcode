#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}


struct edge
{
	int END, next, v;
}v[50];
int first[20], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}

int n, S, m;
bool flag;
void DFS(int rt, int t)
{
	if (rt == n)
	{
		if (t != 1) flag = 1;
		return;
	}
	for (int i = first[rt]; i != -1; i = v[i].next)
		DFS(v[i].END, t + ((S & (1 << i)) != 0));
}

bool Judge(int x)
{
	flag = 0;
	S = x;
	DFS(1, 0);
	return !flag;
}

int Calc(int x)
{
	int ans = 0;
	for (int i = 0; i < m; i++)
		if (x & (1 << i))
			ans += v[i].v;
	return ans;
}

int main()
{
	freopen("mer.in", "r", stdin);
	freopen("mer.out", "w", stdout);
	n = read();
	m = read();
	memset (first, -1, sizeof (first));
	int a, b, c;
	for (int i = 1; i <= m; i++)
	{
		a = read(), b = read(), c = read();
		add(a, b, c);
		// add(b, a, c);
	}
	int N = (1 << m) - 1;
	int ans = 0x3f3f3f3f;
	for (int i = 1; i <= N; i++)
	{
		if (Judge(i))
			ans = min(ans, Calc(i));
	}
	printf ("%d\n", ans);
}
