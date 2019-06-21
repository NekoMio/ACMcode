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
const int MAXN = 10005;
double f[MAXN], g[MAXN];
int main()
{
	int n = read();
	f[0] = 0;
	for (int i = 1; i <= n; i++)
		f[i] = f[i - 1] + 1.0 * n / (n - i + 1);
	// for (int i = 1; i <= n; i++) printf ("%.3f\n", f[i]);
	g[1] = 1;
	for (int i = 2; i <= n; i++)
		g[i] = g[i - 1] + (f[i - 1] + 1) * n / (n - i + 1) + 1.0 * n * n / (n - i + 1) / (n - i + 1) - 1.0 * n / (n - i + 1);
	// for (int i = 1; i <= n; i++) printf ("%.3f\n", g[i]);
	printf ("%.2f\n", g[n]);
}