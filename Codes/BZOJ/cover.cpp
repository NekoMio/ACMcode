#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Point
{
	int x,y;
	bool operator < (const Point &a)const 
	{
		return x == a.x ? y < a.y : x < a.x;
	}
}a[20005];
int n;
struct limit
{
	int x1, y1, x2, y2;
}v[5];
bool dfs(int dep, int mid)
{
	int X1 = 0x3f3f3f3f, X2 = -0x3f3f3f3f, Y1 = 0x3f3f3f3f, Y2 = -0x3f3f3f3f;
	for (int i = 1; i <= n; i++)
	{
		bool flag = 0;
		for (int j = 3; j > dep; j--)
			if(a[i].x <= v[j].x2 && a[i].x >= v[j].x1 && a[i].y <= v[j].y2 && a[i].y >= v[j].y1)
				flag = 1;
		if(!flag)
		{
			X1 = min(X1, a[i].x);
			X2 = max(X2, a[i].x);
			Y1 = min(Y1, a[i].y);
			Y2 = max(Y2, a[i].y);
		}
	}
	if(X1 == 0x3f3f3f3f) return 1;
	if(dep == 1)
	{
		if(X2 - X1  <= mid && Y2 - Y1  <= mid)
			return 1;
		else
			return 0;
	}
	bool ans = 0;
	v[dep].x1 = X1;
	v[dep].x2 = X1 + mid ;
	v[dep].y1 = Y1;
	v[dep].y2 = Y1 + mid ;
	ans |= dfs(dep - 1, mid);
	v[dep].x1 = X1;
	v[dep].x2 = X1 + mid ;
	v[dep].y2 = Y2;
	v[dep].y1 = Y2 - mid ;
	ans |= dfs(dep - 1, mid);
	v[dep].x2 = X2;
	v[dep].x1 = X2 - mid ;
	v[dep].y2 = Y2;
	v[dep].y1 = Y2 - mid ;
	ans |= dfs(dep - 1, mid);
	v[dep].x2 = X2;
	v[dep].x1 = X2 - mid ;
	v[dep].y1 = Y1;
	v[dep].y2 = Y1 + mid ;
	ans |= dfs(dep - 1, mid);
	return ans;
}
bool Judge(int x)
{
	return dfs(3, x);
}
int main()
{
	freopen("cover1.in","r",stdin);
	//freopen("cover.out","w",stdout);
	scanf("%d",&n);
	int l, r = -0x3f3f3f3f, M = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].x,&a[i].y);
		r = max(r, max(a[i].x, a[i].y));
		M = min(M, min(a[i].x, a[i].y));
	}
	l = 0, r = r - M + 10;
	int ans = 0;
	while(l <= r)
	{
		int mid = l + r >> 1;
		if(Judge(mid))
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	//printf("%d",Judge(175));
	printf("%d\n", ans);
}