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
int a[30];
int main()
{
	int n = read();
	for (int i = 0; i < n; i += 1)
	{
		a[i] = read();
	}
	int N = (1 << n);
	int ans = 0;
	for (int i = 0; i < N; i += 1)
	{
		int t = 0;
		for (int j = 0; j < n; j += 1) if (i & (1 << j))
			t ^= a[j];
		int S = i ^ (N - 1);
		for (int j = S; ; j = (j - 1) & S)
		{
			int z = 0;
			for (int k = 0; k < n; k += 1) if (j & (1 << k))
				z ^= a[k];
			if (z == t) ans++;
			if (!j) break;
		}
	}
	printf ("%d\n", ans - 1);
}
