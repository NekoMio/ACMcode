#include <cstdio>
#include <cstring>
#include <algorithm>

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

using namespace std;
const int MAXN = 500005;

int a[MAXN];
int Cnt, Head;

int main()
{
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	int n = read(), q = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= q; i++)
	{
		int l = read(), r = read();
		Head = -1; Cnt = 0;
		for (int j = l; j <= r; j++)
		{
			if (a[j] == Head || Head == -1)
			{
				Cnt++;
				Head = a[j];
			}
			else
			{
				Cnt--;
				if (Cnt == 0) Head = -1;
			}
		}
		if (Head != -1)
		{
			int Sum = 0;
			for (int j = l; j <= r; j++)
				if (a[j] == Head)
					Sum++;
			if (2 * Sum > r - l + 1) printf ("%d\n", Head);
			else printf ("-1\n");
		}
		else
			printf ("-1\n");
	}
}
