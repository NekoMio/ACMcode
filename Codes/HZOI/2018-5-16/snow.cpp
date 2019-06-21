#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 3e5 + 10000;
struct data
{
	int l, r;
}a[MAXN];
bool flag[MAXN];
struct Node
{
	int L, R, l, r, Min, id, tmp, Minr, Maxl, Cutl, Cutr;
	void Pushup()
	{
		while (l <= r && flag[l]) l++;
		while (l <= r && flag[r]) r--;
		if (l > r) return Min = 0x3f3f3f3f, id = 0, void();
		tmp = min(tmp, r);
		tmp = max(tmp, l);
		if (Cutl) tmp = l;
		else
		{
			for (int i = tmp - 1; i >= l; i--)
			{
				if (flag[i]) continue;
				if (a[i].l != a[r].l) break;
				tmp = i;
			}
		}
		if (!Cutl && !Cutr)
		{
			Min = 0x3f3f3f3f, id = 0;
			Maxl = 0, Minr = 0x3f3f3f3f;
			for (int i = l; i <= r; i++)
			{
				if (flag[i]) continue;
				if (a[i].r - a[i].l < Min)
					Min = a[i].r - a[i].l, id = i;
				Maxl = max(Maxl, a[i].l);
				Minr = min(Minr, a[i].r);
			}
		}
		else if (!Cutl)
		{
			Min = Cutr - a[r].l, id = tmp;
			Maxl = a[r].l, Minr = Cutr;
		}
		else if (!Cutr)
		{
			Min = a[l].r - Cutl, id = l;
			Maxl = Cutl, Minr = a[l].r;
		}
		else
		{
			Min = Cutr - Cutl, id = l;
			Maxl = Cutl, Minr = Cutr;
		}
	}
	void Pushdown()
	{
		if (!Cutl && !Cutr) return;
		for (int i = l; i <= r; i++)
		{
			if (flag[i]) continue;
			if (Cutl) a[i].l = Cutl;
			if (Cutr) a[i].r = Cutr;
		}
		Cutl = Cutr = 0;
	}
}c[10105];
int in[MAXN], m;
void Update(int x)
{
	int t = in[x];
	c[t].Pushdown();
	flag[x] = 1;
	for (int i = c[t].L; i < x; i++) if (!flag[i]) a[i].r = min(a[i].r, a[x].l);
	for (int i = c[t].R; i > x; i--) if (!flag[i]) a[i].l = max(a[i].l, a[x].r);
	c[t].Pushup();
	for (int i = t - 1; i >= 1; i--)
	{
		if (c[i].l > c[i].r) continue;
		if (c[i].Minr >= a[x].l)
		{
			c[i].Cutr = a[x].l;
			c[i].Pushup();
		}
		else
		{
			c[i].Pushdown();
			for (int j = c[i].r; j >= c[i].l; j--)
			{
				if (flag[j]) continue;
				if (a[j].r >= a[x].l) a[j].r = a[x].l;
				else break;
			}
			c[i].Pushup();
			break;
		}
	}
	for (int i = t + 1; i <= m; i++)
	{
		if (c[i].l > c[i].r) continue;
		if (c[i].Maxl <= a[x].r)
		{
			c[i].Cutl = a[x].r;
			c[i].Pushup();
		}
		else
		{
			c[i].Pushdown();
			for (int j = c[i].l; j <= c[i].r; j++)
			{
				if (flag[j]) continue;
				if (a[j].l <= a[x].r) a[j].l = a[x].r;
				else break;
			}
			c[i].Pushup();
			break;
		}
	}
}
int main()
{
	// freopen("1.in", "r", stdin);
	int t = read(), n = read();
	for (int i = 1; i <= n; i++)
		a[i].l = read(), a[i].r = read();
	int block = pow(n, 0.5);
	for (int i = 1; i <= n; i++)
		in[i] = (i - 1) / block + 1;
	m = in[n];
	for (int i = 1; i <= m; i++)
	{
		c[i].L = (i - 1) * block + 1, c[i].R = min(i * block, n);
		c[i].l = c[i].L, c[i].r = c[i].R;
		c[i].tmp = c[i].r;
		c[i].Pushup();
	}
	for (int i = 1; i <= n; i++)
	{
		int Min = 0x3f3f3f3f, id = 0;
		for (int j = 1; j <= m; j++)
			if (Min > c[j].Min)
			{
				Min = c[j].Min;
				id = c[j].id;
			}
		printf ("%d\n", id);
		Update(id);
	}
}
