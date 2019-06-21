#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long I[100005], I2[100005];
struct data
{
	long long l, r;
	long long Sum, Sumi, Sumi2;
	long long lazy;
}Tree[100005 << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void PushUp(int rt)
{
	Tree[rt].Sum = Tree[rt << 1].Sum + Tree[rt << 1 | 1].Sum;
	Tree[rt].Sumi = Tree[rt << 1].Sumi + Tree[rt << 1 | 1].Sumi;
	Tree[rt].Sumi2 = Tree[rt << 1].Sumi2 + Tree[rt << 1 | 1].Sumi2;
}
void buildtree(int l, int r, int rt)
{
	Tree[rt].l = l, Tree[rt].r = r;
	if(l == r)
		return;
	int m = l + r >> 1;
	buildtree(lch);
	buildtree(rch);
}
void PushDown(int rt)
{
	if(Tree[rt].lazy)
	{
		Tree[rt<<1].lazy += Tree[rt].lazy;
		Tree[rt<<1|1].lazy += Tree[rt].lazy;
		Tree[rt<<1].Sum += (Tree[rt<<1].r - Tree[rt<<1].l + 1) * Tree[rt].lazy;
		Tree[rt<<1].Sumi += (I[Tree[rt<<1].r] - I[Tree[rt<<1].l - 1]) * Tree[rt].lazy;
		Tree[rt<<1].Sumi2 += (I2[Tree[rt<<1].r] - I2[Tree[rt<<1].l - 1]) * Tree[rt].lazy;
		Tree[rt<<1|1].Sum += (Tree[rt<<1|1].r - Tree[rt<<1|1].l + 1) * Tree[rt].lazy;
		Tree[rt<<1|1].Sumi += (I[Tree[rt<<1|1].r] - I[Tree[rt<<1|1].l - 1]) * Tree[rt].lazy;
		Tree[rt<<1|1].Sumi2 += (I2[Tree[rt<<1|1].r] - I2[Tree[rt<<1|1].l - 1]) * Tree[rt].lazy;
		Tree[rt].lazy = 0;
	}
}
void Update(int L, int R, int c, int rt)
{
	int l = Tree[rt].l, r = Tree[rt].r;
	if(L <= l && R >= r)
	{
		Tree[rt].lazy += c;
		Tree[rt].Sum += (r - l + 1) * c;
		Tree[rt].Sumi += (I[r] - I[l - 1]) * c;
		Tree[rt].Sumi2 += (I2[r] - I2[l - 1]) * c;
		return;
	}
	int m = l + r >> 1;
	PushDown(rt);
	if(L <= m) Update(L,R,c,rt<<1);
	if(R > m) Update(L,R,c,rt<<1|1);
	PushUp(rt);
}
data Query(int L, int R, int rt)
{
	int l = Tree[rt].l, r = Tree[rt].r;
	if(L <= l && R >= r)
	{
		return Tree[rt];
	}
	int m = l + r >> 1;
	PushDown(rt);
	data ans;
	if(R <= m) return Query(L, R, rt<<1);
	if(L > m) return Query(L, R, rt<<1|1); 
	data X = Query(L,R,rt<<1);
	data Y = Query(L,R,rt<<1|1);
	ans.Sum = X.Sum + Y.Sum;
	ans.Sumi = X.Sumi + Y.Sumi;
	ans.Sumi2 = X.Sumi2 + Y.Sumi2;
	return ans;
}
long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}
int main()
{
	int n, m, l, r, d;
	char s[10];
	for (int i = 1; i <= 100000; i++)
		I[i] = I[i - 1] + i, I2[i] = I2[i - 1] + (long long)i * i;
	scanf("%d%d", &n, &m);
	buildtree(1, n - 1, 1);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s",s);
		if(s[0] == 'C')
		{
			scanf("%d%d%d", &l, &r, &d);
			r--;
			Update(l,r,d,1);
		}
		else
		{
			long long Sum = 0;
			scanf("%d%d", &l, &r);
			r--;
			data A = Query(l, r, 1);
			Sum = -A.Sum * (r + 1) * (l - 1) + (l + r) * A.Sumi - A.Sumi2;
			long long S = ((long long)(r - l + 2)) * (r - l + 1) / 2;
			long long GCD = gcd(Sum, S);
			printf("%lld/%lld\n", Sum/GCD, S/GCD);
		}
	}
}