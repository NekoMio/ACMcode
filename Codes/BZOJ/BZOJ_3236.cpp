#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int a[100005];
int in[100005], block;
struct Query
{
	int l, r, a, b, ID;
	bool operator < (const Query &c) const
	{
		return in[l] == in[c.l] ? r > c.r : in[l] < in[c.l];
	}
}Q[1000005];
int sum[100005], n;
int out1[1000005], out2[1000005];
int size[100005], size2[100005];
#define lowbit(_) ((_)&(-_))
void add(int x, int c)
{
	for (int i = x; i <= n; i+=lowbit(i))
		sum[i] += c;
	if(c == 1 && size2[x]) return;
	if(c == -1 && size2[x] != 1) return;
	for (int i = x; i <= n; i+=lowbit(i))
		size[i] += c;
}
int query(int x)
{
	int ans = 0;
	for (int i = x; i > 0; i-=lowbit(i))
		ans += sum[i];
	return ans;
}
int query2(int x)
{
	int ans = 0;
	for (int i = x; i > 0; i-=lowbit(i))
		ans += size[i];
	return ans;
}
int main()
{
	int m;
	scanf("%d%d", &n, &m);
	block = sqrt(n + 0.5);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		in[i] = (i - 1) / block + 1;
		add(a[i], 1);
		size2[a[i]]++;
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d%d", &Q[i].l, &Q[i].r, &Q[i].a, &Q[i].b);
		Q[i].ID = i;
	}
	sort(Q + 1, Q + m + 1);
	int l = 1, r = n;
	for (int i = 1; i <= m; i++)
	{
		while(l < Q[i].l) {add(a[l],-1); size2[a[l]]--; l++;}
		while(l > Q[i].l) {l--; add(a[l], 1); size2[a[l]]++;}
		while(r > Q[i].r) {add(a[r],-1); size2[a[r]]--; r--;}
		while(r < Q[i].r) {r++, add(a[r], 1); size2[a[r]]++;}
		out1[Q[i].ID] = query(Q[i].b) - query(Q[i].a - 1);
		out2[Q[i].ID] = query2(Q[i].b) - query2(Q[i].a - 1);
	}
	for (int i = 1; i <= m; i++)
		printf("%d %d\n", out1[i], out2[i]);
}