#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1000005;
int a[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int Sum[N];
int Have[N];
int main()
{
//	freopen ("set.in", "r", stdin);
//	freopen ("set.out", "w", stdout);
	int n = read();
	Have[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		a[i] = read() % n;
		Sum[i] = (Sum[i - 1] + a[i]) % n;
		if (Have[Sum[i]])
		{
			printf ("%d\n", i - Have[Sum[i]]);
			for (int j = Have[Sum[i]] + 1; j <= i; j++)
				printf ("%d ", j);
			return 0;
		}
		Have[Sum[i]] = i;
	}
	printf ("-1");
	fclose(stdin), fclose(stdout);
	return 0;
}
