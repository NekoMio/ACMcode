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
const int N = 10005;
int fa[N];
int find(int x)
{
	while (fa[x] != x) x = fa[x];
	return x;
}

void setroot(int x, int c)
{
	if (fa[x] != x) setroot(fa[x], x);
	fa[x] = c;
}

int main()
{
	int n = read(), m = read(), a, b;
	char s[10];
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		scanf ("%s", s);
		a = read(), b = read();
		setroot(a, a);
		if (s[0] == 'C') fa[a] = b;
		else if (s[0] == 'D') fa[b] = b;
		else
		{
			if (find(a) == find(b)) puts("Yes");
			else puts("No");
		} 
	}
}
