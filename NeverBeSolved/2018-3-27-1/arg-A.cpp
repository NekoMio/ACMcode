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
const int MAXN = 16;
int a[MAXN], b[MAXN], ans;
bool vis[MAXN];
int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
		a[i] = read();
	DFS(1, 1);
	printf ("%d\n", ans);
}