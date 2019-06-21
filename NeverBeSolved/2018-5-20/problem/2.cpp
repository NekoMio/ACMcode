#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
	int n = read(), m = read(), c = read();
	double x, y;
	for (int i = 1; i <= n; i++)
		scanf ("%lf%lf", &x, &y);
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read();
		printf ("%d %d\n", a, b);
	}
}
