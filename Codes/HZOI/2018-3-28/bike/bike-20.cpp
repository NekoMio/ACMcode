#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 50005;
int a[MAXN], l[MAXN], n, k;
long long dis_tmp[50], dis[50];
void Calc_dis(int x)
{
	dis_tmp[x] = 0;
	for (int i = x - 1; i >= 1; i--)
		dis_tmp[i] = dis_tmp[i + 1] + l[i];
	for (int i = x + 1; i <= n; i++)
		dis_tmp[i] = dis_tmp[i - 1] + l[i - 1];
}
int Num(int x)
{
	int ans = 0;
	while (x)
	{
		ans += x & 1;
		x >>= 1;
	}
	return ans;
}
int main()
{
	n = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n - 1; i++)
		l[i] = read();
	int N = (1 << n) - 1;
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= N; i++)
	{
		long long tmp = 0;
		if (Num(i) > k) continue;
		memset (dis, 0x3f, sizeof (dis));
		for (int j = 1; j <= n; j++)
			if (i & (1 << (j - 1)))
			{
				Calc_dis(j);
				for (int l = 1; l <= n; l++)
					dis[l] = min(dis[l], dis_tmp[l]);
			}
		for (int i = 1; i <= n; i++)
			tmp += 1ll * dis[i] * a[i];
		ans = min(ans, tmp);
	}
	printf ("%lld\n", ans);
}