#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#ifndef LL
#define LL long long
#endif
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
const int N = 100005;
LL Sum[N << 2];
bool flag[N << 2];
void PushUp(int rt)
{
	Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
	flag[rt] = flag[rt << 1] & flag[rt << 1 | 1];
}
void buildtree(int l, int r, int rt)
{
	if(l == r)
	{
		scanf("%lld", &Sum[rt]);
		if(Sum[rt] <= 1)
			flag[rt] = 1;
		return;
	}
	int m = l + r >> 1;
	buildtree(lch);
	buildtree(rch);
	PushUp(rt);
}
void Update(int L, int R, int l, int r, int rt)
{
	if(flag[rt])
		return;
	if(l == r)
	{
		Sum[rt] = sqrt(Sum[rt]);
		if(Sum[rt] <= 1)
			flag[rt] = 1;
		return;
	}
	int m = l + r >> 1;
	if (L <= m) Update(L, R, lch);
	if (R > m) Update(L, R, rch);
	PushUp(rt);
}
LL Query(int L, int R, int l, int r, int rt)
{
	if(L <= l && R >= r)
		return Sum[rt];
	int m = l + r >> 1;
	LL ans = 0;
	if (L <= m) ans += Query(L, R, lch);
	if (R > m) ans += Query(L, R, rch);
	return ans;
}
int main()
{
	int n;
	scanf("%d", &n);
	buildtree(1, n, 1);
	int m;
	scanf("%d", &m);
	while (m--)
	{
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(l > r)
			swap(l, r);
		if (op == 1)
		{
			printf("%lld\n", Query(l, r, 1, n, 1));
		}
		else
			Update(l, r, 1, n, 1);
	}
}