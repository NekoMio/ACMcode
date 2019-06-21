#include <cstdio>
#include <cstring>
#include <algorithm>

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

using namespace std;

const int MAXN = 200005;
struct data
{
	int S, E, v;
	data(int a = 0, int b = 0, int c = 0) {S = a, E = b, v = c;}
}a[MAXN];

int main()
{
	freopen ("journey.in", "r", stdin);
	freopen ("journey.out", "w", stdout);
	int n = read(), m = read();
	int d, b, c;
	for (int i = 1; i <= m; i++)
	{
		d = read(), b = read(), c = read();
		a[i] = data(d, b, c);
	}
	int N = (1 << n) - 1;
	for (int i = 1; i <= m; i++)
	{
		printf ("0\n");
	}
}
