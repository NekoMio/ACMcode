#include <bits/stdc++.h>
using namespace std;
struct data
{
	int a, i;
	bool operator < (const data &c)const
	{
		return a < c.a;
	}
}a[10005];
int main()
{
	srand(time(NULL));
	int n;
	scanf("%d", &n);
	printf ("%d\n", n);
	for (int i = 1; i <= n; i++)
		a[i].a = rand(), a[i].i = i;
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		printf ("%d ", a[i].i);
}