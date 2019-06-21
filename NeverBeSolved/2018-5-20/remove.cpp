#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
struct data
{
	int x1, x2, x3, x4, id;
	bool operator < (const data &a) const 
	{
		return x1 < a.x1;
	}
}a[MAXN];
struct cmp
{
	bool operator()(const data &x, const data &y) const 
	{
		return x.x2 > y.x2;
	}
};
priority_queue<data, vector<data>, cmp> Q;
int Max[MAXN], n, cnt;
#define lowbit(_) ((_)&(-_))
void U(int x, int c)
{
	for (int i = x; i <= cnt; i += lowbit(i))
		Max[i] = max(Max[i], c);
}
int Query(int x)
{
	int ans = 0;
	for (int i = x; i >= 1; i -= lowbit(i))
		ans = max(ans, Max[i]);
	return ans;
}
int f[MAXN];
int Hash[MAXN * 2], tot;
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		a[i].x1 = read(), a[i].x2 = read(), a[i].x3 = read(), a[i].x4 = read();
		Hash[++tot] = a[i].x4;
		Hash[++tot] = a[i].x3;
	}
	sort(Hash + 1, Hash + tot + 1);
	cnt = unique(Hash + 1, Hash + tot + 1) - Hash - 1;
	for (int i = 1; i <= n; i++)
	{
		a[i].x4 = lower_bound(Hash + 1, Hash + cnt + 1, a[i].x4) - Hash;
		a[i].x3 = lower_bound(Hash + 1, Hash + cnt + 1, a[i].x3) - Hash;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		a[i].id = i;
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		f[i] = 1;
		while (!Q.empty() && Q.top().x2 < a[i].x1)
		{
			U(Q.top().x4, f[Q.top().id]);
			Q.pop();
		}
		f[i] = max(f[i], Query(a[i].x3) + 1);
		ans = max(ans, f[i]);
		Q.push(a[i]);
	}
	printf ("%d\n", ans);
}
