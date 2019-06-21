#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int fa[30005], size[30005], d[30005];
int find(int x)
{
	if(fa[x] == x)
		return x;
	int o = fa[x];
	fa[x] = find(fa[x]);
	d[x] += d[o];
	return fa[x];
}
void merge(int a,int b)
{
	int x = find(a), y = find(b);
	fa[y] = x;
	d[y] = size[x];
	size[x] += size[y];
}
int main()
{
	char s[10];
	int p;
	for (int i = 1; i <= 30000; i++)
		fa[i] = i, size[i] = 1;
	scanf("%d", &p);
	for (int i = 1; i <= p; i++)
	{
		int a, b;
		scanf("%s", s);
		if(s[0] == 'M')
		{
			scanf("%d%d",&a,&b);
			merge(a, b);
		}
		else
		{
			scanf("%d", &a);
			printf("%d\n",size[find(a)] - d[a] - 1);
		}
	}
}