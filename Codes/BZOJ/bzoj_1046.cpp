#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[10005],n;
int f[10005],g[10005];
int Maxlen = 0;
int find(int x)
{
	int l = 1, r = Maxlen ,ans = 0;
	while(l <= r)
	{
		int m = l + r>>1;
		if(g[m] > x) l = m + 1,ans = m;
		else r = m - 1;
	}
	return ans;
}
void printans(int x)
{
	int pre = 0x80808080;
	for(int i = 1; i <= n; i++)
	{
		if(f[i] >= x && a[i] > pre)
		{
			printf("%d",a[i]);
			if(x != 1)
				printf(" ");
			pre = a[i];
			x--;
			if(!x)
				break;
		}
	}
	printf("\n");
}
int main(int argc, char const *argv[])
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		scanf("%d",&a[i]);
	for (int i = n; i > 0; i--)
	{
		f[i] = find(a[i]) + 1;
		Maxlen = max(Maxlen, f[i]);
		g[f[i]] = max(g[f[i]],a[i]);
	}
	//printf("%d\n",Maxlen);
	int m;
	scanf("%d",&m);
	while(m--)
	{
		int len;
		scanf("%d", &len);
		if(len > Maxlen) 
			printf("Impossible\n");
		else
			printans(len);
	}
	return 0;
}