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
const int MAXN = 10005;
int a[MAXN];
int main()
{
	int n;
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int Max = a[i], Min = a[i];
		for (int j = i; j >= 1; j--)
		{
			Max = max(Max, a[j]);
			Min = min(Min, a[j]);
			if (Max - Min == i - j) ans++;
		}
	}
	printf ("%lld\n", ans);
}