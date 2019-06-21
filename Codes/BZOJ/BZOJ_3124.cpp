#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 200005;
struct edge
{
	int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].v = c;                     
	v[p].next = first[a];
	first[a] = p++;
}
vector<int> st;
int Max = 0, Size, Num;
int C1[MAXN], C2[MAXN], Sum1[MAXN], Sum2[MAXN];
void dfs(int rt, int fa, int dis)
{
	if (dis > Max)
	{
		Max = dis;
		Size = 1;
		Num = rt;
		st.clear();
		st.push_back(rt);
	}
	else if (dis == Max)
	{
		st.push_back(rt);
		Size++;
	}
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs(v[i].END, rt, dis + v[i].v);
	}
}
int ans = 0, size1, size2;
void dfs(int rt, int fa)
{
	Sum1[rt] += C1[rt];
	Sum2[rt] += C2[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs(v[i].END, rt);
		Sum1[rt] += Sum1[v[i].END];
		Sum2[rt] += Sum2[v[i].END];
	}
	if (Sum1[rt] == size1 && !Sum2[rt]) ans++;
	if (Sum2[rt] == size2 && !Sum1[rt]) ans++;
}
signed main()
{
	memset (first, -1, sizeof (first));
	int n = read();
	int a, b, c;
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read(), c = read();
		add(a, b, c);
		add(b, a, c);
	}
	dfs(1, 0, 0);
	for (int i = 0; i < st.size(); i++)
		C1[st[i]] = 1;
	st.clear();
	size1 = Size;
	Max = 0;
	dfs(Num, 0, 0);
	for (int i = 0; i < st.size(); i++)
		C2[st[i]] = 1;
	size2 = Size;
	printf ("%lld\n", Max);
	dfs(1, 0);
	printf ("%lld\n", ans);
}
