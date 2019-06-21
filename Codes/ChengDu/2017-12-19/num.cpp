#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MOD = 1e9;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}


int st[200], cnt[11], top;
long long ans = 0;
int Sum = 1;

void DFS(int x, int t, int now)
{
	if (x < 0) return;
	if (x == 0) 
	{
		return ans += t, void();
	}
	for (int i = 1; i <= 9; i++)
		DFS(x - i, t * 10 + i, i);
}

int main()
{
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
	{
		Sum *= m;
		DFS(Sum, 0, 1);
	}
	printf ("%lld\n", ans % MOD);
}