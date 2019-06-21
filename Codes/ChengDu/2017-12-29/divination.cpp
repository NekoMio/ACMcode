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

struct point
{
	int x, y;
}a[10];

#define K(_,__)(\
((double)(_).y - (__).y) / ((_).x - (__).x)\
)

int x[10];
char c[11];
int main()
{
	freopen("journey.in", "r", stdin);
	freopen("journey.out", "w", stdout);
	int n = read();
	for (int i = 1; i <= n; i++)
		a[i].x = read(), a[i].y = read();
	scanf ("%s", c + 1);
	int N = 1;
	for (int i = 1; i <= n; i++) x[i] = i, N = N * i;
	while (N--)
	{
		bool flag = 0;
		for (int i = 1; i <= n - 2; i++)
		{
			if (c[i] == 'L')
			{
				if (!(K(a[x[i + 1]], a[x[i + 2]]) > K(a[x[i]], a[x[i + 1]])))
				{
					flag = 1;
					break;
				}
			}
			else 
			{
				if (!(K(a[x[i + 1]], a[x[i + 2]]) < K(a[x[i]], a[x[i + 1]])))
				{
					flag = 1;
					break;
				}
			}
		}
		if (!flag)
		{
			for (int i = 1; i <= n; i++)
				printf ("%d ", x[i]);
			return 0;
		}
		next_permutation(x + 1, x + n + 1);
	}
	printf ("Impossible\n");
	return 0;
}
